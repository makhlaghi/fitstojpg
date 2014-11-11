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
#ifndef ARGPPARSER_H
#define ARGPPARSER_H

#include <argp.h>



/* Definition parameters for the argp: */
const char *argp_program_version=PACKAGE_STRING
  "\nCopyright (C) 2014 Mohammad Akhlaghi.\n"
  "License GPLv3+: GNU GPL version 3 or later "
  "<http://gnu.org/licenses/gpl.html>\n"
  "This is free software: you are free to change "
  "and redistribute it.\n"
  "There is NO WARRANTY, to the extent permitted by law.";





const char *argp_program_bug_address=PACKAGE_BUGREPORT;





static char args_doc[] = "FITSimage.fits JPEGimage";





const char doc[] = 
  /* Before the list of options: */
  "\n" PACKAGE_STRING" -- Convert a FITS image to a JPEG image.\n"
  "Configured for this machine on "CONFIGDATE", "CONFIGTIME".\n\n"
  "If no output JPEG name is given, the output name will be the same as "
  "the input FITS name with `.jpg` instead of `.fits`.\n\n"
  "When calling the short format of the options, simply put your input "
  "value after the short version of the option, an equal sign (=) should "
  "not be used. For example, `-e4` or `-e 4` are the same as calling "
  "`--imgext=4`.\n\n"
  "The three capital letters after the long options indicate that providing "
  "a value is mandatory if the option is called. The letters show the "
  "format your input will be stored in:\n"
  "   INT:  An integer.\n"
  "   FLT:  A floating point number.\n"
  "   STR:  A string of characters (for example a file name).\n\n"
  "The default values for options are shown in the `[...]` immediately "
  "before the description for that option. Defaults are set and can be "
  "changed before running `./configure` in the `defaults.ac` file."
  /* After the list of options: */
  "\v"
  PACKAGE_NAME" home page: "PACKAGE_URL;





/* The options are classified into these categories:
   1. Operating mode like quiet, help and version.
   2. Input (image, mask and kernel name, extensions and ...)
   3. Meshs and threads.
   4. Detection 

   Available letters for short options:
   h i m o v x z
   A B D E F G H I J K L M N O P Q R S T U W X Y Z

   Number keys used: <=500.

   Options with keys (second structure element) larger than 500 do not
   have a short version.
 */
static struct argp_option options[] =
  {
    /* Such cases are group headers */
    {
      0, 0, 0, 0,  		/* These have to be zero for groups. */
      "Operating modes:", 	/* Explanation for the group. */
      -1			/* Group ID. */
    },
    {
      "log",		      /* Long name for this option.         */
      'l',		      /* Short name or key for this option. */
      0,		      /* Informative type of value it gets. */
      0,                      /* Flags for this option. */
      "Use logarithmic scaling.\n",
      -1		      /* Option group ID. */
    },
    {
      "noinv",
      'n',
      0,
      0,
      "By default the image is inverted such that the brightest pixels "
      "are the darkest in the output. With this option, the brightest "
      "will be white.\n",
      -1
    },
    {
      "allext",
      'a',
      0,
      0,
      "Convert all the extensions in the FITS image.\n",
      -1      
    },
    {
      "ttrunccolor",
      't',
      0,
      0,
      "Set `--fluxhigh` to the maximum color, this is only relevant "
      "when `--fluxhigh` is larger than the maximum flux in the image. \n",
      -1      
    },
    {
      "btrunccolor",
      'b',
      0,
      0,
      "Set `--fluxlow` to the minimum color, this is only relevant "
      "when `--fluxlow` is smaller than the minimum flux in the image. \n",
      -1      
    },
    {
      "convfirst",
      'C',
      0,
      0,
      "First convert the pixels, then truncate the flux. By default the "
      "opposite is done.\n",
      -1      
    },





    {
      0, 0, 0, 0,  		/* These have to be zero for groups. */
      "Input FITS image:",      /* Explanation for the group. */
      1				/* Group ID. */
    },
    {
      "imgext",	
      'e', 		
      "INT",
      0,
      "["DP_IMGEXT_T"] The input image fits extension number, starting "
      "from 0 (zero).\n",
      1
    },
    {
      "fluxlow",	
      'p', 		
      "FLT",
      0,
      "["DP_FLUXLOW_T"] The lower flux threshold on the image, if equal "
      "to `--fluxhigh`, no threshold will be applied.\n",
      1
    },
    {
      "fluxhigh",	
      'q', 		
      "FLT",
      0,
      "["DP_FLUXHIGH_T"] The higher flux threshold on the image, if equal "
      "to `--fluxlow`, no threshold will be applied.\n",
      1
    },
    {
      "x1",
      'j', 		
      "INT",
      0,
      "["DP_X1_T"] To convert only a small region of a larger FITS image. "
      "This option sets the bottom left (when viewed in SAO ds9) box "
      "corner position along the first FITS axis (horizontal in SAO ds9). "
      "If `--x1`==`--x2` or `--y1==--y2`, then no cropping is done.\n",
      1
    },
    {
      "y1",
      'k', 		
      "INT",
      0,
      "["DP_Y1_T"] The bottom left box corner position along the second "
      "FITS axis, see explanation of `--x1`.\n",
      1
    },
    {
      "x2",
      's', 		
      "INT",
      0,
      "["DP_X2_T"] The top right box corner position along the first "
      "FITS axis, see explanation of `--x1`.\n",
      1
    },
    {
      "y2",
      'y', 		
      "INT",
      0,
      "["DP_Y2_T"] The top right box corner position along the second "
      "FITS axis, see explanation of `--x1`.\n",
      1
    },
    {
      "convert",
      'r', 		
      "STR",
      0,
      "Convert pixel values prior to making the JPEG image. This can be "
      "useful if segmentation maps, or images that keep labels of "
      "defined regions are the input. In such cases, a group of pixels "
      "have one label or value and this option might come in handy. By "
      "default, conversion happens after trunctation, but this can be "
      "changed with the `-C` option. In any case, it occurs before "
      "logarithmic transformation. The syntax for conversion is like this:\n"
      "\t`from_N:to_N,...,from_2:to_2,from_1:to_1`\n"
      "The order of conversion is the opposite of input order (as labeled). "
      "Note that no spaces must be used any where in the argument\n",
      1
    },
    
    


    {
      0, 0, 0, 0,  		
      "Output JPEG image:",      
      2				
    },
    {
      "quality",
      'u',
      "INT",
      0,
      "["DP_QUALITY_T"] A value between >0 and <=100 with 100 begin the "
      "maximum quality.\n",
      2
    }, 
    {
      "width",
      'w',
      "FLT",
      0,
      "["DP_WIDTH_T"] The width of the JPEG image in centimeters. Note that "
      "in most cases you will set the centimeter size based on the "
      "published medium. In digital usage, only the number of pixels (that "
      "is equal to the FITS image size) matters, not this value.\n",
      2
    },
    {
      "colormode",
      'c',
      "STR",
      0,
      "["DP_COLORMODE_T"] One of these:\n\t`cmyk`: CMYK (blak channel "
      "only).\n\t`gray`: Gray scale.\n",
      2
    },
    {
      "maxjpg",
      'd', 		
      "INT",
      0,
      "["DP_MAXJPG_T"] The dynamic range of a JPEG image is 0-255. This "
      "option specifies the maximum value.\n",
      2
    },
    {
      "iborder",
      'f', 		
      "INT",
      0,
      "["DP_IBORDER_T"] Inner (black color) border width in pixels.\n",
      2
    },    
    {
      "oborder",
      'g', 		
      "INT",
      0,
      "["DP_OBORDER_T"] Outer (white color) border width in pixels.\n",
      2
    },

    

    {0}
  };





/* Parse a single option: */
static error_t
parse_opt(int key, char *arg, struct argp_state *state)
{
  /* Temporary variable: */
  int tmp;
  
  /* Save the arguments structure: */
  struct a2jparams *p = state->input;
  
  /* In case the user incorrectly uses the equal sign (for example
     with a short format or with space in the long format, then `arg`
     start with (if the short version was called) or be (if the long
     version was called with a space) the equal sign. So, here we
     check if the first character of arg is the equal sign, then the
     user is warned and the program is stopped: */
  if(arg && arg[0]=='=')
    argp_error(state, "Incorrect use of the equal sign (`=`). For short "
	       "options, `=` should not be used and for long options, "
	       "there should be no space between the option, equal sign "
	       "and value.");
 
  switch(key)
    {
    /* Operating modes: */
    case 'l':
      p->log=1;
      break;
    case 'a':
      p->allext=1;
      break;
    case 'n':
      p->inv=0;
      break;
    case 't':
      p->ttrunccolor=1;
      break;
    case 'b':
      p->btrunccolor=1;
      break;
    case 'C':
      p->convertfirst=1;
      break;

    /* Input FITS image: */
    case 'e':
      intelzero(arg, &p->imgext, "imgext", key);
      break;
    case 'p':
      anyfloat(arg, &p->fluxlow);
      break;
    case 'q':
      anyfloat(arg, &p->fluxhigh);
      break;
    case 'j':			     /* Note that the axises in C and     */
      intl1(arg, &p->y1, "x1", key); /* FITS differ. Also counting begins */
      --p->y1;			     /* from 1 in FITS and 0 in C.        */
      break;
    case 'k':
      intl1(arg, &p->x1, "y1", key);
      --p->x1;
      break;
    case 's':
      intl1(arg, &p->y2, "x2", key);
      --p->y2;
      break;
    case 'y':
      intl1(arg, &p->x2, "y2", key);
      --p->x2;
      break;
    case 'r':
      p->conv=makeconvstruct(arg);
      break;
      

    /* Output JPEG image: */
    case 'u':
      intrange(arg, &p->quality, "quality", key, 0, 100);
      break;
    case 'w':
      floatl0(arg, &p->width, "width", key);
      break;
    case 'c':
      if(strcmp(arg, CMYKNAME)==0)
	p->colormode=CMYKCODE;
      else if(strcmp(arg, GRAYNAME)==0)
	p->colormode=GRAYCODE;
      else
	{
	  fprintf(stderr, PACKAGE": %s is not recognized in "
		  "`--colormode (-c)`. Should be `%s` or `%s`.\n",
		  arg, CMYKNAME, GRAYNAME);
	  exit(EXIT_FAILURE);
	}
      break;
    case 'd':
      intrange(arg, &tmp, "maxjpg", key, 0, 255);
      p->maxjpg=tmp;
      break;
    case 'f':
      intelzero(arg, &p->iborder, "iborder", key);
      break;
    case 'g':
      intelzero(arg, &p->oborder, "oborder", key);
      break;
      
      /* Read the non-option argument: */
    case ARGP_KEY_ARG:
      /* Since there are only two arguments, state->arg_num should
	 never be more than 2. Note that it starts from zero.*/
      if(state->arg_num >= 2)
	argp_error(state, "Too many arguments! ");

      /* See what type of input value it is and put it in. */
      if( strcmp(&arg[strlen(arg)-5], ".fits")==0 )
	{
	  if(p->imgname)
	    argp_error(state, "Only one FITS image should be given.");
	  else
	    p->imgname=arg;
	}
      else if( strcmp(&arg[strlen(arg)-4], ".jpg")==0
	       || strcmp(&arg[strlen(arg)-4], ".JPG")==0
	       || strcmp(&arg[strlen(arg)-5], ".jpeg")==0
	       || strcmp(&arg[strlen(arg)-5], ".JPEG")==0)
	{
	  if(p->outname)
	    argp_error(state, "Only one JPEG image should be given.");
	  else
	    {
	      p->outname=arg;
	      p->freeoutname=0;
	    }
	}
      else
	argp_error(state, "Argument not recognized as a FITS image "
		   "(ending with `.fits`) or a JPEG image (ending in "
		   "any of `.jpg`, `.jpeg`, `.JPG` or `.JPEG`).");
      break;
      
      /* Make sure an argument is given: */
    case ARGP_KEY_END:
      if(state->arg_num==0)
	argp_error(state, "No argument given!");
      if(p->imgname==NULL)
	argp_error(state, "No input FITS image provided!");
      break;

    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}





/* Basic structure defining the whole argument reading process. */
static struct argp argp = {options, parse_opt, args_doc, doc};


#endif
