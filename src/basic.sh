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
# This test:
# -----------
#
# This is the most basic usage of fitstojpg (convert the first
# extension in a FITS image and use its full flux range). The output
# will be a jpg image with the same name but the extention of `.jpg`.
# Note that if you don't give the `basic.jpg` command line argument,
# the output JPEG image will be `mock.jpg`.

./fitstojpg $srcdir/mock.fits basic.jpg
#rm basic.jpg
