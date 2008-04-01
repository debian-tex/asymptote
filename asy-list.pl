#!/usr/bin/env perl
#####
# asy-list.pl
#
#  Build asy-keywords.el from list of asy global functions and variables 
#
#####

open(keywords, "> asy-keywords.el") ||
    die("Couldn't open asy-keywords.el for writing.");

print keywords <<END;
;;
;; This file is automatically generated by asy-list.pl.
;; Changes will be overwritten.
;;
(defvar asy-keywords-version "$ARGV[1]")

END

sub add {
  print keywords $_[0]." ";
}

sub openlist {
    open(asylist, $ARGV[0]) || die("Couldn't open $ARGV[0]");
}

print keywords <<END;
(defvar asy-keyword-name '(
END

open(camp, "camp.l") || die("Couldn't open camp.l");

# Search for the %% separator, after which the definitions start.
while (<camp>) {
  if (/^%%\s*$/) {
    last; # Break out of the loop.
  }
}

while (<camp>) {
  if (/^%%\s*$/) {
    last; # A second %% indicates the end of definitions.
  }
  if (/^(\w+)\s*\{/) {
    add($1);
  }
}

openlist();

while (<asylist>) {
  if (/^(\w*)[^ ]* (\w*)\(.*/) {
    push @types, $1;
    push @functions, $2;
  }
  if (/^([^ ]*) (\w*);/) {
    push @variables, $2;
  }
}

@saw{@types} = ();
@types = sort keys %saw; 
undef %saw;

@saw{@functions} = ();
@functions = sort keys %saw; 
undef %saw;

@saw{@variables} = ();
@variables = sort keys %saw; 
undef %saw;

print keywords <<END;
))

(defvar asy-type-name '(
END

foreach(@types) {
 print keywords $_ . " ";
}

print keywords <<END;
))

(defvar asy-function-name '(
END

foreach(@functions) {
 print keywords $_ . " ";
}

print keywords <<END;
))

(defvar asy-variable-name '(
END

foreach(@variables) {
 print keywords $_ . " ";
}

print keywords "))\n";

