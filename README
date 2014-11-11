FITStoJPG
=========

Convert a FITS image to a grayscale or CMYK JPEG image.

Description:
------------

The [FITS image
standard](https://heasarc.gsfc.nasa.gov/docs/heasarc/fits.html) is the
standard used by astronomers to archive and use astronomical
data. This package converts images saved in that format into gray
scale or CMYK (with only the black channel being active) JPEG format
images. The resolution of the output JPEG image is identical to the 
input image. Some of the capabilities of FITStoJPG can be listed as:

* Using greyscale and CMYK colorspaces.
* Convert all the possible extensions in a FITS image with one command.
* Specify a box in the FITS image instead of converting the whole image.
* Specify a flux range to emphasize on a special feature.
* Convert pixel value (useful in segmentation maps).
* Add inner and outer borders to the JPEG output.
* Set the quality of the JPEG image.
* Use logarithmic scale before saving as JPEG.
* Inverts the colors by default (great for including in a document),
  can be turned off.


Why CMYK?
---------

The major advantage in saving in the CMYK color space is in printing.
So if you don't want to ultimately print the image, it doesn't really
matter that much. But if you do want to print your FITS image in a
report or a paper, there is a big difference and we strongly recommend
you to save the output as CMYK. Also some journals require the colors
space of the images used to be CMYK. Most color printers use
Cyan-Magenta-Yellow and Key (black) ink cartridges to do color
printing. A FITS image only has one value per pixel, so it is
essentially a greyscale image.

When you send a grey scale image into a color printer, most printers
use the combination of the three CMY colors to produce shades of
grey. This results in a slightly blurred image due to the very small
errors in printing each color and also in the extra use of ink. But
when you save a FITS image only in the K channel of the CMYK color
space, you force the printer to only use its black ink, this results
in a sharper printed image with the shades of grey being more clear,
you also use less ink so it is also more cost-effective! 

Take a look at the figure below as an example, where in each figure,
the bottom left pixel is complete black and the top right pixel is
complete white. The one on the left is a grey scale JPEG image and on
the right is a CMYK JPEG image with only the K channel used.  I have
taken a screen shot of how the two images compare when I included then
in a LaTeX document and viewed them on my desktop monitor.

<img src="https://raw.githubusercontent.com/makhlaghi/fitstojpg/master/doc/fitstojpg-figures/grey_CMYK_comp.png" width=600/>

In print the ouputs are very similar. You see that the shades of grey
in the left image (greyscale) are slightly more darker with a higher
contrast. Most converters of an RBG space image to a CMYK use all
three channels in their conversion, resulting in a very large file
size. Since RBG requires 3 bytes per pixel but CMYK requires 4! But
when you only save in the K channel of the CMYK color space, the JPEG
image compression algorithm, detects the fact that you have left the
three channels empty and the resulting image approximately has the
same volume (in bytes) as a greyscale JPEG image that only has one
byte per pixel. Therefore your report or paper has a lower volume than
if you want to convert to CMYK and also prints better.

Requirements:
------------

FITStoJPG requires two packages to be installed on your
machine, installing them is easy and straightforward. 

- [IJG's libjpeg](http://www.ijg.org/), which should already be
  installed  on your system.
- [cfitsio](http://heasarc.nasa.gov/fitsio/fitsio.html) For
  reading and writing FITS files. I have explained [how to install
  `cfitsio` here](http://www.astr.tohoku.ac.jp/~akhlaghi/cfitsiowcslibinstall.html)


Installing and running:
------------

To install FITStoJPG, after downloading or cloning it, all you have
to do is to run the standard configuring, compiling and installing
commands in the downloaded directory (`$` as user and `#` as root):

    $ ./configure
    $ make
    # make install

Command line options are used to specify how FITStoJPG operates. To
get the full list of options and a short explanation of each, run
`fitstojpg --help` or `fitstojpg -?`. 


Future updates and issues:
------------

1. Add much more functionality and generality.
2. Work on a better user experience.
3. Fix any bugs I have not found yet!


Comments and suggestions:
----------------------------------------

I hope FITStoJPG will be useful for you. If you find any problems in
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

FITStoJPG is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

FITStoJPG is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with FITStoJPG.  If not, see <http://www.gnu.org/licenses/>.