fits2jpg
=========

Convert a FITS image to a grayscale or CMYK JPEG image.

Note: CMYK colors are still faulty, I will fix it as soon as possible.

Description:
------------

The [FITS image
standard](https://heasarc.gsfc.nasa.gov/docs/heasarc/fits.html) is the
standard used by astronomers to archive and use astronomical
data. This package converts images saved in that format into gray
scale or CMYK (with only the black channel being active) JPEG format
images. The resolution of the output JPEG image is identical to the 
input image.


Prerequisits:
------------
`fits2jpg` requires two packages to be installed on your
machine, installing them is easy and straightforward. 

- [IJG's libjpeg](http://www.ijg.org/), which should already be
  installed  on your system.
- [cfitsio](http://heasarc.nasa.gov/fitsio/fitsio.html) For
  reading and writing FITS files. I have explained [how to install
  `cfitsio` here](http://www.astr.tohoku.ac.jp/~akhlaghi/cfitsiowcslibinstall.html)


Installing and running:
------------
 
To install this `fits2jpg`, after downloading or cloning it, all you
have to do is to run `make` in the downloaded directory. In order to
be able to run `fits2jpg` from anywhere on your system, run `make
install` as root after the installation finishes.

Some command line options can be given so you can customize the
output, to learn them, run `./fits2jpg -h`.  A full list of all the
options with some explanation will be provided, nealy all the
operation of `fits2jpg` can be defined by these input options and
their arguments.  The [POSIX argument syntax
conventions](http://www.gnu.org/software/libc/manual/html_node/Argument-Syntax.html#Argument-Syntax)
apply.

In short the options are:

* `-h`: View help.
* `-l`: Logarithmic scaling.
* `-n`: Don't inverse grayscale.
       (by default it is for easier printing and viewing.)
* `-i`: Input FITS filename.
* `-e`: Input FITS extention.
* `-o`: Output JPEG name.
* `-w`: Width in print in centimeters.
* `-c`: Color space (grayscale or CMYK).
* `-a`: Lower truncation radius.
* `-b`: Higher truncation radius.
* `-f`: Width of black inner border in pixels.
* `-g`: Width of white outer border in pixels.

Future updates and issues:
------------
0. The CMYK output is not yet correct!
1. Make a nice documentation.
2. Add much more functionality and generality.
3. Work on a better user experience.
4. Fix any bugs I have not found yet!

Comments and suggestions:
----------------------------------------

I hope `fits2jpg` will be useful for you. If you find any problems in
this program please contact me so I can correct them. I would also be
very glad to hear any suggestions or comments you might have, thank
you.

makhlaghi@gmail.com 

akhlaghi@astr.tohoku.ac.jp

http://astr.tohoku.ac.jp/~akhlaghi/

----------------------------------------
Copyright:
----------------------------------------
Copyright (C) 2014 Mohammad Akhlaghi

Tohoku University Astronomical Institute

http://astr.tohoku.ac.jp/~akhlaghi/

`fits2jpg` is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

`fits2jpg` is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with `fits2jpg`.  If not, see <http://www.gnu.org/licenses/>.
