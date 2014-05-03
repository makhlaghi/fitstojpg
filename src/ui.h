/*********************************************************************
fitstojpg - Make mock astronomical profiles (galaxy, star, ...) 
           in a FITS file

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
#ifndef UI_H
#define UI_H

void
setdefaultoptions(struct a2jparams *p);

void
checkremoveoutimage(char *outname);

void
checkinimage(char *inname);

void
findnamebase(char *inname, char **out);

void
freeconvstruct(struct conversion *c);

void
getsaveoptions(struct a2jparams *p, int argc, char *argv[]);

#endif
