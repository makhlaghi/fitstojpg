/*********************************************************************
fitstojpg - Convert FITS images to Grey scale JPEG images.

Copyright (C) 2014 Mohammad Akhlaghi
Tohoku University Astronomical Institute, Sendai, Japan.
http://astr.tohoku.ac.jp/~akhlaghi/

fitstojpg is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

fitstojpg is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with fitstojpg. If not, see <http://www.gnu.org/licenses/>.

**********************************************************************/

#ifndef ARR2JPG_H
#define ARR2JPG_H


/* Macros for various types. These are intentionally chosen to be the
   same as CITSIO's implementation of the standard FITS types. */
#define BYTE_IMG        8
#define SHORT_IMG      16
#define LONG_IMG       32
#define LONGLONG_IMG   64
#define FLOAT_IMG     -32
#define DOUBLE_IMG    -64


/* This is used in converting certain values in the array. */
struct conversion
{
  float from;
  float to;
  struct conversion *next;
};



/* Structure to define the inputs into float2jpg. */
struct a2jparams
{
  /* On/Off options: */
  int   inv;			/* Inverse grayscale image. */
  int   allext;			/* Convert all extensions to JPEG. */
  int   log;			/* Logarithmic or not. */
  int   ttrunccolor;            /* High truncation as max color. */
  int   btrunccolor;		/* Low truncation as min color. */

  /* Options with arguments: */
  char *inname;			/* Name of input. */
  char *outname;		/* Name of output. */
  char  color;			/* c: CMYK. g: Grayscale. */
  int   quality;		/* Quality of JPEG compression. */
  int   ext;			/* Extention of FITS image. */
  float width;			/* Width of image in cm. */
  float low;			/* Lower pixel value trunctation. */
  float high;			/* Higher pixel value truncation. */
  int   ibord;		        /* Inner border (black) width. */
  int   obord;	        	/* Outer border (White) width. */
  struct conversion *conv;	/* Structure to define conversion. */

  /* Internal options: */
  int freeoutname;		/* Free the outname or not? */
};



void
arr2jpg(void *arr, size_t s0, size_t s1, int bitpix, 
	struct a2jparams *p);


#endif
