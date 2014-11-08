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
#include <string.h>
#include <assert.h>
#include <jpeglib.h>


#include "config.h"
#include "arr2jpg.h"
#include "arraymanip.h"
#include "fitsarrayvv.h"

#include "ui.h"			/* Needs arr2jpg.h */
#include "main.h"		/* Needs arr2jpg.h */
#include "stats.h"		/* Needs arr2jpg.h */






int 
main(int argc, char *argv[])
{
  struct a2jparams in;

  setparams(&in, argc, argv);   /* ui.c */

  if(in.allext)
    convertallext(&in);		     /* below! */
  else
    convertoneext(&in);		     /* below! */

  if(in.freeoutname)
    free(in.outname);

  freeconvstruct(in.conv);	     /* ui.c  */

  return 0;
}





/* To only convert one extention in JPEG. */
void
convertoneext(struct a2jparams *p)
{
  void *arr;
  int bitpix;
  size_t s0, s1;

  fits_to_array(p->imgname, p->imgext, &bitpix, &arr, &s0, &s1);
  checkremoveoutimage(p->outname);   /* ui.c */
  if(p->x1!=p->x2 && p->y1!=p->y2)
    {
      shrinkarray(&arr, bitpix, s0, s1, p->x1, p->y1, p->x2, p->y2);
      if(arr==NULL) /* If the region is out of the image */
	{
	  fprintf(stderr, PACKAGE": the cropped region (%d, %d)-(%d,%d)"
		  "does not overlap with the image (%lu, %lu). No JPEG "
		  "image created", p->y1+1, p->x1+1, p->y2+1, p->x2+1,
		  s1, s0);
	  exit(EXIT_FAILURE);
	}
      s0=p->x2-p->x1;
      s1=p->y2-p->y1;
    }
  arr2jpg(arr, s0, s1, bitpix, p);   /* arr2jpg.c */
  
  free(arr);
}





/* To convert all extentions to JPEG. */
void
convertallext(struct a2jparams *p)
{
  char *base;
  int  i, numext;

  numextinfits(p->imgname, &numext);  /* fitsarrayvv.c */

  /* Check which name to use as base. */
  if(p->freeoutname==0)/* an outname is supplied. */
    findnamebase(p->outname, &base);
  else
    {
      /* Even though freeoutname was initially one, but it was not
	 allocated in ui.c. It will be allocated here and freed
	 here. */
      p->freeoutname=0;
      findnamebase(p->imgname, &base);  /* ui.c */
    }

  p->outname=malloc(strlen(base)*sizeof *(p->outname));
  assert(p->outname!=NULL);

  for(i=0;i<numext;i++)
    {
      p->imgext=i;
      sprintf(p->outname, "%s_%d.jpg", base, i+1);
      convertoneext(p);
    }
  
  free(p->outname);
  free(base);
}
