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
#include <jpeglib.h>

#include "arr2jpg.h"
#include "fitsarrayvv.h"
#include "ui.h"	/* Needs arr2jpg.h */
#include "stats.h"





int 
main(int argc, char *argv[])
{
  void *arr;
  int bitpix;
  size_t s0, s1;
  struct a2jparams in;

  setdefaultoptions(&in);

  getsaveoptions(&in, argc, argv);
  
  checkinimage(in.inname);

  checkremoveoutimage(in.outname);

  fits_to_array(in.inname, in.ext, &bitpix, &arr, &s0, &s1);

  arr2jpg(arr, s0, s1, bitpix, &in);

  free(arr);
  return 0;
}
