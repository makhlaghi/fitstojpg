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





/*************************************************************
 ***********           Make JSAMPLE array.         ***********
 *************************************************************/
void
makejsample(JSAMPLE **a, size_t s0, size_t s1, struct a2jparams *p)
{
  size_t size, o;
  JSAMPLE *jsarr;

  if(sizeof *jsarr!=1)
    {
      printf("\n\nJSAMPLE has to be unsigned char!\n\n");
      exit(EXIT_FAILURE);
    }

  o=p->ibord*2+p->obord*2;

  size=(s0+o)*(s1+o);
  if(p->color=='c') size*=4;	/* For CMYK. */

  if(p->obord+p->ibord)
    assert( (jsarr=calloc(size, sizeof *jsarr))!=NULL );
  else
    assert( (jsarr=malloc(size*sizeof *jsarr))!=NULL );   

  *a=jsarr;
}




















/*************************************************************
 ***********      Write JSAMPLE array to JPEG      ***********
 *************************************************************/
void
writeJSAMPLEtoJPEG(struct a2jparams *p, JSAMPLE *a, 
		   size_t s0, size_t s1)
{
  JSAMPROW r[1];
  FILE * outfile;
  int row_stride, c;
  struct jpeg_error_mgr jerr;
  struct jpeg_compress_struct cinfo;

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
}




















/*************************************************************
 ***********       Prepare input FLOAT array       ***********
 *************************************************************/
/* Fill the JSAMPLE array with no border. */
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
    {
      for(i=0;i<size;i++)
	{
	  jsr[i*4+3]=UCHAR_MAX-(arr[i]-min)*m;
	  jsr[i*4]=jsr[i*4+1]=jsr[i*4+2]=0;
	}
    }
}





/* Fill the JSAMPLE array, leaving space for a border. */
void
floatfilljsarr_wbord(JSAMPLE *jsr, float *arr, size_t s0, size_t s1, 
		 struct a2jparams *p)
{
  double m;
  size_t ib, ob;
  float min, max;
  size_t i, j, start, o, ns0, ns1;

  fminmax(arr, s0*s1, &min, &max);
  m=(double)UCHAR_MAX/((double)max-(double)min);

  assert(min<max);		/* Might go crazy sometimes! */

  ib=p->ibord;
  ob=p->obord;
  o=ib+ob;
  ns0=s0+2*o;
  ns1=s1+2*o;

  if(p->color=='g')
    {
      if(p->inv)
	for(i=0;i<s0;i++)
	  for(j=0;j<s1;j++)
	    jsr[(i+o)*ns1+j+o]=UCHAR_MAX-(arr[i*s1+j]-min)*m;
      else
	for(i=0;i<s0;i++)
	  for(j=0;j<s1;j++)
	    jsr[(i+o)*ns1+j+o]=(arr[i*s1+j]-min)*m;

      if(ob==0) return;
      for(i=0;i<ns0;i++)
	for(j=0;j<ns1;j++)
	    if(i<ob || i>=ns0-ob || j<ob || j>=ns1-ob) 
	      jsr[i*ns1+j]=UCHAR_MAX;
    }
  else
    {
      for(i=0;i<s0;i++)
	for(j=0;j<s1;j++)    
	  {
	    start=((i+o)*ns1+j+o)*4;
	    jsr[start+3]=UCHAR_MAX-(arr[i*s1+j]-min)*m;
	    jsr[start]=jsr[start+1]=jsr[start+2]=0;
	  }

      if(ob==0) return;
      for(i=0;i<ns0;i++)
	for(j=0;j<ns1;j++)
	    if(i<ob || i>=ns0-ob || j<ob || j>=ns1-ob) 
	      jsr[(i*ns1+j)*4+3]=UCHAR_MAX;
    }
}





/* Save a float array into a JPEG image. */
void
float2jpg(float *arr, size_t s0, size_t s1, struct a2jparams *p)
{
  /*size_t i;*/
  JSAMPLE *a;

  assert(p->color=='c' || p->color=='g');
  /*
  for(i=0;i<s0*s1;i++)
    arr[i]=i;
  */
  makejsample(&a, s0, s1, p);
  
  if(p->ibord==0 && p->obord==0)
    floatfilljsarr(a, arr, s0*s1, p->color, p->inv);
  else
    {
      floatfilljsarr_wbord(a, arr, s0, s1, p);
      s0+=2*(p->ibord+p->obord);
      s1+=2*(p->ibord+p->obord);
    }

  writeJSAMPLEtoJPEG(p, a, s0, s1);

  free(a); 
}
