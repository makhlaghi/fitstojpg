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
# This is a simple exmple showing how all the extensions in a
# multi-extension FITS file will be converted to a JPEG image.

echo srcdir is: $srcdir
./fitstojpg $srcdir/mock.fits -a
