#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
AC_INIT([mruby-mdbm], [0.0.1], [syucream1031@gmail.com])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_SRCDIR([src/mruby_mdbm.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX

# ATS root
MDBM_PREFIX=./mdbm
AC_ARG_WITH(mdbm_prefix, AC_HELP_STRING([--with-mdbm-prefix=DIR],
    [pathname to mdbm_prefix [[mdbm_prefix]]]),
    [MDBM_PREFIX="$with_mdbm_prefix"])
AC_SUBST(MDBM_PREFIX)

# mruby root
MRUBY_PREFIX=`pwd`/mruby
AC_ARG_WITH(mruby_prefix, AC_HELP_STRING([--with-mruby-prefix=DIR],
    [pathname mruby_prefix [[mruby_prefix]]]),
    [MRUBY_PREFIX="$with_mruby_prefix"])
AC_SUBST(MRUBY_PREFIX)

# Checks for libraries.
# AC_HAVE_LIBRARY([mruby])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
