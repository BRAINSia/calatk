# Copyright (C) 2008, 2011    GAMS Development
# All Rights Reserved.
# This file is distributed under the Eclipse Public License.
#
## $Id: Makefile.am 2042 2011-08-14 10:57:59Z stefan $
#
# Author: Stefan Vigerske

AUTOMAKE_OPTIONS = foreign

EXTRA_DIST = 

noinst_LTLIBRARIES = libLinearSolverLoader.la

libLinearSolverLoader_la_SOURCES = \
  LibraryHandler.c LibraryHandler.h \
  HSLLoader.c HSLLoader.h

AM_CPPFLAGS = \
  -I`$(CYGPATH_W) $(srcdir)/../../Common` \
  -I`$(CYGPATH_W) $(srcdir)/../../Algorithm/LinearSolvers` \
  $(HSL_CFLAGS)

if BUILD_PARDISOLOADER
  libLinearSolverLoader_la_SOURCES += PardisoLoader.c PardisoLoader.h
endif

libLinearSolverLoader_la_LIBADD = 
libLinearSolverLoader_la_DEPENDENCIES =  

DEFAULT_INCLUDES = -I. -I`$(CYGPATH_W) $(srcdir)` -I$(top_builddir)/src/Common

DISTCLEANFILES = 
