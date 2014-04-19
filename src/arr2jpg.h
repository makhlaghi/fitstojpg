/*********************************************************************
fits2jpg - Convert FITS images to Grey scale JPEG images.

Copyright (C) 2014 Mohammad Akhlaghi
Tohoku University Astronomical Institute, Sendai, Japan.
http://astr.tohoku.ac.jp/~akhlaghi/

fits2jpg is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

fits2jpg is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with fits2jpg. If not, see <http://www.gnu.org/licenses/>.

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





/* Structure to define the inputs into float2jpg. */
struct a2jparams
{
  char *inname;			/* Name of input. */
  char *outname;		/* Name of output. */
  char  color;			/* c: CMYK. g: Grayscale. */
  int   inv;			/* Inverse grayscale image. */
  int   ext;			/* Extention of FITS image. */
  float width;			/* Width of image in cm. */
  float low;			/* Lower pixel value trunctation. */
  float high;			/* Higher pixel value truncation. */
  float log;			/* Logarithmic or not. */
  int   ibord;		        /* Inner border (black) width. */
  int   obord;	        	/* Outer border (White) width. */
};



void
arr2jpg(void *arr, size_t s0, size_t s1, int bitpix, 
	struct a2jparams *p);


#endif
