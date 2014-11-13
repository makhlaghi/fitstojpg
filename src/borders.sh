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
#Putting an inner border of 1 pixel width and an outer border of two
#pixels width on the output JPEG image.

./fitstojpg --imgext=2 --iborder=1 --oborder=2 $srcdir/mock.fits borders.jpg
#rm borders.jpg
