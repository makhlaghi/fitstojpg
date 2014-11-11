/*********************************************************************
FITStoJPG: Convert a FITS image to a JPEG image.

Copyright (C) 2014 Mohammad Akhlaghi
Tohoku University Astronomical Institute, Sendai, Japan.
http://astr.tohoku.ac.jp/~akhlaghi/

FITStoJPG is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

FITStoJPG is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with FITStoJPG. If not, see <http://www.gnu.org/licenses/>.
**********************************************************************/
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>

#include "config.h"
#include "arr2jpg.h"

#include "ui.h"			/* Needs arr2jpg.h          */
#include "argpparser.h"		/* Needs arr2jpg.h and ui.h */





/****************************************************************
 *****************      Checking functions     ******************
 ****************************************************************/
void
intelzero(char *optarg, int *var, char *lo, char so)
{
  long tmp;
  char *tailptr;
  tmp=strtol(optarg, &tailptr, 0);
  if(strlen(tailptr))
    {
      fprintf(stderr, PACKAGE": the argument to option `-%c`: `%s` was not "
	      "readable as a number!\n", so, optarg);
      exit(EXIT_FAILURE);
    }
  if(tmp<0)
    {
      fprintf(stderr, PACKAGE": argument to `--%s (-%c)` should be >=0, "
	      "it is: %ld\n", lo, so, tmp);
      exit(EXIT_FAILURE);
    }
  *var=tmp;  
}





void
intlzero(char *optarg, int *var, char *lo, char so)
{
  long tmp;
  char *tailptr;
  tmp=strtol(optarg, &tailptr, 0);
  if(strlen(tailptr))
    {
      fprintf(stderr, PACKAGE": the argument to option `-%c`: `%s` was not "
	      "readable as a number!\n", so, optarg);
      exit(EXIT_FAILURE);
    }
  if(tmp<=0)
    {
      fprintf(stderr, PACKAGE": argument to `--%s (-%c)` should be >0, "
	      "it is: %ld\n", lo, so, tmp);
      exit(EXIT_FAILURE);
    }
  *var=tmp;  
}





void
intl1(char *optarg, int *var, char *lo, char so)
{
  long tmp;
  char *tailptr;
  tmp=strtol(optarg, &tailptr, 0);
  if(strlen(tailptr))
    {
      fprintf(stderr, PACKAGE": the argument to option `-%c`: `%s` was not "
	      "readable as a number!\n", so, optarg);
      exit(EXIT_FAILURE);
    }
  if(tmp<1)
    {
      fprintf(stderr, PACKAGE": argument to `--%s (-%c)` should be >=1, "
	      "it is: %ld\n", lo, so, tmp);
      exit(EXIT_FAILURE);
    }
  *var=tmp;  
}





void
floatl0(char *optarg, float *var, char *lo, char so)
{
  float tmp;
  char *tailptr;
  tmp=strtof(optarg, &tailptr);
  if(strlen(tailptr))
    {
      fprintf(stderr, PACKAGE": the argument to option `-%c`: `%s` was not "
	     "readable as a number!\n", so, optarg);
      exit(EXIT_FAILURE);
    }
  if(tmp<=0)
    {
      fprintf(stderr, PACKAGE": argument to `--%s (-%c)` should be > 0, "
	      "but it is: %.3f\n", lo, so, tmp);
      exit(EXIT_FAILURE);      
    }
  *var=tmp;
}





void
intrange(char *optarg, int *var, char *lo, char so, int low, int high)
{
  long tmp;
  char *tailptr;
  tmp=strtol(optarg, &tailptr, 0);
  if(strlen(tailptr))
    {
      fprintf(stderr, PACKAGE": the argument to option `-%c`: `%s` was not "
	     "readable as a number!\n", so, optarg);
      exit(EXIT_FAILURE);
    }
  if(tmp<=low || tmp>high)
    {
      fprintf(stderr, PACKAGE": argument to `--%s (-%c)` should be >%d "
	      "and >=%d. It is: %ld\n", lo, so, low, high, tmp);
      exit(EXIT_FAILURE);
    }
  *var=tmp;  
}




void
anyfloat(char *optarg, float *var)
{
  char *tailptr;
  *var=strtof(optarg, &tailptr);
}




/* Check if the output image exists. If so, remove it. */
void
checkremoveoutimage(char *outname)
{
  FILE *tmpfile;
  if ((tmpfile = fopen(outname, "r")) != NULL) 
    {
      fclose(tmpfile);
      if(unlink(outname)==-1)
	{
	  fprintf(stderr, "'%s' already exists and could", outname); 
	  fprintf(stderr, " not be removed");
	  exit(EXIT_FAILURE);
	}
    }
}





/* Check if input image exists. */
void
checkinimage(char *inname)
{
  FILE *tmpfile;
  if ((tmpfile = fopen(inname, "r")) != NULL) 
    fclose(tmpfile);
  else
    {
      printf("\n\n\tError: %s does not exist\n\n", inname);
      exit(EXIT_FAILURE);
    }
}





void
findnamebase(char *inname, char **out)
{
  size_t i, l;
  char *base;

  l=strlen(inname);
  /* The 50 is added in case all extentions are requested,
     in which case a number will be added to the name and we 
     need this extra space!*/
  assert( (base=malloc((l+50)*sizeof *base))!=NULL );
  strcpy(base, inname);
  for(i=l;i!=0;i--)
    if(base[i]=='.')
      {
	base[i]='\0';
	break;
      }
  if(i==0)
    {
      printf("\n\n\tError: %s does not have a '.'\n\n", inname);
      exit(EXIT_FAILURE);
    }
  *out=base;
}





void
freeconvstruct(struct conversion *c)
{
  struct conversion *t, *tt;
  t=c;
  while(t!=NULL)
    {
      tt=t->next;
      free(t);
      t=tt;
    }
}





void
consistencycheck(struct a2jparams *p)
{    
  /* Check the lower and higher trunction values. */
  if(p->fluxlow>p->fluxhigh)
    {
      fprintf(stderr, PACKAGE": Lower (%f) > higher (%f).\n\n", 
	      p->fluxlow, p->fluxhigh);
      exit(EXIT_FAILURE);	    
    }
}


















/****************************************************************
 *****************        Read options:      ********************
 ****************************************************************/
struct conversion *
makeconvstruct(char *arg)
{
  char *p=arg;
  struct conversion *out=NULL, *c;

  while(*p!='\0')
    {
      assert( (c=malloc(sizeof *c))!=NULL);
      c->from=strtof(p, &p);
      if(*p==':') p++;
      else
	{
	  fprintf(stderr, PACKAGE": In the conversion option, [from] "
		  "and [to] values should be separated by a ':'. You "
		  "have given a '%c': %s\n", *p, arg);
	  exit(EXIT_FAILURE);
	}
      c->to=strtof(p, &p);
      if(*p==',') p++;
      else if(*p!='\0')
	{
	  fprintf(stderr, PACKAGE": In the conversion option, [from] "
		  "and [to] pairs should be separated by a ','. You have "
		  "provided a '%c': %s\n\n\n", *p, arg);
	  exit(EXIT_FAILURE);
	}
      c->next=out;
      out=c;
    }
  return out;
}





void
setparams(struct a2jparams *p, int argc, char *argv[])
{
  /* Default operating modes: */
  p->log          = 0;
  p->inv          = 1;
  p->allext       = 0;
  p->ttrunccolor  = 0;
  p->btrunccolor  = 0;
  p->convertfirst = 0;
  
  /* Default input FITS image parameters: */
  p->imgname      = NULL;
  p->imgext       = DP_IMGEXT_V;
  p->fluxlow      = DP_FLUXLOW_V;
  p->fluxhigh     = DP_FLUXHIGH_V;
  p->x1           = DP_Y1_V-1;
  p->y1           = DP_X1_V-1;
  p->x2           = DP_Y2_V-1;
  p->y2           = DP_X2_V-1;
  p->conv         = NULL;

  /* Default output JPEG image parameters: */
  p->outname      = NULL;
  p->quality      = DP_QUALITY_V;
  p->width        = DP_WIDTH_V;
  p->colormode    = DP_COLORMODE_V;
  p->maxjpg       = DP_MAXJPG_V;
  p->iborder      = DP_IBORDER_V;
  p->oborder      = DP_OBORDER_V;
  p->freeoutname  = 1;
  
  /* Read the arguments: */
  argp_parse(&argp, argc, argv, 0, 0, p);

  /* Check if the input values are consistent: */
  consistencycheck(p);

  /* If outname was not set, set it here. In case all extentions are
     wanted, then this job will be done else where. */
  if(p->freeoutname && p->allext==0)
    {
      findnamebase(p->imgname, &p->outname);
      strcat(p->outname, ".jpg");
    }
}




#if 0
/* Read all the options into the program */
void
getsaveoptions(struct a2jparams *p, int argc, char *argv[])
{
  int c, tmp;
  char *tailptr;

  setdefaultoptions(&in);	     /* ui.c */

  if(argc==1)
    printhelp(p);

  while( (c=getopt(argc, argv, 
		   "Chvltbanc:d:e:o:i:w:p:q:f:g:r:u:j:k:s:y:")) != -1 )
    switch(c)
      {
      case 'h':			/* Print help. */
	printhelp(p);
      case 'v':			/* Print version. */
	printversioninfo();
	exit(EXIT_SUCCESS);

      /* Options with no arguments: */
      case 'l':			/* Logarithmic scaling. */
	p->log=1;
	break;
      case 'a':			/* Convert all extentions. */
	p->allext=1;
	break;
      case 'n':			/* Logarithmic scaling. */
	p->inv=0;
	break;
      case 't':			/* Top truncation to max color. */
	p->ttrunccolor=1;
	break;
      case 'b':			/* Bottom truncation to min color. */
	p->btrunccolor=1;
	break;
      case 'C':			/* Bottom truncation to min color. */
	p->convertfirst=1;
	break;

      /* Options with arguments: */
      case 'i':			/* Input FITS image name. */
	p->inname=optarg;
	break;
      case 'e':			/* Extension of the FITS image. */
	checkint(optarg, &p->ext, c);
	break;
      case 'o': 		/* Output JPEG image name. */
	p->outname=optarg;
	p->freeoutname=0;
	break;
      case 'c':			/* Color scale. */
	p->colormode=*optarg;
	break;
      case 'u':			/* Quality of JPEG compression. */
	checkintlimit(optarg, &p->quality, c, 0, 100);
	break;
      case 'w':
	p->width=strtof(optarg, &tailptr);
	if(p->width<0)
	  {
	    fprintf(stderr, "Abort: Width ('-%c') is %f.\n\n", 
		    optopt, p->width);
	    exit(EXIT_FAILURE);	    
	  }
	break;
      case 'p':
	p->low=strtof(optarg, &tailptr);
	break;
      case 'q':
	p->high=strtof(optarg, &tailptr);
	break;
      case 'd':			/* Maximum byte value in JPEG  */
	checkintlimit(optarg, &tmp, c, 0, UCHAR_MAX);
	p->maxjpg=tmp;
	break;
      case 'f':			/* Inner border. */
	checkint(optarg, &p->iborder, c);
	break;
      case 'g':			/* Outer border. */
	checkint(optarg, &p->oborder, c);
	break;
      case 'r':			/* Convert pixel values */
	p->conv=makeconvstruct(optarg, c);
	break;
      case 'j':			/* Crop Bottom left corner x axis. */
	checkint(optarg, &tmp, c);
	p->y0=tmp-1;
	break;
      case 'k':			/* Crop Bottom left corner y axis. */
	checkint(optarg, &tmp, c);
	p->x0=tmp-1;
	break;
      case 's':			/* Crop Top right corner x axis. */
	checkint(optarg, &tmp, c);
	p->y1=tmp-1;
	break;
      case 'y':			/* Crop Top right corner y axis. */	
	checkint(optarg, &tmp, c);
	p->x1=tmp-1;
	break;
      case '?':
	fprintf(stderr, "\nUnknown option: '-%c'.\n\n", optopt);
	exit(EXIT_FAILURE);
      default:
	abort();
      }

  checkinimage(p->inname);
}
#endif
