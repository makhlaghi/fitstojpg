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
#ifndef UI_H
#define UI_H

void
anyfloat(char *optarg, float *var);

void
intl1(char *optarg, int *var, char *lo, char so);

void
intlzero(char *optarg, int *var, char *lo, char so);

void
intelzero(char *optarg, int *var, char *lo, char so);

void
floatl0(char *optarg, float *var, char *lo, char so);

void
intrange(char *optarg, int *var, char *lo, char so, int low, int high);

void
checkremoveoutimage(char *outname);

void
findnamebase(char *inname, char **out, int removenamedir);

struct conversion *
makeconvstruct(char *arg);

void
setparams(struct a2jparams *p, int argc, char *argv[]);

void
freeconvstruct(struct conversion *c);

#endif
