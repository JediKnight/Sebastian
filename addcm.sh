#!/bin/bash

prog='Sebastian'
ver='0.0.1'
src='sebastian.c sebastian.h lex.yy.l'
addr='bug@bamboo-copter.com'

echo "cd $1"
cd $1
pwd

echo "make clean"
make clean >/dev/null 2>&1 &
while :
do
    if [ `ps ax |grep make |grep -v grep |wc -l |awk '{print $1}'` -eq 0 ]; then
	break
    fi
    echo -n "."
    sleep 1
done

echo "done"

echo "delete "
rm -f configure.in
rm -f Makefile.am
rm -f src/Makefile.am

echo "touch new file"
touch INSTALL NEWS README COPYING AUTHORS ChangeLog

echo "autoscan"
autoscan

mv configure.scan configure.in

echo "AM_INIT_AUTOMAKE([FULL-PACKAGE-NAME], [VERSION])" >>configure.in
[ ! -z $4 ] && echo "AC_PROG_LEX" >>configure.in
#[ ! -z $5 ] && echo "AM_PROG_YACC" >>configure.in

gsed -i "s|FULL-PACKAGE-NAME|$prog|g" configure.in
gsed -i "s|VERSION|$ver|g" configure.in
gsed -i "s|BUG-REPORT-ADDRESS|$addr|" configure.in

echo "SUBDIRS = src" >Makefile.am

echo "bin_PROGRAMS = $prog" >src/Makefile.am
echo "${prog}_SOURCES = $src" >>src/Makefile.am

aclocal
autoconf
autoheader
automake --copy --add-missing
