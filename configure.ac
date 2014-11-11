#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([FITStoJPG], [0.4], [makhlaghi@gmail.com], [fitstojpg],
        [https://github.com/makhlaghi/fitstojpg])
AM_INIT_AUTOMAKE([-Wall -Werror gnu])
AC_CONFIG_SRCDIR([src/ui.h])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
${CFLAGS=""}
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([cfitsio], [main], [], [AC_MSG_ERROR([Cannot continue.])])
AC_CHECK_LIB([jpeg], [main], [], [AC_MSG_ERROR([Cannot continue.])])
AC_CHECK_LIB([m], [main], [], [AC_MSG_ERROR([Cannot continue.])])

# Checks for header files.
AC_CHECK_HEADERS([limits.h stdlib.h string.h unistd.h argp.h], [],
                 [AC_MSG_ERROR([Cannot continue.])])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([strtol])

#Tell configure which files to work on:
AC_CONFIG_FILES([Makefile
                 src/Makefile])

#Read the configuration date.
AC_MSG_CHECKING([for date of configuration])
AC_DEFINE_UNQUOTED([CONFIGDATE], ["`date +"%d %B %Y"`"], 
                   [Date of configuration])
AC_DEFINE_UNQUOTED([CONFIGTIME], ["`date +"%H:%M"`"], 
                   [Time of configuration])
AC_MSG_RESULT([done])	

#Check if `defaults.ac` exists:
AC_MSG_CHECKING([if \`defaults.ac\` exists])
if [[ -f "$srcdir/defaults.ac" ]]; then
  source $srcdir/defaults.ac
else
  printf "\n$srcdir/defaults.ac does not exist!"; exit 1; fi
AC_MSG_RESULT([done])

#Function to check if input is a number:
checkifnumber()
{
  if ! [[[ $1 =~ ^-?[0-9]+([.][0-9]+)?$ ]]] ; then
    printf "\n\n\"$1\" in \'defaults.ac\` is not a number.\n"
    printf "Note: Replace numbers written like \".1\" with \"0.1\".\n\n"
    exit 1
  fi
}

#Read the rest of the default values and check them:
AC_MSG_CHECKING([default values in \`defaults.ac\`])

if [[ -n "$imgext" ]]; then
  checkifnumber	$imgext
  if [[ `echo "$imgext>=0" | bc` == 1 ]]; then
    AC_DEFINE_UNQUOTED([DP_IMGEXT_T], ["$imgext"], [Default parameter])
    AC_DEFINE_UNQUOTED([DP_IMGEXT_V], [$imgext], [Default parameter])
  else
    printf "\n\nIn \`defaults.ac\`, imgext must be >=0.\n\n"; exit 1; fi
else printf "\n\nimgext not in \`defaults.ac\` or not set.\n\n"; exit 1; fi

if [[ -n "$fluxlow" ]]; then
  checkifnumber $fluxlow
  AC_DEFINE_UNQUOTED([DP_FLUXLOW_T], ["$fluxlow"], [Default parameter])
  AC_DEFINE_UNQUOTED([DP_FLUXLOW_V], [$fluxlow], [Default parameter])
else printf "\n\nfluxlow not in \`defaults.ac\` or not set.\n\n"; exit 1; fi

if [[ -n "$fluxhigh" ]]; then
  checkifnumber $fluxhigh
  AC_DEFINE_UNQUOTED([DP_FLUXHIGH_T], ["$fluxhigh"], [Default parameter])
  AC_DEFINE_UNQUOTED([DP_FLUXHIGH_V], [$fluxhigh], [Default parameter])
else printf "\n\nfluxhigh not in \`defaults.ac\` or not set.\n\n"; exit 1; fi

if [[ -n "$x1" ]]; then
  checkifnumber $x1
  if [[ `echo "$x1>0" | bc` == 1 ]]; then
    AC_DEFINE_UNQUOTED([DP_X1_T], ["$x1"], [Default parameter])
    AC_DEFINE_UNQUOTED([DP_X1_V], [$x1], [Default parameter])
  else
    printf "\n\nIn \`defaults.ac\`, x1 must be >0.\n\n"; exit 1; fi
else printf "\n\nx1 not in \`defaults.ac\` or not set.\n\n"; exit 1; fi

if [[ -n "$y1" ]]; then
  checkifnumber $y1
  if [[ `echo "$y1>0" | bc` == 1 ]]; then
    AC_DEFINE_UNQUOTED([DP_Y1_T], ["$y1"], [Default parameter])
    AC_DEFINE_UNQUOTED([DP_Y1_V], [$y1], [Default parameter])
  else
    printf "\n\nIn \`defaults.ac\`, y1 must be >0.\n\n"; exit 1; fi
else printf "\n\ny1 not in \`defaults.ac\` or not set.\n\n"; exit 1; fi

if [[ -n "$x2" ]]; then
  checkifnumber $x2
  if [[ `echo "$x2>0" | bc` == 1 ]]; then
    AC_DEFINE_UNQUOTED([DP_X2_T], ["$x2"], [Default parameter])
    AC_DEFINE_UNQUOTED([DP_X2_V], [$x2], [Default parameter])
  else
    printf "\n\nIn \`defaults.ac\`, x2 must be >0.\n\n"; exit 1; fi
else printf "\n\nx2 not in \`defaults.ac\` or not set.\n\n"; exit 1; fi

if [[ -n "$y2" ]]; then
  checkifnumber $y2
  if [[ `echo "$y2>0" | bc` == 1 ]]; then
    AC_DEFINE_UNQUOTED([DP_Y2_T], ["$y2"], [Default parameter])
    AC_DEFINE_UNQUOTED([DP_Y2_V], [$y2], [Default parameter])
  else
    printf "\n\nIn \`defaults.ac\`, y2 must be >0.\n\n"; exit 1; fi
else printf "\n\ny2 not in \`defaults.ac\` or not set.\n\n"; exit 1; fi

if [[ -n "$quality" ]]; then
  checkifnumber $quality
  if [[ `echo "$quality>0 && $quality<=100" | bc` == 1 ]]; then
    AC_DEFINE_UNQUOTED([DP_QUALITY_T], ["$quality"], [Default parameter])
    AC_DEFINE_UNQUOTED([DP_QUALITY_V], [$quality], [Default parameter])
  else
    printf "\n\nIn \`defaults.ac\`, quality must be >0 and <=100.\n\n"; exit 1; fi
else printf "\n\nquality not in \`defaults.ac\` or not set.\n\n"; exit 1; fi

if [[ -n "$width" ]]; then
  checkifnumber $width
  if [[ `echo "$width>0" | bc` == 1 ]]; then
    AC_DEFINE_UNQUOTED([DP_WIDTH_T], ["$width"], [Default parameter])
    AC_DEFINE_UNQUOTED([DP_WIDTH_V], [$width], [Default parameter])
  else
    printf "\n\nIn \`defaults.ac\`, width must be >0.\n\n"; exit 1; fi
else printf "\n\nwidth not in \`defaults.ac\` or not set.\n\n"; exit 1; fi

if [[ -n "$colormode" ]]; then
  if [[ $colormode = "cmyk" ]]; then
    AC_DEFINE_UNQUOTED([DP_COLORMODE_T], ["$colormode"], [Default parameter])  
    AC_DEFINE_UNQUOTED([DP_COLORMODE_V], ['c'], [Default parameter])
  elif [[ $colormode = "gray" ]]; then
    AC_DEFINE_UNQUOTED([DP_COLORMODE_T], ["$colormode"], [Default parameter])    
    AC_DEFINE_UNQUOTED([DP_COLORMODE_V], ['g'], [Default parameter])
  else
    printf "\n\nIn \`defaults.ac\`, colormode must be \"cmyk\" or \"gray\".\n\n"
    exit 1; fi
else printf "\n\nwidth not in \`defaults.ac\` or not set.\n\n"; exit 1; fi

if [[ -n "$maxjpg" ]]; then
  checkifnumber $maxjpg
  if [[ `echo "$maxjpg>0 && $maxjpg<=255" | bc` == 1 ]]; then
    AC_DEFINE_UNQUOTED([DP_MAXJPG_T], ["$maxjpg"], [Default parameter])
    AC_DEFINE_UNQUOTED([DP_MAXJPG_V], [$maxjpg], [Default parameter])
  else
    printf "\n\nIn \`defaults.ac\`, maxjpg must be >0 and <=255.\n\n"; exit 1; fi
else printf "\n\nmaxjpg not in \`defaults.ac\` or not set.\n\n"; exit 1; fi

if [[ -n "$iborder" ]]; then
  checkifnumber $iborder
  if [[ `echo "$iborder>=0" | bc` == 1 ]]; then
    AC_DEFINE_UNQUOTED([DP_IBORDER_T], ["$iborder"], [Default parameter])
    AC_DEFINE_UNQUOTED([DP_IBORDER_V], [$iborder], [Default parameter])
  else
    printf "\n\nIn \`defaults.ac\`, iborder must be >=0.\n\n"; exit 1; fi
else printf "\n\niborder not in \`defaults.ac\` or not set.\n\n"; exit 1; fi

if [[ -n "$oborder" ]]; then
  checkifnumber $oborder
  if [[ `echo "$oborder>=0" | bc` == 1 ]]; then
    AC_DEFINE_UNQUOTED([DP_OBORDER_T], ["$oborder"], [Default parameter])
    AC_DEFINE_UNQUOTED([DP_OBORDER_V], [$oborder], [Default parameter])
  else
    printf "\n\nIn \`defaults.ac\`, oborder must be >=0.\n\n"; exit 1; fi
else printf "\n\noborder not in \`defaults.ac\` or not set.\n\n"; exit 1; fi

AC_MSG_RESULT([done])	

#Make the outputs:
AC_OUTPUT

#Print a bye-bye message:
echo
echo "==================================================="
echo "AC_PACKAGE_STRING is now configured:"
echo
echo "You are now ready to compile AC_PACKAGE_STRING".
echo "Simply run the commands: \`make\` then \`make install\`"
echo "==================================================="
echo
