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
  JSAMPLE *jsarr, *fpt, *pt;

  if(sizeof *jsarr!=1)
    {
      printf("\n\nJSAMPLE has to be unsigned char!\n\n");
      exit(EXIT_FAILURE);
    }

  o=p->iborder*2+p->oborder*2;

  size=(s0+o)*(s1+o);
  if(p->colormode==CMYKCODE) size*=4;	/* For CMYK. */

  if(p->oborder+p->iborder && p->colormode==GRAYCODE)
    assert( (jsarr=calloc(size, sizeof *jsarr))!=NULL );
  else
    assert( (jsarr=malloc(size*sizeof *jsarr))!=NULL );

  if(p->colormode==CMYKCODE)
    {
      pt=jsarr;  fpt=jsarr+size;
      do
	*pt=UCHAR_MAX;
      while(++pt<fpt);
    }

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
  if(p->colormode==CMYKCODE)
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
  jpeg_set_quality(&cinfo, p->quality, TRUE);
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
 ***********     function body for all types       ***********
 *************************************************************/
/* 
   This only happens if ttrunccolor or btrunccolor are on.  In this
   case, the user has probably given truncation values lower and
   higher than the actual image range in order to set the color scale
   (make the image not have pure black or white).

   Note that because truncation was applied before this step,
   max<=p->fluxhigh and min>=p->low. So all we have to do is change their
   values to the user input high and low values.*/
#define ADJUSTMINMAXTRUNC {			                \
  if(p->fluxlow!=p->fluxhigh && p->ttrunccolor)		        \
    max=p->fluxhigh;						\
  if(p->fluxlow!=p->fluxhigh && p->btrunccolor)			\
    min=p->fluxlow;						\
}


#define FILLJSARRBODY {				                \
								\
    ADJUSTMINMAXTRUNC;						\
								\
    m=(double)maxjpg/((double)max-(double)min);			\
    if(p->colormode==GRAYCODE)					\
      {								\
	if(p->inv)						\
	  for(i=0;i<size;i++)					\
	    jsr[i]=maxjpg-(arr[i]-min)*m;			\
	else							\
	  for(i=0;i<size;i++)					\
	    jsr[i]=(arr[i]-min)*m;				\
      }								\
    else							\
      {								\
	if(p->inv)				                \
	  for(i=0;i<size;i++)			                \
	    {					                \
	      jsr[i*4+3]=maxjpg-(arr[i]-min)*m;			\
	      jsr[i*4]=jsr[i*4+1]=jsr[i*4+2]=UCHAR_MAX;	      	\
	    }							\
	else							\
	  for(i=0;i<size;i++)			                \
	    {					                \
	      jsr[i*4+3]=(arr[i]-min)*m;			\
	      jsr[i*4]=jsr[i*4+1]=jsr[i*4+2]=UCHAR_MAX;	        \
	    }					        	\
      }								\
  }                                             





#define FILLJSARRAYWITHBORDBODY {                               \
								\
    ib=p->iborder;						\
    ob=p->oborder;						\
    o=ib+ob;							\
    ns0=s0+2*o;							\
    ns1=s1+2*o;							\
								\
    ADJUSTMINMAXTRUNC;						\
								\
    m=(double)maxjpg/((double)max-(double)min);			\
                                                                \
    if(p->colormode==GRAYCODE)					\
      {								\
	if(p->inv)						\
	  for(i=0;i<s0;i++)					\
	    for(j=0;j<s1;j++)					\
	      jsr[(i+o)*ns1+j+o]=maxjpg-(arr[i*s1+j]-min)*m;	\
	else							\
	  for(i=0;i<s0;i++)					\
	    for(j=0;j<s1;j++)					\
	      jsr[(i+o)*ns1+j+o]=(arr[i*s1+j]-min)*m;		\
	/* Add border: */					\
	if(ob==0) return;					\
	for(i=0;i<ns0;i++)					\
	  for(j=0;j<ns1;j++)					\
	    if(i<ob || i>=ns0-ob || j<ob || j>=ns1-ob)          \
	      jsr[i*ns1+j]=UCHAR_MAX;                           \
      }								\
    else							\
      {								\
	if(p->inv)						\
	  for(i=0;i<s0;i++)					\
	    for(j=0;j<s1;j++)					\
	      {							\
		start=((i+o)*ns1+j+o)*4;			\
		jsr[start+3]=maxjpg-(arr[i*s1+j]-min)*m;	\
	      }							\
	else							\
	  for(i=0;i<s0;i++)					\
	    for(j=0;j<s1;j++)					\
	      {							\
		start=((i+o)*ns1+j+o)*4;			\
		jsr[start+3]=(arr[i*s1+j]-min)*m;		\
	      }							\
	/* Add border: */					\
	if(ob==0) return;					\
	for(i=0;i<ns0;i++)					\
	  for(j=0;j<ns1;j++)					\
	    if( (i>=ob && i<o) || (i>=ns0-o && i<ns0-ob) ||	\
		(j>=ob && j<o) || (j>=ns1-o && j<ns1-ob) )	\
	      if(i>=ob && i<ns0-ob && j>=ob && j<ns1-ob)	\
		jsr[(i*ns1+j)*4+3]=0;				\
      }								\
  }




















/*************************************************************
 ***********         Functions for all types       ***********
 *************************************************************/
void
bytefilljsarr(JSAMPLE *jsr, unsigned char *arr, size_t s0, size_t s1, 
	      struct a2jparams *p)
{
  double m;
  size_t size, ib, ob;
  unsigned char min, max;
  unsigned char maxjpg=p->maxjpg;
  size_t i, j, start, o, ns0, ns1;

  ucminmax(arr, s0*s1, &min, &max);

  size=s0*s1;
  if(p->iborder==0 && p->oborder==0)
    {FILLJSARRBODY}
  else
    {FILLJSARRAYWITHBORDBODY}
}





void
shortfilljsarr(JSAMPLE *jsr, short *arr, size_t s0, size_t s1, 
	      struct a2jparams *p)
{
  double m;
  short min, max;
  size_t size, ib, ob;
  unsigned char maxjpg=p->maxjpg;
  size_t i, j, start, o, ns0, ns1;

  shortminmax(arr, s0*s1, &min, &max);

  size=s0*s1;
  if(p->iborder==0 && p->oborder==0)
    {FILLJSARRBODY}
  else
    {FILLJSARRAYWITHBORDBODY}
}





void
longfilljsarr(JSAMPLE *jsr, long *arr, size_t s0, size_t s1, 
	      struct a2jparams *p)
{
  double m;
  long min, max;
  size_t size, ib, ob;
  unsigned char maxjpg=p->maxjpg;
  size_t i, j, start, o, ns0, ns1;

  longminmax(arr, s0*s1, &min, &max);

  size=s0*s1;
  if(p->iborder==0 && p->oborder==0)
    {FILLJSARRBODY}
  else
    {FILLJSARRAYWITHBORDBODY}
}





void
floatfilljsarr(JSAMPLE *jsr, float *arr, size_t s0, size_t s1, 
		 struct a2jparams *p)
{
  double m;
  float min, max;
  size_t size, ib, ob;
  unsigned char maxjpg=p->maxjpg;
  size_t i, j, start, o, ns0, ns1;

  floatminmax(arr, s0*s1, &min, &max);

  size=s0*s1;
  if(p->iborder==0 && p->oborder==0)
    {FILLJSARRBODY}
  else
    {FILLJSARRAYWITHBORDBODY}
}





void
doublefilljsarr(JSAMPLE *jsr, double *arr, size_t s0, size_t s1, 
		 struct a2jparams *p)
{
  double m;
  double min, max;
  size_t size, ib, ob;
  unsigned char maxjpg=p->maxjpg;
  size_t i, j, start, o, ns0, ns1;

  doubleminmax(arr, s0*s1, &min, &max);

  size=s0*s1;
  if(p->iborder==0 && p->oborder==0)
    {FILLJSARRBODY}
  else
    {FILLJSARRAYWITHBORDBODY}
}




















/*************************************************************
 ***********             Main functions            ***********
 *************************************************************/
/* Save a float array into a JPEG image. */
void
arr2jpg(void *arr, size_t s0, size_t s1, int bitpix, 
	struct a2jparams *p)
{
  JSAMPLE *jsr;
  
  assert(p->colormode==CMYKCODE || p->colormode==GRAYCODE);
 
  makejsample(&jsr, s0, s1, p);
  
  switch(bitpix)
    {
    case BYTE_IMG:
      if(p->convertfirst)
	{
	  if(p->conv!=NULL) convuc(p->conv, arr, s0*s1);
	  if(p->fluxlow<p->fluxhigh)
	    truncucarray(arr, s0*s1, p->fluxlow, p->fluxhigh);
	}
      else
	{
	  if(p->fluxlow<p->fluxhigh)
	    truncucarray(arr, s0*s1, p->fluxlow, p->fluxhigh);
	  if(p->conv!=NULL) convuc(p->conv, arr, s0*s1);
	}
      if(p->log) ucarrlog(arr, s0*s1);
      bytefilljsarr(jsr, arr, s0, s1, p);
      break;
    case SHORT_IMG:
      if(p->convertfirst)
	{
	  if(p->conv!=NULL) convs(p->conv, arr, s0*s1);
	  if(p->fluxlow<p->fluxhigh)
	    truncsarray(arr, s0*s1, p->fluxlow, p->fluxhigh);
	}
      else
	{
	  if(p->fluxlow<p->fluxhigh)
	    truncsarray(arr, s0*s1, p->fluxlow, p->fluxhigh);
	  if(p->conv!=NULL) convs(p->conv, arr, s0*s1);
	}
      if(p->log) sarrlog(arr, s0*s1);
      shortfilljsarr(jsr, arr, s0, s1, p);
      break;
    case LONG_IMG:
      if(p->convertfirst)
	{
	  if(p->conv!=NULL) convl(p->conv, arr, s0*s1);
	  if(p->fluxlow<p->fluxhigh)
	    trunclarray(arr, s0*s1, p->fluxlow, p->fluxhigh);
	}
      else
	{
	  if(p->fluxlow<p->fluxhigh)
	    trunclarray(arr, s0*s1, p->fluxlow, p->fluxhigh);
	  if(p->conv!=NULL) convl(p->conv, arr, s0*s1);
	}
      if(p->log) larrlog(arr, s0*s1);
      longfilljsarr(jsr, arr, s0, s1, p);
      break;
    case FLOAT_IMG:
      if(p->convertfirst)
	{
	  if(p->conv!=NULL) convf(p->conv, arr, s0*s1);
	  if(p->fluxlow<p->fluxhigh)
	    truncfarray(arr, s0*s1, p->fluxlow, p->fluxhigh);
	}
      else
	{
	  if(p->fluxlow<p->fluxhigh)
	    truncfarray(arr, s0*s1, p->fluxlow, p->fluxhigh);
	  if(p->conv!=NULL) convf(p->conv, arr, s0*s1);
	}
      if(p->log) farrlog(arr, s0*s1);
      floatfilljsarr(jsr, arr, s0, s1, p);
      break;
    case DOUBLE_IMG:
      if(p->convertfirst)
	{
	  if(p->conv!=NULL) convd(p->conv, arr, s0*s1);
	  if(p->fluxlow<p->fluxhigh)
	    truncdarray(arr, s0*s1, p->fluxlow, p->fluxhigh);
	}
      else
	{
	  if(p->fluxlow<p->fluxhigh)
	    truncdarray(arr, s0*s1, p->fluxlow, p->fluxhigh);
	  if(p->conv!=NULL) convd(p->conv, arr, s0*s1);
	}
      if(p->log) darrlog(arr, s0*s1);
      doublefilljsarr(jsr, arr, s0, s1, p);
      break;
    case LONGLONG_IMG:
      printf("\n\n%s. BITPIX=%d (long long) Not supported!\n\n",
	     p->imgname, bitpix);
      exit(EXIT_FAILURE);
    default:
      printf("\n\n%s. BITPIX=%d, Not recognized!\n", 
	     p->imgname, bitpix);
      printf("\tAcceptable values are: %d, %d, %d, %d, %d, %d\n",
	     BYTE_IMG, SHORT_IMG, LONG_IMG, FLOAT_IMG, 
	     DOUBLE_IMG, LONGLONG_IMG);
      printf("\tSee the CFITSIO C programmer reference guide.\n\n");
      exit(EXIT_FAILURE);
    }

  if(p->iborder!=0 || p->oborder!=0)
    {
      s0+=2*(p->iborder+p->oborder);
      s1+=2*(p->iborder+p->oborder);
    }

  writeJSAMPLEtoJPEG(p, jsr, s0, s1);

  free(jsr); 
}
