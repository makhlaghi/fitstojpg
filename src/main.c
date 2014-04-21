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
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <jpeglib.h>

#include "arr2jpg.h"
#include "ui.h"
#include "stats.h"
#include "main.h"
#include "fitsarrayvv.h"





int 
main(int argc, char *argv[])
{
  struct a2jparams in;

  setdefaultoptions(&in);	     /* ui.c */

  getsaveoptions(&in, argc, argv);   /* ui.c */
  
  checkinimage(in.inname);	     /* ui.c */

  if(in.allext)
    convertallext(&in);		     /* below! */
  else
    convertoneext(&in);		     /* below! */

  if(in.freeoutname)
    free(in.outname);

  return 0;
}





void
convertoneext(struct a2jparams *p)
{
  void *arr;
  int bitpix;
  size_t s0, s1;

  fits_to_array(p->inname, p->ext, &bitpix, &arr, &s0, &s1);
  checkremoveoutimage(p->outname);
  arr2jpg(arr, s0, s1, bitpix, p);
  
  free(arr);
}





void
convertallext(struct a2jparams *p)
{
  char *base;
  int  i, numext;

  numextinfits(p->inname, &numext);

  /* Check which name to use as base. */
  if(p->freeoutname==0)/* an outname is supplied. */
    findnamebase(p->outname, &base);
  else
    {
      /* Even though freeoutname was initially one, but it was not
	 allocated in ui.c. It will be allocated here and freed
	 here. */
      p->freeoutname=0;
      findnamebase(p->inname, &base);
    }

  p->outname=malloc(strlen(base)*sizeof *(p->outname));
  assert(p->outname!=NULL);

  for(i=0;i<numext;i++)
    {
      p->ext=i;
      sprintf(p->outname, "%s_%d.jpg", base, i+1);
      convertoneext(p);
    }
  
  free(p->outname);
  free(base);
}
