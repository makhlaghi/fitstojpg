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
ucharmin(unsigned char *in, size_t size, int *min);
void
shortmin(short *in, size_t size, short *min);
void
longmin(long *in, size_t size, long *min);
void
floatmin(float *in, size_t size, float *min);
void
doublemin(double *in, size_t size, double *min);




void
ucminmax(unsigned char *in, size_t size, unsigned char *min, 
	 unsigned char *max);
void
shortminmax(short *in, size_t size, short *min, short *max);
void
longminmax(long *in, size_t size, long *min, long *max);
void
floatminmax(float *in, size_t size, float *min, float *max);
void
doubleminmax(double *in, size_t size, double *min, double *max);





void 
truncucarray(unsigned char *in, size_t size, unsigned char low, 
	     unsigned char high);
void 
truncsarray(short *in, size_t size, short low, short high);
void 
trunclarray(long *in, size_t size, long low, long high);
void 
truncfarray(float *in, size_t size, float low, float high);
void 
truncdarray(double *in, size_t size, double low, double high);





void
ucarrlog(unsigned char *in, size_t size, struct a2jparams *p);
void
sarrlog(short *in, size_t size, struct a2jparams *p);
void
larrlog(long *in, size_t size, struct a2jparams *p);
void
farrlog(float *in, size_t size, struct a2jparams *p);
void
darrlog(double *in, size_t size, struct a2jparams *p);

#endif
