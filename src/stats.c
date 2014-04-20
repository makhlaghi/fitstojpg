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
#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>

#include "arr2jpg.h"
#include "stats.h"


#define SIMILARINMIN {     \
  for(;in<fpt;in++)        \
    if(*in<tmin) tmin=*in; \
  *min=tmin;               \
  }

void
ucharmin(unsigned char *in, size_t size, int *min)
{
  unsigned char tmin=UCHAR_MAX, *fpt;
  fpt=in+size;
  SIMILARINMIN
}





void
shortmin(short *in, size_t size, short *min)
{
  short tmin=SHRT_MAX, *fpt;
  fpt=in+size;
  SIMILARINMIN
}





void
longmin(long *in, size_t size, long *min)
{
  long tmin=LONG_MAX, *fpt;
  fpt=in+size;
  SIMILARINMIN
}




void
floatmin(float *in, size_t size, float *min)
{
  float tmin=MAXFD, *fpt;
  fpt=in+size;
  SIMILARINMIN
}





void
doublemin(double *in, size_t size, double *min)
{
  double tmin=MAXFD, *fpt;
  fpt=in+size;
  SIMILARINMIN
}




















/*************************************************************
 ***********    Finding the minimum and maximum    ***********
 *************************************************************/
#define SIMILARMINMAX {        \
  fpt=in+size;                 \
  do                           \
    {                          \
      if(*in>tmax) tmax=*in;   \
      if(*in<tmin) tmin=*in;   \
    }                          \
  while (++in<fpt);            \
  *max=tmax;                   \
  *min=tmin;                   \
  }

void
ucminmax(unsigned char *in, size_t size, unsigned char *min, 
	 unsigned char *max)
{
  unsigned char tmin=UCHAR_MAX, tmax=0, *fpt;
  SIMILARMINMAX
}





void
shortminmax(short *in, size_t size, short *min, short *max)
{
  short tmin=SHRT_MAX, tmax=SHRT_MIN, *fpt;
  SIMILARMINMAX
}





void
longminmax(long *in, size_t size, long *min, long *max)
{
  long tmin=LONG_MAX, tmax=LONG_MIN, *fpt;
  SIMILARMINMAX
}





void
floatminmax(float *in, size_t size, float *min, float *max)
{
  float tmin=MAXFD, tmax=MINFD, *fpt;
  SIMILARMINMAX
}





void
doubleminmax(double *in, size_t size, double *min, double *max)
{
  double tmin=MAXFD, tmax=MINFD, *fpt;
  SIMILARMINMAX
}




















/*************************************************************
 ***********         Truncate the arrays           ***********
 *************************************************************/
#define SIMILARTRUNCATE {         \
  assert(low<high);               \
  fpt=in+size;                    \
  do                              \
    {                             \
      if(*in>high) *in=high;      \
      else if(*in<low) *in=low;   \
    }                             \
  while(++in<fpt);                \
  }

void 
truncucarray(unsigned char *in, size_t size, unsigned char low, 
	     unsigned char high)
{
  unsigned char *fpt;
  SIMILARTRUNCATE
}





void 
truncsarray(short *in, size_t size, short low, short high)
{
  short *fpt;
  SIMILARTRUNCATE
}





void 
trunclarray(long *in, size_t size, long low, long high)
{
  long *fpt;
  SIMILARTRUNCATE
}





void 
truncfarray(float *in, size_t size, float low, float high)
{
  float *fpt;
  SIMILARTRUNCATE
}





void 
truncdarray(double *in, size_t size, double low, double high)
{
  double *fpt;
  SIMILARTRUNCATE
}




















/*************************************************************
 ***********             Find the log              ***********
 *************************************************************/
#define SIMILARLOG {                 \
  fpt=in+size;                       \
  do                                 \
    *in=logf(*in-min);               \
  while(++in<fpt);                   \
  if(p->low<p->high)                 \
    {                                \
      p->low=logf(p->low-min);       \
      p->high=logf(p->high-min);     \
    }                                \
  }

void
ucarrlog(unsigned char *in, size_t size, struct a2jparams *p)
{
  int min;
  unsigned char *fpt;

  ucharmin(in, size, &min);
  if(min==0) min=-1;  /* So we don't have log(0) */
  SIMILARLOG
}





void
sarrlog(short *in, size_t size, struct a2jparams *p)
{
  short min, *fpt;

  shortmin(in, size, &min);
  min-=1; /* So we don't have log(0) */
  SIMILARLOG
}





void
larrlog(long *in, size_t size, struct a2jparams *p)
{
  long min, *fpt;

  longmin(in, size, &min);
  min-=1; /* So we don't have log(0) */
  SIMILARLOG
}





void
farrlog(float *in, size_t size, struct a2jparams *p)
{
  float min, *fpt;

  floatmin(in, size, &min);
  min-=-0.0001*min; /* So we don't calculate log(0). */
  SIMILARLOG
}





void
darrlog(double *in, size_t size, struct a2jparams *p)
{
  double min, *fpt;

  doublemin(in, size, &min);
  min-=-0.0001*min; /* So we don't calculate log(0). */
  SIMILARLOG
}
