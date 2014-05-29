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
#include <stdlib.h>
#include <assert.h>

#include "arraymanip.h"
#include "fitsarrayvv.h"





/* Check to see if a box defined by the two points (x1,y1) and (x2,y2)
   is inside an array of size size1 and size2. If it doesn't overlap,
   then x1=x2 and y1=y2.*/
void
checkifinarray(int *x1, int *y1, int *x2, int *y2, int s0, int s1)
{
  int temp;
  if(*x1==*x2 && *y1==*y2) return;        

  if(*x2<*x1){temp=*x1;*x1=*x2;*x2=temp;} 
  if(*y2<*y1){temp=*y1;*y1=*y2;*y2=temp;}

  if(*x1<0) *x1=0;    if(*x1>s0) *x1=s0;
  if(*y1<0) *y1=0;    if(*y1>s1) *y1=s1;
  if(*x2<0) *x2=0;    if(*x2>s0) *x2=s0;
  if(*y2<0) *y2=0;    if(*y2>s1) *y2=s1;
}





/* We have a large array of size (size1*size2). We want to shrink this
    array, such that (x1,y1) comes down to point (0,0) and the new
    array now only extends to the old (x2,y2). So the size of the new
    array is: w1*w2 where w1=x2-x1 and w2=y2-y1. 

    If the desired region is totally out of the array, a NULL pointer
    is returned.*/
void
ucharshrinkarray(unsigned char **in, int size1, int size2,
        int x1, int y1, int x2, int y2)
{
  size_t i, ux1, uy1, us2, w1, w2;
  unsigned char *ifpt, *ofpt, *rowstart;

  checkifinarray(&x1, &y1, &x2, &y2, size1, size2);
  if(x1==x2 || y1==y2) 		/* The required region does not */
    {				/* overlap with the array. */
      free(*in);
      *in=NULL;
      return;
    }
  /* The region covers the whole image, no need for the next step. */
  if(x1==0 && y1==0 && x2==size1 && y2==size2) return;

  w1=x2-x1;  w2=y2-y1;
  ux1=x1; uy1=y1; us2=size2;  /* The inputs are int (can be negative,
				 which is allowed: will become zero).
				 but pointers are unsigned, so to 
				 faciliate the process in the loop, 
				 they are converted to size_t. */
  for(i=0;i<w1;i++)
    {
      ofpt=rowstart=*in+i*w2;
      ifpt=*in+(ux1+i)*us2+uy1;
      while(ofpt<rowstart+w2)
	*ofpt++=*ifpt++;
 
    }      
  *in=(unsigned char *)realloc(*in, w1*w2*sizeof(unsigned char));
  assert(*in!=NULL);    
}





void
shortshrinkarray(short **in, int size1, int size2,
        int x1, int y1, int x2, int y2)
{
  short *ifpt, *ofpt, *rowstart;
  size_t i, ux1, uy1, us2, w1, w2;

  checkifinarray(&x1, &y1, &x2, &y2, size1, size2);
  if(x1==x2 || y1==y2) 		/* The required region does not */
    {				/* overlap with the array. */
      free(*in);
      *in=NULL;
      return;
    }
  /* The region covers the whole image, no need for the next step. */
  if(x1==0 && y1==0 && x2==size1 && y2==size2) return;

  w1=x2-x1;  w2=y2-y1;
  ux1=x1; uy1=y1; us2=size2;  /* The inputs are int (can be negative,
				 which is allowed: will become zero).
				 but pointers are unsigned, so to 
				 faciliate the process in the loop, 
				 they are converted to size_t. */
  for(i=0;i<w1;i++)
    {
      ofpt=rowstart=*in+i*w2;
      ifpt=*in+(ux1+i)*us2+uy1;
      while(ofpt<rowstart+w2)
	*ofpt++=*ifpt++;
 
    }      
  *in=(short *)realloc(*in, w1*w2*sizeof(short));
  assert(*in!=NULL);    
}





void
longshrinkarray(long **in, int size1, int size2,
        int x1, int y1, int x2, int y2)
{
  long *ifpt, *ofpt, *rowstart;
  size_t i, ux1, uy1, us2, w1, w2;

  checkifinarray(&x1, &y1, &x2, &y2, size1, size2);
  if(x1==x2 || y1==y2) 		/* The required region does not */
    {				/* overlap with the array. */
      free(*in);
      *in=NULL;
      return;
    }
  /* The region covers the whole image, no need for the next step. */
  if(x1==0 && y1==0 && x2==size1 && y2==size2) return;

  w1=x2-x1;  w2=y2-y1;
  ux1=x1; uy1=y1; us2=size2;  /* The inputs are int (can be negative,
				 which is allowed: will become zero).
				 but pointers are unsigned, so to 
				 faciliate the process in the loop, 
				 they are converted to size_t. */
  for(i=0;i<w1;i++)
    {
      ofpt=rowstart=*in+i*w2;
      ifpt=*in+(ux1+i)*us2+uy1;
      while(ofpt<rowstart+w2)
	*ofpt++=*ifpt++;
 
    }      
  *in=(long *)realloc(*in, w1*w2*sizeof(long));
  assert(*in!=NULL);    
}





void
floatshrinkarray(float **in, int size1, int size2,
        int x1, int y1, int x2, int y2)
{
  float *ifpt, *ofpt, *rowstart;
  size_t i, ux1, uy1, us2, w1, w2;

  checkifinarray(&x1, &y1, &x2, &y2, size1, size2);
  if(x1==x2 || y1==y2) 		/* The required region does not */
    {				/* overlap with the array. */
      free(*in);
      *in=NULL;
      return;
    }
  /* The region covers the whole image, no need for the next step. */
  if(x1==0 && y1==0 && x2==size1 && y2==size2) return;

  w1=x2-x1;  w2=y2-y1;
  ux1=x1; uy1=y1; us2=size2;  /* The inputs are int (can be negative,
				 which is allowed: will become zero).
				 but pointers are unsigned, so to 
				 faciliate the process in the loop, 
				 they are converted to size_t. */
  for(i=0;i<w1;i++)
    {
      ofpt=rowstart=*in+i*w2;
      ifpt=*in+(ux1+i)*us2+uy1;
      while(ofpt<rowstart+w2)
	*ofpt++=*ifpt++;
 
    }      
  *in=(float *)realloc(*in, w1*w2*sizeof(float));
  assert(*in!=NULL);    
}





void
doubleshrinkarray(double **in, int size1, int size2,
        int x1, int y1, int x2, int y2)
{
  double *ifpt, *ofpt, *rowstart;
  size_t i, ux1, uy1, us2, w1, w2;

  checkifinarray(&x1, &y1, &x2, &y2, size1, size2);
  if(x1==x2 || y1==y2) 		/* The required region does not */
    {				/* overlap with the array. */
      free(*in);
      *in=NULL;
      return;
    }
  /* The region covers the whole image, no need for the next step. */
  if(x1==0 && y1==0 && x2==size1 && y2==size2) return;

  w1=x2-x1;  w2=y2-y1;
  ux1=x1; uy1=y1; us2=size2;  /* The inputs are int (can be negative,
				 which is allowed: will become zero).
				 but pointers are unsigned, so to 
				 faciliate the process in the loop, 
				 they are converted to size_t. */
  for(i=0;i<w1;i++)
    {
      ofpt=rowstart=*in+i*w2;
      ifpt=*in+(ux1+i)*us2+uy1;
      while(ofpt<rowstart+w2)
	*ofpt++=*ifpt++;
 
    }      
  *in=(double *)realloc(*in, w1*w2*sizeof(double));
  assert(*in!=NULL);    
}





void
shrinkarray(void **in, int bitpix, int size1, int size2,
	    int x1, int y1, int x2, int y2)
{
  unsigned char **u; short **s; long **l;
  float **f; double **d;
  switch(bitpix)
    {
    case BYTE_IMG:
      u=(unsigned char **)in;	/* To stop warnings! */
      ucharshrinkarray(u, size1, size2, x1, y1, x2, y2);
      break;

    case SHORT_IMG:
      s=(short **)in;
      shortshrinkarray(s, size1, size2, x1, y1, x2, y2);
      break;

    case LONG_IMG:
      l=(long **)in;
      longshrinkarray(l, size1, size2, x1, y1, x2, y2);
      break;

    case FLOAT_IMG:
      f=(float **)in;
      floatshrinkarray(f, size1, size2, x1, y1, x2, y2);
      break;

    case DOUBLE_IMG:
      d=(double **)in;
      doubleshrinkarray(d, size1, size2, x1, y1, x2, y2);
      break;

    case LONGLONG_IMG:
      printf("\n\nBITPIX=%d (long long) Not supported!\n\n", bitpix);
      exit(EXIT_FAILURE);

    default:
      printf("\n\nBITPIX=%d, Not recognized!\n\n", bitpix);
      exit(EXIT_FAILURE);
    }  
}









