#!/bin/sh
#Test 1: install texlive-full/2009
echo "=== TeX Live Test System ==="
echo "=== Test 1: install/remove/install/purge texlive-full/2009 ==="
echo ""
echo "=== INSTALL APTITUDE"
apt-get install  --allow-unauthenticated --assume-yes  aptitude
aptargs="--without-recommends --assume-yes -o Aptitude::CmdLine::Ignore-Trust-Violations=yes"
echo "=== START INSTALL TEST VERSION"
echo "deb file:/ pool/" >> /etc/apt/sources.list
gunzip -c /pool/Packages.gz > /var/lib/apt/lists/_pool_Packages
aptitude install $aptargs tex-common texlive-full
echo "=== START REMOVE"
aptitude remove $aptargs texlive-full
echo "=== START INSTALL"
aptitude install $aptargs tex-common texlive-full
echo "=== START PURGE"
aptitude purge $aptargs '~ntexlive'
echo "=== END"