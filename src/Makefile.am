## Process this file with automake to produce Makefile.in
##
## Hand written file: used as input into Autotools.
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

AM_CFLAGS = -Wall -O3
##AM_CFLAGS = -Wall -g -O0
AM_LDFLAGS = -lcfitsio -ljpeg -lm

bin_PROGRAMS = fitstojpg
fitstojpg_SOURCES = main.c main.h argpparser.h ui.c ui.h	\
fitsarrayvv.c fitsarrayvv.h arr2jpg.c arr2jpg.h stats.c stats.h	\
arraymanip.c arraymanip.h

## Necessary commands for `make check`:
TESTS = basic.sh fluxtrunc.sh borders.sh allextensions.sh crop.sh

CLEANFILES = basic.jpg fluxtrunc.jpg borders.jpg mock_1.jpg	\
mock_2.jpg mock_3.jpg crop.jpg
