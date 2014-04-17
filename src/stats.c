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

#include "arr2jpg.h"
#include "stats.h"




void
floatmin(float *in, size_t size, float *min)
{
  float tmin=MAXFD, *fpt;
  fpt=in+size;
  for(;in<fpt;in++)
    if(*in<tmin) tmin=*in;
  *min=tmin;
}





/* Find the minimum and maximum values in a float array. */
void
fminmax(float *in, size_t size, float *min, float *max)
{
  float tmin=MAXFD, tmax=MINFD, *pt=in, *fpt;
  fpt=in+size;
  for(;pt<fpt;pt++) 
    {
      if(*pt>tmax) tmax=*pt;
      else if(*pt<tmin) tmin=*pt;
    }
  *max=tmax;    
  *min=tmin;    
}





void 
truncfarray(float *in, size_t size, float low, float high)
{
  float *fpt;
  assert(low<high);

  fpt=in+size;    
  for(;in<fpt;in++)
    {
      if(*in>high) *in=high;
      else if(*in<low) *in=low;
    }
}





void
farrlog(float *in, size_t size, struct a2jparams *p)
{
  float min, *fpt;

  floatmin(in, size, &min);
  min-=-0.0001*min; /* So we don't calculate log(0). */

  fpt=in+size;
  do
    *in=logf(*in-min);
  while(++in<fpt);

  if(p->low<p->high)
    {
      p->low=logf(p->low-min);
      p->high=logf(p->high-min);
    }
}
