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
#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>

#include "arr2jpg.h"
#include "stats.h"


/* Since these functions are so short and similar, the standard
   spacing: 5 lines between similar functions is abandoned in this
   file. */


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
 ***********    Find the minimum positive value    ***********
 *************************************************************/
#define SIMILARINMINPOS {                              \
    fpt=in+size;				       \
    for(;in<fpt;in++)				       \
      if(*in>0 && *in<tmin) tmin=*in;		       \
    *min=tmin;					       \
  }
void
shortminpos(short *in, size_t size, short *min)
{
  short tmin=SHRT_MAX, *fpt;
  SIMILARINMINPOS
}
void
longminpos(long *in, size_t size, long *min)
{
  long tmin=LONG_MAX, *fpt;
  SIMILARINMINPOS
}
void
floatminpos(float *in, size_t size, float *min)
{
  float tmin=MAXFD, *fpt;
  SIMILARINMINPOS
}
void
doubleminpos(double *in, size_t size, double *min)
{
  double tmin=MAXFD, *fpt;
  SIMILARINMINPOS
}



















/*************************************************************
 ***********        Converting pixel values        ***********
 *************************************************************/
#define SIMILARCONV {					   \
    struct conversion *t;				   \
    fpt=in+size;					   \
    for(t=p;t!=NULL;t=t->next)				   \
      {							   \
	from=t->from;					   \
	to=t->to;					   \
	pt=in;						   \
	do{if(*pt==from) *pt=to;} while(++pt<fpt);	   \
      }							   \
}
void
convuc(struct conversion *p, unsigned char *in, size_t size)
{
  unsigned char *pt, *fpt, from, to;
  SIMILARCONV;
}
void
convs(struct conversion *p, short *in, size_t size)
{
  short *pt, *fpt, from, to;
  SIMILARCONV;
}
void
convl(struct conversion *p, long *in, size_t size)
{
  long *pt, *fpt, from, to;
  SIMILARCONV;
}
void
convf(struct conversion *p, float *in, size_t size)
{
  float *pt, *fpt, from, to;
  SIMILARCONV;
}
void
convd(struct conversion *p, double *in, size_t size)
{
  double *pt, *fpt, from, to;
  SIMILARCONV;
}



















/*************************************************************
 ***********             Find the log              ***********
 *************************************************************/
/* Note that the logarithm of zero and negative values are
   not defined, so we find the minimum positive value in the
   array and set all zero and negative pixels to that value.*/
#define SIMILARLOG {                                      \
    forneg=logf(minpos);	                          \
    fpt=in+size;					  \
    do							  \
      {							  \
	if(*in>0)					  \
	  *in=logf(*in);				  \
	else						  \
	  *in=forneg;					  \
      }							  \
    while(++in<fpt);					  \
  }
void
ucarrlog(unsigned char *in, size_t size)
{
  unsigned char minpos=1, *fpt, forneg;
  SIMILARLOG
}
void
sarrlog(short *in, size_t size)
{
  short minpos, *fpt, forneg;
  shortminpos(in, size, &minpos);
  SIMILARLOG
}
void
larrlog(long *in, size_t size)
{
  long minpos, *fpt, forneg;
  longminpos(in, size, &minpos);
  SIMILARLOG
}
void
farrlog(float *in, size_t size)
{
  float minpos, *fpt, forneg;
  floatminpos(in, size, &minpos);
  minpos-=minpos*0.1;
  SIMILARLOG
}
void
darrlog(double *in, size_t size)
{
  double minpos, *fpt, forneg;
  doubleminpos(in, size, &minpos);
  minpos-=minpos*0.1;
  SIMILARLOG
}
