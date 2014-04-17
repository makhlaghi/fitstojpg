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

struct a2jparams
{
  char *inname;			/* Name of input. */
  char *outname;		/* Name of output. */
  char  color;			/* c: CMYK. g: Grayscale. */
  int   ext;			/* Extention of FITS image. */
  float width;			/* Width of image in cm. */
  float low;			/* Lower pixel value trunctation. */
  float high;			/* Higher pixel value truncation. */
  float log;			/* Logarithmic or not. */
  float inv;
};

void
float2jpg(float *arr, size_t s0, size_t s1, struct a2jparams *p);


#endif
