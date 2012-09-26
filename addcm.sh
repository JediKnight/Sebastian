#!/bin/bash

prog='Sebastian'
ver='0.0.1'
src='sebastian.c sebastian.h lex.yy.l'
addr='bug@bamboo-copter.com'

echo "cd $1"
cd $1
pwd

function runproc()
{
    echo -n "$2."

    while :
    do
	if [ `ps -p $1 |grep -v PID |wc -l |awk '{print $1}'` -eq 0 ]; then
	    break
	fi
	echo -n "."
	sleep 1
    done

    echo " ok"
}

make clean >/dev/null 2>&1 &
runproc $! "make clean"

rm -f configure.in &
runproc $! "delete configure.in"

rm -f Makefile.am &
runproc $! "delete Makefile.am"

rm -f src/Makefile.am
runproc $! "delete src/Makefile.am"

touch INSTALL NEWS README COPYING AUTHORS ChangeLog &
runproc $! "touch INSTALL NEWS README COPYING AUTHORS ChangeLog"

autoscan &
runproc $! "run autoscan"

mv configure.scan configure.in &
runproc $! "rename configure.scan => configure.in"

echo "AM_INIT_AUTOMAKE([FULL-PACKAGE-NAME], [VERSION])" >>configure.in &
runproc $! "add automake directive"

echo "AC_PROG_LEX" >>configure.in &
runproc $! "add flex directive"

echo "AC_PROG_YACC" >>configure.in &
runproc $! "add bison directive"

gsed -i "s|FULL-PACKAGE-NAME|$prog|g" configure.in &
runproc $! "change package name"

gsed -i "s|VERSION|$ver|g" configure.in &
runproc $! "change version"

gsed -i "s|BUG-REPORT-ADDRESS|$addr|" configure.in &
runproc $! "change bugreport address"

echo "SUBDIRS = src" >Makefile.am &
runproc $! "add source directory directive"


echo "bin_PROGRAMS = $prog" >src/Makefile.am &
runproc $! "add program name directive"

echo "${prog}_SOURCES = $src" >>src/Makefile.am &
runproc $! "add source file list"

aclocal &
runproc $! "aclocal"

autoconf &
runproc $! "autoconf"

autoheader &
runproc $! "autoheader"

automake --copy --add-missing &
runproc $! "automake"
