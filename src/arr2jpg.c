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
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <assert.h>
#include <jpeglib.h>

#include "arr2jpg.h"
#include "stats.h"






void
makejsample(JSAMPLE **a, size_t size, char color)
{
  JSAMPLE *jsarr;

  if(sizeof *jsarr!=1)
    {
      printf("\n\nJSAMPLE has to be unsigned char!\n\n");
      exit(EXIT_FAILURE);
    }

  if(color=='c') size*=4;	/* For CMYK. */
  
  assert( (jsarr=malloc(size*sizeof *jsarr))!=NULL );

  *a=jsarr;
}





void
floatfilljsarr(JSAMPLE *jsr, float *arr, size_t size, char color, 
	       int inv)
{
  size_t i;
  double m;
  float min, max;

  fminmax(arr, size, &min, &max);
  m=(double)UCHAR_MAX/((double)max-(double)min);

  if(color=='g')
    {
      if(inv)
	for(i=0;i<size;i++)
	  jsr[i]=UCHAR_MAX-(arr[i]-min)*m;
      else
	for(i=0;i<size;i++)
	  jsr[i]=(arr[i]-min)*m;
    }
  else
    for(i=0;i<size;i++)
      {
	jsr[i*4+3]=UCHAR_MAX-(arr[i]-min)*m;
	jsr[i*4]=jsr[i*4+1]=jsr[i*4+2]=0;
      }

}





void
float2jpg(float *arr, size_t s0, size_t s1, struct a2jparams *p)
{
  JSAMPLE *a;
  JSAMPROW r[1];
  FILE * outfile;
  int row_stride, c;
  struct jpeg_error_mgr jerr;
  struct jpeg_compress_struct cinfo;

  assert(p->color=='c' || p->color=='g');

  makejsample(&a, s0*s1, p->color);
  
  floatfilljsarr(a, arr, s0*s1, p->color, p->inv);

  /* Begin the JPEG writing, following libjpeg's example.c  */
  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_compress(&cinfo);

  if ((outfile = fopen(p->outname, "wb")) == NULL) {
    fprintf(stderr, "can't open output file %s\n", p->outname);
    exit(1);
  }
  jpeg_stdio_dest(&cinfo, outfile);

  cinfo.image_width  = s1;
  cinfo.image_height = s0;
  if(p->color=='c')
    {
      row_stride=4*s1;
      cinfo.input_components = 4;
      cinfo.in_color_space = JCS_CMYK;
    }
  else
    {
      row_stride=s1;
      cinfo.input_components = 1;
      cinfo.in_color_space = JCS_GRAYSCALE;
    }

  jpeg_set_defaults(&cinfo);
  jpeg_set_quality(&cinfo, 100, TRUE);
  cinfo.density_unit=1;
  cinfo.Y_density=cinfo.X_density=s1/(p->width/2.54);
  jpeg_start_compress(&cinfo, TRUE);

  /* cinfo.next_scanline is 'unsigned int' */
  c=s0-1; /* In FITS the first row is on the bottom!  */
  while (cinfo.next_scanline < cinfo.image_height) 
    {
      r[0] = & a[c-- * row_stride];
      (void) jpeg_write_scanlines(&cinfo, r, 1);
    }

  jpeg_finish_compress(&cinfo);
  fclose(outfile);
  jpeg_destroy_compress(&cinfo);
  free(a); 
}
