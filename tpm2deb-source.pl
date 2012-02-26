#!/usr/bin/perl
#
# tpm2deb-source.pl
# machinery to create debian packages from TeX Live depot
# (c) 2005, 2006, 2007, 2008, 2009, 2010, 2011 Norbert Preining
#
# $Id$
#
# configuration is done via the file tpm2deb.cfg
# 

use strict;
no strict 'refs';
# use warnings;
# no warnings 'uninitialized';

my $opt_master;
our $opt_debug;
our $opt_nosrcpkg;
our $opt_noremove;
my $globalreclevel;
my $oldsrcdir;

BEGIN {
	unshift (@INC, "./all/debian");
}

my ($mydir,$mmydir);
($mydir = $0) =~ s,/[^/]*$,,;
if ($mydir eq $0) { $mydir = `pwd` ; chomp($mydir); }
if (!($mydir =~ m,/.*,,)) { $mmydir = `pwd`; chomp($mmydir); $mydir = "$mmydir/$mydir" ; }


# $opt_master = "./LocalTPM";
$opt_debug = 0;
$opt_nosrcpkg = 0;
$opt_noremove = 0;
$globalreclevel = 1;
$oldsrcdir = "./src";

use Getopt::Long;

GetOptions ("debug!", 	# debug mode
			"nosrcpkg!",			# dont build source package
			"noremove!",			# dont remove build dir
			"master=s" => \$opt_master,	# location of Master
			"reclevel=i" => \$globalreclevel,	# recursion level
			"oldsource=s" => \$oldsrcdir	# use old source
	);
 

#use Strict;
use File::Basename;
use File::Copy;
use File::Path;
use File::Temp qw/ tempfile tempdir /;
use Cwd;
use tpm2debcommon ;


my $changelog = "";
my $changelogversion = "";
my $changelogextraversion = "";
my $changelogrevision = "";
my $changelogdistribution = "";
my $allowed_dists = "(unstable|UNRELEASED|sarge-backports|etch-backports|stable-security|experimental)";


our $Master;

if (!($opt_master =~ m,^/.*$,,)) {
	$Master = `pwd`;
	chomp($Master);
	$Master .= "/$opt_master";
} else {
	$Master = $opt_master;
}

#
# put Master/Tools/ into the include path to find TeX Live perl modules
#
unshift (@INC, "$Master/tlpkg");
#
# these we can only load now that we have correctly set the path to Master
#
require TeXLive::TLPDB;

File::Basename::fileparse_set_fstype('unix');


&main(@ARGV);

1;


####################################################################
#
# PART 0: The main() function
#
####################################################################

# variables needed outside of main
my $version;
my $revision;
my $extraversion;
my $date;
my $arch;
my $shortl;

sub main {
	my ($cmd,@packages) = @_;
	$arch = "all";
	$::tlpdb = TeXLive::TLPDB->new(root => "$Master");
	die "Cannot load tlpdb!" unless defined($::tlpdb);
	initialize_config_file_data("all/debian/tpm2deb.cfg");
	use Data::Dumper;
	#print Dumper(\%Config);
	build_data_hash();
	#print Dumper(\%TeXLive);
	check_consistency();
	if ("$cmd" eq "make-control") {
		foreach my $package (@packages) {
			$arch = get_arch($package);
			make_deb_control($package,"$package.control");
		}
		exit 0;
	}
	foreach my $package (@packages) {
		# 
		# various variables have to be set
		#
		$arch = get_arch($package);
		print "Working on $package, arch=$arch\n";
		if ("$cmd" eq "make-deb-source") {
			make_deb_source($package);
		} elsif ("$cmd" eq "make-orig-tar") {
			read_changelog($package);
			$version = "$changelogversion$changelogextraversion";
			$revision = $changelogrevision;
			make_orig_tar($package);
		} else {
			print "cmd >$cmd< undefined!\n";
		}
	}
}


sub read_changelog {
	my ($package) = @_;

# 	print "entering read_changelog: $mydir/$package/debian/changelog\n";
# 	myopen(CL, "<$mydir/$package/debian/changelog") || die("Cannot open $mydir/$package/debian/changelog");;
 	open(CL, "<$mydir/$package/debian/changelog") || die("Cannot open $mydir/$package/debian/changelog");;
	my @lines = <CL>;
	close(CL);
# 	print "lines=@lines\n\n";

	my $dataline = "";
	$extraversion = "";
	$version = "";
	$revision = "";
	$date = "";

	foreach my $line (@lines) {
		print "changelog header=$line...\n";
		$line =~ m/^#/ && next;
		$line =~ m/^\s*$/ && next;
		# now we should have the first/top line, break out
		if ($line =~ m/^$package \(([^-]*)-(\S*)\) $allowed_dists; urgency=/) {
			$changelogversion = "$1";
			$changelogrevision = "$2";
			print "changelog version: $changelogversion-$changelogrevision\n";
			return;
		} else {
			print STDERR "$line\n";
			die("cannot parse changelog file $package.changelog\n Allowed dists:\n$allowed_dists");
		}
	}
}


#
# make_orig_tar
#
# Build the .orig.tar.gz from the perforce depot
#
sub make_orig_tar {
	# my function
	sub unpack_package {
		my ($pkg, $dest) = @_;
		if ($TeXLive{'binary'}{$pkg}{'relocated'}) {
			$dest .= "/texmf-texlive";
		}
		File::Path::mkpath($dest);
		if (-r "$Master/archive/$pkg.tar.xz") {
			`tar -C $dest -xf $Master/archive/$pkg.tar.xz`;
		}
		if (-r "$Master/archive/$pkg.doc.tar.xz") {
			`tar -C $dest -xf $Master/archive/$pkg.doc.tar.xz`;
		}
		if (-r "$Master/archive/$pkg.source.tar.xz") {
			`tar -C $dest -xf $Master/archive/$pkg.source.tar.xz`;
		}
	}
	sub copy_unpack_included_packages {
		my ($binpkg, $dest) = @_;
		my @packs = @{$TeXLive{'binary'}{$binpkg}{'includedpackages'}};
		for my $p (@packs) {
			unpack_package($p, $dest);
		}
	}
	#
	# copy_collection_files 
	#
	sub copy_collection_files {
		my ($entry, $destination, $types) = @_;
		print "copy-collection-files $entry\n";
		my %lists = %{&get_all_files($entry,$globalreclevel)};
		my @allfiles = ();
		$opt_debug && print STDERR "copy_collection_files: entry=$entry, types=$types, destination=$destination\n";
		foreach my $type (split(/ /,$types)) {
			@allfiles = (@allfiles, @{$lists{$type}});
		}
		COLLFILE: foreach my $f (@allfiles) {
			foreach my $pat (@{$TeXLive{'all'}{'file_blacklist'}}) { 
				if ($f =~ m|^${pat}$|) { next COLLFILE ; }
			}
			mycopy("$Master/$f","$destination/$f");
		}
	}
	# real start
	my ($src_package) = @_;
	my $foo;
	my $tmpdir = "${src_package}-${version}";
	my $debdest = "$tmpdir/debian";

	# don't regenerate an already existing tarball
	if ( -f "${src_package}_${version}.orig.tar.gz" ) {
		print "${src_package}_${version}.orig.tar.gz already exists, skipping.\n";
		return 0;
	}

	#$texlivedest = "$tmpdir/Master";
	my $texlivedest = "$tmpdir";
	#
	# if $changelogrevision > 1 then bail out, we are not allowed to
	# build a new source!
	#
	if (1 lt $changelogrevision && ! ((my $tmprevision = $changelogrevision) =~ /1~/) ) {
		printf STDERR "ERROR ERROR ERROR\nYou are not allowed to generate a new source for revisions greater than 1!\nPlease specify the the location of the old sources with --oldsource=location\nExiting!\n";
		exit 1;
	}
	#
	# we are building a complete new package!
	# binfiles are always ignored because they are build from a different 
	# package
	# 
	my $types = "RunFiles DocFiles SourceFiles";
	#
	$opt_debug && print STDERR "Working on a source package!\n";
	foreach my $coll (@{$TeXLive{'source'}{$src_package}{'binary_packages'}}) {
		copy_unpack_included_packages($coll, $texlivedest);
		#copy_collection_files($coll,$texlivedest,$types);
	}
	#
	# 
	# copy the files necessary for tpm2deb.pl from the Tools directory
	#
	&mkpath("$texlivedest/tlpkg");
	system("cp -a $Master/tlpkg/texlive.tlpdb $Master/tlpkg/TeXLive $texlivedest/tlpkg") == 0
		or die("Cannot copy necessary tlpkg file");
	#
	# make everything writeable!
	#
	system("chmod -R u+w $tmpdir") == 0
	    or die("Cannot set permissions on $tmpdir");
	#
	# and remove x bits from all files under Master/texmf-dist/doc
	# this makes essential scripts in web2c (makeupd etc) not executable!
	# so disable it. We could run over {tex,...} if we want!
	if (-d "$texlivedest/texmf-dist") {
		system("find $texlivedest/texmf-dist/ -type f -print0 | xargs -0 chmod -x") == 0
		    or die("Cannot remove unwanted execution permissions");
	}
	if (-d "$texlivedest/texmf-doc") {
		system("find $texlivedest/texmf-doc/ -type f -print0 | xargs -0 chmod -x") == 0
		    or die("Cannot remove unwanted execution permissions");
	}
	# remove any svn directories
	system("find $texlivedest -name '.svn' | xargs rm -rf") == 0
		or die("Error while removing svn directories");
	#
	# make the original source package
	#
	system("tar -cf - $tmpdir | gzip -c9 > ${src_package}_${version}.orig.tar.gz") == 0
	    or die("Error creating orig.tar.gz");
	if (!$opt_debug && !$opt_noremove) { system("rm -rf $tmpdir"); }
}

#
# create_override_file
#
sub create_override_file {
	my ($package,$sourcepkg,$debdest,@locont) = @_;
	my @binlines;
	my @sourcelines;
	foreach (@locont) {
		if (m/^(\S*)#/) {
			next;
		} elsif (m/^(\S*) source: /) {
			if ($1 eq $sourcepkg) {
				push @sourcelines, $_;
			}
		} elsif (m/^(\S*): /) {
			if ($1 eq $package) {
				push @binlines, $_;
			}
		} else {
			push @binlines, "$package: $_";
		}
	}
	if ($#binlines >= 0) {
 		open(BINOVER,">$debdest/$package.override") 
		    or die("Cannot open $debdest/$package.override");
		foreach (@binlines) {
			print BINOVER $_;
		}
		close(BINOVER);
	}
	if ($#sourcelines >= 0) {
 		open(SOURCEOVER,">$debdest/source.lintian-overrides") 
		    or die("Cannot open $debdest/source.lintian-overrides");
		foreach (@sourcelines) {
			print SOURCEOVER $_;
		}
		close(SOURCEOVER);
	}
}

#
# make_deb_source
#
# We have to build a `real' debian package with .orig.tar.gz and a diff
# file. For this we start by putting the necessary files from the texmf trees
# into some subdirectory, and create the rest of the files via a diff
#
sub make_deb_source {
	my ($package) = @_;
	if ($package eq 'all') {
		foreach my $p (@{$TeXLive{'all'}{'sources'}}) {
			make_deb_source($p);
		}
		return 0;
	}
	my $foo;
	$arch = get_arch($package);
	read_changelog($package);
	$version = "$changelogversion$changelogextraversion";
	$revision = $changelogrevision;
	print "PACKAGE=$package ARCH=$arch VERSION=$version REVISION=$revision\n";
	# check for different places of old sources
	my $sourcedone = 0;
	my $oldorig;
	if (-r "./${package}_${version}.orig.tar.gz") {
		$oldorig = "./${package}_${version}.orig.tar.gz";
		$sourcedone = 1;
	} elsif (-r "$oldsrcdir/${package}_${version}.orig.tar.gz") {
		$oldorig = "$oldsrcdir/${package}_${version}.orig.tar.gz";
		system("cp $oldorig .") == 0 or die("Cannot cp $oldorig .!\n");
		$sourcedone = 1;
	}
	if ($sourcedone) {
		print "Reusing $oldorig file for source package building!\n";
		system("tar -xzf $oldorig") == 0 or die("Error untarring");
	} else {
		die("Please create a .orig.tar.gz first!\n");
	}
	my $tmpdir = "${package}-${version}";
	mkpath($tmpdir);
	$opt_debug && print STDERR "tmpdir = $tmpdir\n";
	my $debdest = "$tmpdir/debian";
	# $texlivedest = "$tmpdir/Master";
	my $texlivedest = "$tmpdir";
	# dpkg-source cannot handle new symlinks
	my $symlinklist = `find $mydir/all/ -type l`;
	die("Symlinks $symlinklist detected in $mydir/all") if $symlinklist;
	
	system ("cp -a $mydir/all/* $tmpdir/") == 0
	    or die("Error copying common files");
	system ("rm  $tmpdir/debian/rules.in") == 0
	    or die("Error removing rules.in");
	system ("find $tmpdir/ -name .svn -type d -print0 | xargs -0 rm -rf") == 0 
	    or die("Error removing .svn directories");

	system ("cp -a $mydir/$package/* $tmpdir/") == 0
	    or die("Error copying package-specific files");

	my @metapackages;
	my @normalpackages;
	foreach my $foo (@{$TeXLive{'source'}{$package}{'binary_packages'}}) {
		$opt_debug && print STDERR "DEBUG: $foo in @{$TeXLive{'all'}{'meta_packages'}}\n";
		if (ismember($foo,@{$TeXLive{'all'}{'meta_packages'}})) {
			push @metapackages, $foo;
		} else {
			push @normalpackages, $foo;
		}
	}
	system (qq{eperl -k -d arch=$arch -d srcpackage=$package -dbinpackages="@normalpackages" -dmetapackages="@metapackages" $mydir/all/debian/rules.in > $debdest/rules}) == 0
	    or die("Error creating debian/rules");;
	system(qq{chmod ugo+x $debdest/rules}) == 0
	    or die("Cannot change permissions of $debdest/rules");;

	make_deb_control($package,"$debdest/control");
	system ("find $tmpdir/ -name .svn -type d -print0 | xargs -0 rm -rf") == 0 
	    or die("Error removing .svn directories");
	# 
	# lintian override files
	#
	open(OVERRIDE,"<$mydir/all/debian/lintian.override") 
	    or die("Cannot open $mydir/all/debian/lintian.override");
	my @locont = <OVERRIDE>;
	close(OVERRIDE);
	foreach my $coll (@{$TeXLive{'source'}{$package}{'binary_packages'}}) {
		create_override_file($coll,$package,$debdest,@locont);
	} 
	# 
	# Building the source package
	#
	print STDERR "Building the package with dpkg-source\n";
	system ("chmod u+w $tmpdir/debian/*") == 0
	    or die("Error adjusting permissions of $tmpdir/debian");
	if (!$opt_nosrcpkg) {
	    my $dpkg_cmdline = "dpkg-source -b $tmpdir" . ($opt_debug ? "" : " 2>/dev/null");
	    system ( $dpkg_cmdline) == 0
		or die("Cannot pack ${package}_${version}!\n");
	}
	if (!$opt_debug && !$opt_noremove) { system("rm -rf $tmpdir"); }
}

#
# make_deb_control
#

sub make_deb_control {
	# my functions
	sub makeuniq {
		my ($arrayref) = @_;
		my %bla;
		foreach (@$arrayref) {
			$bla{$_} = 1;
		}
		@$arrayref = keys(%bla);
	}  
	sub unversioned_tetex_conflict {
		my (@AllConflicts) = @_;
		my $ret = 1;
		foreach my $conflict (@AllConflicts) {
			if ($conflict =~ m/^[[:space:]]*tetex-(base|extra|bin|source)[^(]*$/) {
				return(1);
			}
		}
		return(0);
	}
	# real start
	my ($package, $destfname) = @_;
	my $foo;
	open(CONTROL,">$destfname") || die("Cannot open $destfname!\n");
	print CONTROL "Source: $package\n";
	print CONTROL "Section: ",
		defined($TeXLive{'source'}{$package}{'section'}) ? "$TeXLive{'source'}{$package}{'section'}" : "$TeXLive{'all'}{'section'}",
		"\n";
	print CONTROL "Priority: ",
		defined($TeXLive{'source'}{$package}{'priority'}) ? $TeXLive{'source'}{$package}{'priority'} : "$TeXLive{'all'}{'priority'}",
		"\n";
	print CONTROL "Maintainer: ",
		defined($TeXLive{'source'}{$package}{'maintainer'}) ? $TeXLive{'source'}{$package}{'maintainer'} : "$TeXLive{'all'}{'maintainer'}",
		"\n";
	print CONTROL "Uploaders: ",
		defined($TeXLive{'source'}{$package}{'uploaders'}) ? $TeXLive{'source'}{$package}{'uploaders'} : "$TeXLive{'all'}{'uploaders'}",
		"\n";
	if (defined($TeXLive{'source'}{$package}{'build_dep'})) {
		print CONTROL "Build-Depends: $TeXLive{'source'}{$package}{'build_dep'}\n";
	}
	if (defined($TeXLive{'source'}{$package}{'build_dep_indep'})) {
		print CONTROL "Build-Depends-Indep: $TeXLive{'source'}{$package}{'build_dep_indep'}\n";
	}
	print CONTROL "Standards-Version: ",
		defined($TeXLive{'source'}{$package}{'standards'}) ? "$TeXLive{'source'}{$package}{'standards'}" : "$TeXLive{'all'}{'standards'}",
		"\n";
	print CONTROL "Homepage: http://www.tug.org/texlive/\n";
	#
	# now start the individual packages
	#
	my @pkglist = ();
	foreach my $pkg (@{$TeXLive{'source'}{$package}{'binary_packages'}}) {
		my %lists = %{&get_all_files($pkg,$globalreclevel)};
		my $title = $TeXLive{'binary'}{$pkg}{'title'};
		my @lop = ();
		my $contains_binaries = 0;
		# check that some packages are actually included before adding
		# intro text below to the control file
		foreach my $p (@{$TeXLive{'binary'}{$pkg}{'includedpackages'}}) {
			my $subtype = $TeXLive{'binary'}{$p}{'type'};
			if ($p =~ m/\.i386-linux$/) {
				$contains_binaries = 1 ;
			}
			if (($subtype eq "Package") || ($subtype eq "Documentation")) {
				push @lop, $p;
			}
		}
		my $description = $TeXLive{'binary'}{$pkg}{'description'};
		if (defined($TeXLive{'binary'}{$pkg}{'description'})) {
			$description = $TeXLive{'binary'}{$pkg}{'description'};
		}
		print CONTROL "\nPackage: $pkg\n";
		if (defined($TeXLive{'binary'}{$pkg}{'section'})) {
			print CONTROL "Section: $TeXLive{'binary'}{$pkg}{'section'}\n";
		}
		print CONTROL "Architecture: $arch\n";
		my @AllDepends = @{$TeXLive{'binary'}{$pkg}{'depends'}};
		# in case that we have binaries included we add the dep
		# onto texlive-bin-$source
		if ($contains_binaries) {
			#my $binname = $package; # texlive-{base,extra,lang,doc}
			#$binname .= "-binaries";
			#push @AllDepends, $binname;
			push @AllDepends, "texlive-binaries";
		}
		push @AllDepends, '${misc:Depends}';
# 		if ($arch eq "any") {
# 			push (@AllDepends, '${shlibs:Depends}');
# 		}
		print CONTROL "Depends: ";
		makeuniq(\@AllDepends);
		my @finaldeps = ();
		foreach my $d (@AllDepends) {
			if ($d =~ m/^texlive[^ ]*$/) {
				# if we match a package name without a space, ie without a
				# correct version number, we add the respective source
				# package minimal version
				my $srcpkg = $TeXLive{'binary'}{$d}{'source_package'};
				push @finaldeps, "$d (>= $TeXLive{'source'}{$srcpkg}{'latest_version'})";
			} else {
				push @finaldeps, "$d";
			}
		}
		print CONTROL join(", ",@finaldeps), "\n";
		$opt_debug && print STDERR  "\nDependencies for $package: ", join(", ",@AllDepends), "\n";
		#
		# Conflicts
		#
		my @AllConflicts = @{$TeXLive{'binary'}{$pkg}{'conflicts'}};
		if ($#AllConflicts >= 0) {
			makeuniq(\@AllConflicts);
			print CONTROL "Conflicts: ", join(", ", @AllConflicts), "\n";
		}
		#
		# Recommends
		#
		my @AllRecommends = @{$TeXLive{'binary'}{$pkg}{'recommends'}};
		if ($#AllRecommends >= 0) {
			makeuniq(\@AllRecommends);
			print CONTROL "Recommends: ", join(", ", @AllRecommends), "\n";
		}
		#
		# Provides
		#
		my @AllProvides = @{$TeXLive{'binary'}{$pkg}{'provides'}};
		if ($#AllProvides >= 0) {
			makeuniq(\@AllProvides);
			print CONTROL "Provides: ", join(", ", @AllProvides), "\n";
		}
		#
		# Suggests
		#
		my @AllSuggests = @{$TeXLive{'binary'}{$pkg}{'suggests'}};
		if ($#AllSuggests >= 0) {
			makeuniq(\@AllSuggests);
			print CONTROL "Suggests: ", join(", ", @AllSuggests), "\n";
		}
		#
		# Replaces
		#
		my @AllReplaces = @{$TeXLive{'binary'}{$pkg}{'replaces'}};
		if ($#AllReplaces >= 0) {
			makeuniq(\@AllReplaces);
			print CONTROL "Replaces: ", join(", ", @AllReplaces), "\n";
		}
		#
		print CONTROL "Description: TeX Live: $title\n";
		#
		my @deslines = split(/\n/, $description);
		my $firstline = 1;
		foreach my $l (@deslines) {
			if ($l =~ m/^\s*$/) {
				if ($firstline) { $firstline = 0; next; }
				print CONTROL " .\n";
			} else { 
				#$shortl = shortenline($l);
				#print CONTROL " $shortl\n";
				$shortl = $l;
				write CONTROL;
			}
		}
		if ($#lop < 0) {
			next;
		}
		print CONTROL " .\n This package includes the following CTAN packages:\n";
		foreach my $p (@lop) {
			next if is_blacklisted($p,$pkg);
			# ignore split out arch packages
			next if ($p =~ m/\.i386-linux$/);
			my $tit = $TeXLive{'binary'}{$p}{'title'};
			chomp($tit);
			# add an extra space at the beginning to have a real list
			$shortl = " $p -- $tit";
			write CONTROL;
		}
	}
	close CONTROL;
}


sub get_arch {
	my ($srcpackage) = @_;
	my $a = "all";
	if (defined($TeXLive{'source'}{$srcpackage}{'architecture'})) {
		$a = $TeXLive{'source'}{$srcpackage}{'architecture'};
	}
	return($a);
}

	

#####################################
#
# Formats
#
format CONTROL =
~^<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
$shortl
~~ ^<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
$shortl
.

### Local Variables:
### perl-indent-level: 4
### tab-width: 4
### indent-tabs-mode: t
### End:
# vim:set tabstop=4: #