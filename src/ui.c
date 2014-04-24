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
  /* On/Off options: */
  p->log         =0;
  p->inv         =1; 
  p->allext      =0;
  p->ttrunccolor =0;
  p->btrunccolor =0;

  /* Options with arguments. */
  p->inname      ="a.fits";
  p->color       ='c';
  p->quality     =100;
  p->ext         =0;
  p->width       =5.0f;
  p->low         =0.0f;
  p->high        =0.0f;
  p->ibord       =1;
  p->obord       =1;
  p->conv        =NULL;

  /* For internal use: */
  p->freeoutname =1;  /* We'll assume the user doesn't give any */
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





void
checkintlimit(char *optarg, int *var, int opt, 
	      int llimit, int hlimit)
{
  long tmp;
  char *tailptr;
  tmp=strtol(optarg, &tailptr, 0);
  if(tmp<llimit)
    {
      printf("\n\n Error: argument to -%c ", opt); 
      printf("should be larger than %d\n\n", llimit);
      exit(EXIT_FAILURE);
    }
  if(tmp>hlimit)
    {
      printf("\n\n Error: argument to -%c ", opt); 
      printf("should be smaller than %d\n\n", hlimit);
      exit(EXIT_FAILURE);
    }
  *var=tmp;  
}





void
printversioninfo()
{
  printf("\n\nfits2jpg %.1f\n", FITS2JPGVERSION);
  printf("============\n");
  printf("Convert a FITS image to a grayscale or CMYK JPEG image.\n");
  printf("\nCopyright (C) 2014  Mohammad Akhlaghi\n");
  printf("This program comes with ABSOLUTELY NO WARRANTY.\n");
  printf("This is free software, and you are welcome to\n");
  printf("redistribute it under the ");
  printf("GNU Public License v3 or later.\n\n\n");
}





/* Print the help menu. */
void
printhelp(struct a2jparams *p)
{
  printversioninfo();
  printf("####### Options that won't run 'fits2jpg'.\n");
  printf(" -h:\tPrint this command and abort.\n\n");
  printf(" -v:\tPrint only version and copyright information.\n\n\n");

  printf("####### Options without arguments (On or Off):\n");
  printf("By default all are off\n");
  printf(" -n:\tDon't inverse the image.\n");
  printf("\tBy default all images are inverted:\n");
  printf("\ta larger pixel value is translated to darker colors.\n");
  printf("\tThis is better for Astronomical objects with \n");
  printf("\ta large area covered by the sky.\n\n");

  printf(" -a:\tConvert all extentions to JPEG.\n");
  printf("\tThe extention numbers will be appended to \n"); 
  printf("\tthe JPEG names for each extention.\n\n");

  printf(" -l:\tLogarithmic scaling.\n\n");

  printf(" -t:\tSet the top truncation to the max color.\n");
  printf("\tBy default max color is black. If `-n` option is\n");
  printf("\tgiven it is white.\n\n");

  printf(" -b:\tSet the bottom (lower) truncation to ");
  printf("the minimum color.\n");
  printf("\tBy default min color is white. If `-n` option is\n");
  printf("\tgiven it is black.\n\n\n");



  printf("####### Options with arguments:\n");
  printf(" -i FILENAME\n\tInput FITS image name.\n\n");

  printf(" -e INTEGER\n\tFITS extention (if '-n' is not called)\n");
  printf("\tdefault: %d\n\n", p->ext);

  printf(" -o FILENAME\n\tOutput JPG image name\n");
  printf("\tdefault. When input is 'base.fits': 'base.jpg'.\n\n");

  printf(" -u INTEGER\n\tOutput JPG quality.\n");
  printf("\t100: No compression, high quality. As the value\n");
  printf("\tdecreases, the compression is more effective\n");
  printf("\but the tquality decreases.\n");
  printf("\tdefault: %d.\n\n", p->quality);

  printf(" -w FLOAT\n\tOutput JPG width in centimeters.\n");
  printf("\tdefault: %.3fcm\n\n", p->width);

  printf(" -c CHARACTER\n\tColor mode:\n");
  printf("\t\tc: CMYK.\n");
  printf("\t\tg: Gray scale image.\n");
  printf("\tdefault: %c\n\n", p->color);

  printf(" -p FLOAT\n\tLower pixel value truncation.\n");
  printf("\tIf equal to higher, no truncation.\n");
  printf("\tdefault: %f\n\n", p->low);

  printf(" -q FLOAT\n\tHigher pixel value truncation.\n");
  printf("\tIf equal to lower, no truncation.\n");
  printf("\tdefault: %f\n\n", p->high);

  printf(" -f INTEGER\n\tInner (black) border width\n");
  printf("\tdefault: %d\n\n", p->ibord);

  printf(" -g INTEGER\n\tOuter (white) border width\n");
  printf("\tdefault: %d\n\n", p->obord);

  printf(" -r from_1:to_1,from_2:to_2,...,from_N:to_N\n");
  printf("\tConvert \"from\" to \"to\".\n");
  printf("\tThis is usually not needed in astronomical images.\n");
  printf("\tBut can be useful if segmentation maps, or images\n");
  printf("\tthat keep labels or defined regions are input.\n");
  printf("\tIn such cases, a group of pixels have one label or\n");
  printf("\tvalue and this option might come in handy.\n");
  printf("\tConversion happens after trunctation, before log.\n");
  printf("\tThe order of conversion is the opposite of input order.\n");
  printf("\tNote that no spaces must be used any where in ");
  printf("the argument\n");
  printf("\tdefault: Convert nothing!\n\n\n");

  exit(EXIT_SUCCESS);
}





struct conversion *
makeconvstruct(char *arg, int opt)
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
	  printf("\n\nError in argument to '-%c':\n", opt);
	  printf("\t[from] and [to] values should be ");
	  printf("separated by a ':'.\n"); 
	  printf("\tYou have provided a '%c': \t%s\n\n\n", *p, arg);
	  exit(EXIT_FAILURE);
	}
      c->to=strtof(p, &p);
      if(*p==',') p++;
      else if(*p!='\0')
	{
	  printf("\n\nError in argument to %c:\n", opt);
	  printf("[from] and [to] pairs should be ");
	  printf("separated by a ','.\n"); 
	  printf("\tYou have provided a '%c': \t%s\n\n\n", *p, arg);
	  exit(EXIT_FAILURE);
	}
      c->next=out;
      out=c;
    }
  return out;
}





/* Read all the options into the program */
void
getsaveoptions(struct a2jparams *p, int argc, char *argv[])
{
  int c;
  char *tailptr;

  if(argc==1)
    printhelp(p);

  while( (c=getopt(argc, argv, "hvltbanc:e:o:i:w:p:q:f:g:r:u:")) != -1 )
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
      case 'e':			/* Extension of the FITS image. */
	checkint(optarg, &p->ext, c);
	break;
      case 'f':			/* Inner border. */
	checkint(optarg, &p->ibord, c);
	break;
      case 'g':			/* Outer border. */
	checkint(optarg, &p->obord, c);
	break;
      case 'r':			/* Convert pixel values */
	p->conv=makeconvstruct(optarg, c);
	break;
      case '?':
	fprintf(stderr, "\nUnknown option: '-%c'.\n\n", optopt);
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
