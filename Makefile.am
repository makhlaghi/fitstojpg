## Process this file with autoconf to produce a configure script.
##
## Hand written file: used as input into GNU Autotools (autoconf).
##
## NOTE:
## This file will be called by the Makefile.am in the top directory,
## so this file does not need to be called directly by automake to
## make the full FITStoJPG package.
##
## This is the automake instructions to build FITStoJPG.  FITStoJPG
## will convert a FITS image to a JPEG image. It is free software
## released under GNU GPLv3+.
##
## Copyright (C) 2014 Mohammad Akhlaghi
## Tohoku University Astronomical Institute, Sendai, Japan.
## http://astr.tohoku.ac.jp/~akhlaghi/

SUBDIRS = src doc

dist_doc_DATA = README

EXTRA_DIST = defaults.ac src/mock.fits src/allextensions.sh		\
src/basic.sh src/crop.sh src/fluxtrunc.sh src/borders.sh doc/texinfo.tex
