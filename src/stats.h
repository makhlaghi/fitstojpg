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
#ifndef STATS_H
#define STATS_H


#define MINFD -1e30
#define MAXFD  1e30

void
floatmin(float *in, size_t size, float *min);

void
fminmax(float *in, size_t size, float *min, float *max);

void 
truncfarray(float *in, size_t size, float low, float high);

void
farrlog(float *in, size_t size, struct a2jparams *p);

#endif
