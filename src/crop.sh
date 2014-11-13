#! /bin/bash
#
# Tests (examples) of using FITStoJPG:
#
#
#
# General information:
# ====================
#
# mock.fits is a multi-extension FITS image of a mock galaxy. The
# first extension is an actual mock image, the second extension is
# convolved and noise has been added on the third.
#
# Since FITStoJPG is not yet installed on the system, it is running
# from this directory, hence the `./fitstojpg`. After installation,
# run it with "fitstojpg" in any directory.
#
# After installation, see `fitstojpg --help` for all options.
#
#
#
# This test:
# -----------
#
#Crop a region of the FITS image:

./fitstojpg --imgext=2 --x1=10 --y1=3 --x2=48 --y2=45 $srcdir/mock.fits crop.jpg
#rm fluxtrunc.jpg
