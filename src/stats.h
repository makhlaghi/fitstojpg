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
#ifndef STATS_H
#define STATS_H


#define MINFD -1e30
#define MAXFD  1e30




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
ucharminpos(unsigned char *in, size_t size, int *min);
void
shortminpos(short *in, size_t size, short *min);
void
longminpos(long *in, size_t size, long *min);
void
floatminpos(float *in, size_t size, float *min);
void
doubleminpos(double *in, size_t size, double *min);





void
convuc(struct conversion *p, unsigned char *in, size_t size);
void
convs(struct conversion *p, short *in, size_t size);
void
convl(struct conversion *p, long *in, size_t size);
void
convf(struct conversion *p, float *in, size_t size);
void
convd(struct conversion *p, double *in, size_t size);





void
ucarrlog(unsigned char *in, size_t size);
void
sarrlog(short *in, size_t size);
void
larrlog(long *in, size_t size);
void
farrlog(float *in, size_t size);
void
darrlog(double *in, size_t size);

#endif
