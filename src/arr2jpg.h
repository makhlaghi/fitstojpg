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

/* To keep the color mode codes: */
#define CMYKNAME       "cmyk"
#define GRAYNAME       "gray"
#define CMYKCODE       'c'
#define GRAYCODE       'g'


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
  /* Operating modes: */
  int                 inv;      /* Inverse grayscale image.            */
  int              allext;      /* Convert all extensions to JPEG.     */
  int                 log;	/* Logarithmic or not.                 */
  int         ttrunccolor;      /* High truncation as max color.       */
  int         btrunccolor;	/* Low truncation as min color.        */
  int        convertfirst;	/* First convert then truncate.        */

  /* Input FITS image: */
  char           *imgname;	/* Name of input.                      */
  int              imgext;	/* Extention of FITS image.            */
  float           fluxlow;	/* Lower pixel value trunctation.      */
  float          fluxhigh; 	/* Higher pixel value truncation.      */
  int                  x1;	/* Crop Bottom left corner x axis.     */
  int                  y1;	/* Crop Bottom left corner y axis.     */
  int                  x2;	/* Crop Top right corner x axis.       */
  int                  y2;	/* Crop Top right corner y axis.       */
  struct conversion *conv;	/* Structure to define conversion.     */

  /* Output JPEG image: */
  char           *outname;	/* Name of output.                     */
  int             quality;	/* Quality of JPEG compression.        */
  float             width;	/* Width of image in cm.               */
  char          colormode;	/* c: CMYK. g: Grayscale.              */
  unsigned char    maxjpg;	/* Maximum BYTE value to use in image. */
  int             iborder;      /* Inner border (black) width.         */
  int             oborder;     	/* Outer border (White) width.         */

  /* Internal options: */
  int         freeoutname;	/* Free the outname or not?            */
};



void
arr2jpg(void *arr, size_t s0, size_t s1, int bitpix, 
	struct a2jparams *p);


#endif
