/*********************************************************************
mockgals - Make mock astronomical profiles (galaxy, star, ...) 
           in a FITS file

Copyright (C) 2014 Mohammad Akhlaghi
Tohoku University Astronomical Institute, Sendai, Japan.
http://astr.tohoku.ac.jp/~akhlaghi/

mockgals is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

mockgals is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with mockgals. If not, see <http://www.gnu.org/licenses/>.

**********************************************************************/
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>

#include "arr2jpg.h"
#include "main.h"
#include "ui.h"





/****************************************************************
 *****************     Small functions used    ******************
 *********************      in main()      **********************
 ****************************************************************/
/* Set the default values for the inputs */
void
setdefaultoptions(struct a2jparams *p)
{
  p->log=0;
  p->inv=1;   /* Invert greyscale image by default. */
  p->allext=0;

  p->inname="a.fits";
  p->freeoutname=1;  /* We'll assume the user doesn't give any */
  p->color='g';
  p->ext=0;
  p->width=5.0f;
  p->low=0.0f;
  p->high=0.0f;
  p->ibord=1;
  p->obord=1;
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



















/****************************************************************
 *****************        Read options:      ********************
 ****************************************************************/
/* Check if an integer input is positive. */
void
checkint(char *optarg, int *var, int opt)
{
  long tmp;
  char *tailptr;
  tmp=strtol(optarg, &tailptr, 0);
  if(tmp<0)
    {
      printf("\n\n Error: argument to -%c ", opt); 
      printf("should be positive\n\n");
      exit(EXIT_FAILURE);
    }
  *var=tmp;  
}




/* Print the help menu. */
void
printhelp(struct a2jparams *p)
{
  printf("\n\nfits2jpg %.1f\n", FITS2JPGVERSION);
  printf("============\n");
  printf("Convert a FITS image to a grayscale or CMYK JPEG image.\n");
  printf("\nCopyright (C) 2014  Mohammad Akhlaghi\n");
  printf("This program comes with ABSOLUTELY NO WARRANTY.\n");
  printf("This is free software, and you are welcome to\n");
  printf("redistribute it under the ");
  printf("GNU Public License v3 or later.\n\n\n");

  printf("####### Options that won't run 'fits2jpg'.\n");
  printf(" -h:\n\tPrint this command and abort.\n\n\n");

  printf("####### Options without arguments (On or Off):\n");
  printf("By default all are off\n");
  printf(" -n:\n\tDon't inverse greyscale image.\n");
  printf("\tBy default all images are inversed:\n");
  printf("\tdarker pixel value means larger values.\n");
  printf("\tWe feel it is easier to the eyes like this.\n\n");

  printf(" -a:\n\tConvert all extentions to JPEG.\n\n");

  printf(" -l:\n\tLogarithmic scaling.\n\n\n");

  printf("####### Options with arguments:\n");
  printf(" -i FILENAME:\n\tInput FITS image name.\n");
  printf("\tdefault: '%s'\n\n", p->inname);

  printf(" -e INTEGER:\n\tFITS extention\n");
  printf("\tdefault: %d\n\n", p->ext);

  printf(" -o FILENAME:\n\tOutput JPG image name\n");
  printf("\tdefault: 'base.jpg', when input is 'base.fits'.\n\n");

  printf(" -w FLOAT:\n\tOutput JPG width in centimeters.\n");
  printf("\tdefault: %.3fcm\n\n", p->width);

  printf(" -c CHARACTER:\n\tColor mode:\n");
  printf("\t\tc: CMYK (32bit per pixel) gray).\n");
  printf("\t\tg: Gray scale image (8 bit pixels).\n");
  printf("\tdefault: %c\n\n", p->color);

  printf(" -p FLOAT:\n\tLower pixel value truncation.\n");
  printf("\tIf equal to higher, no truncation.\n");
  printf("\tdefault: %f\n\n", p->low);

  printf(" -q FLOAT:\n\tHigher pixel value truncation.\n");
  printf("\tIf equal to lower, no truncation.\n");
  printf("\tdefault: %f\n\n", p->high);

  printf(" -f INTEGER:\n\tInner border width\n");
  printf("\tdefault: %d\n\n", p->ibord);

  printf(" -g INTEGER:\n\tOuter border width\n");
  printf("\tdefault: %d\n\n", p->obord);

  exit(EXIT_SUCCESS);
}





/* Read all the options into the program */
void
getsaveoptions(struct a2jparams *p, int argc, char *argv[])
{
  int c;
  char *tailptr;

  while( (c=getopt(argc, argv, "lhanc:e:o:i:w:p:q:f:g:")) != -1 )
    switch(c)
      {
      /* Options with no arguments: */
      case 'l':			/* Logarithmic scaling. */
	p->log=1;
	break;
      case 'h':			/* Print help. */
	printhelp(p);
      case 'a':			/* Convert all extentions. */
	p->allext=1;
	break;
      case 'n':			/* Logarithmic scaling. */
	p->inv=0;
	break;

      /* Options with arguments: */
      case 'i':			/* Input FITS image name. */
	p->inname=optarg;
	break;
      case 'o': 		/* Output JPEG image name. */
	p->outname=optarg;
	p->freeoutname=0;
	break;
      case 'c':			/* Color scale. */
	p->color=*optarg;
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
      case 'e':			/* Extension of the FITS image. */
	checkint(optarg, &p->ext, c);
	break;
      case 'f':			/* Inner border. */
	checkint(optarg, &p->ibord, c);
	break;
      case 'g':			/* Outer border. */
	checkint(optarg, &p->obord, c);
	break;
      case '?':
	fprintf(stderr, "Unknown option: '-%c'.\n\n", optopt);
	exit(EXIT_FAILURE);
      default:
	abort();
      }

  /* If outname was not set, set it here. In case all extentions are
     wanted, then this job will be done else where. */
  if(p->freeoutname==1 && p->allext==0)
    {
      findnamebase(p->inname, &p->outname);
      strcat(p->outname, ".jpg");
    }
    
  /* Check the lower and higher trunction values. */
  if(p->low>p->high)
    {
      fprintf(stderr, "Abort: Lower (%f) > higher (%f).\n\n", 
	      p->low, p->high);
      exit(EXIT_FAILURE);	    
    }
}
