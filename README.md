# MMTL

[![Build Status](https://travis-ci.org/fuesika/mmtl.png?branch=cmake_builds)](https://travis-ci.org/fuesika/mmtl)

# Introduction

This branch contains reviewed code only that has been transferred to a
CMake-based build process. For the full and patched original code, refer to the
branch *old_code* in this git-repository.

# Original Information

TNT is the graphical front end supporting 2-D electromagnetic field
solvers developed at the Mayo Special Purpose Processor Development
Group (Mayo SPPDG).  These field solvers can compute per-unit-length
electrical characteristics from two dimensional descriptions of
transmission lines.

Mayo SPPDG has been implementing and using a variety of
electromagnetic modeling tools since the mid-1980s in support of its
primary research mission: developing next generation electronics
technology for high speed signal processor applications.  The
Mayo-developed applications have been known as the "MMTL"
applications, for Multilayer Multiconductor Transmission Line analysis
tools.  For more information about Mayo SPPDG, visit
http://www.mayo.edu/sppdg/

TNT is primarily a Tcl/Tk script application, and requires Tcl, Tk,
Incr Tcl, IWidgets, and BWidget packages.  These packages are freely
available, and the source code can be downloaded from
http://tcl.sourceforge.net/, http://incrtcl.sourceforge.net/, and
http://tcllib.sourceforge.net/.  Or you can download and install a
free binary distribution of ActiveTcl which includes all these (and
many other) packages from http://www.activestate.com/tcl/.

# Download

Original Win32-binaries and sources for TNT and MMTL field solver programs available on the web (discontinued since 2004):
* http://mmtl.sourceforge.net/

For the latest and patched version refer to:
* https://github.com/fuesika/mmtl


# Copyright

Copyright (C) Mayo Foundation 2002-2004.

TNT is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 2 of the License, or (at your
option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with TNT; see the file COPYING.  If not, write to the Free
Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
02111-1307 USA


# News

**February 16, 2015**
After some struggling with the original sources and trying to compile
TNT and MMTL using the latest GNU compilers, I provide the patched
sources via github. The original site at sourceforge seems to be
discontinued since its original release.
See https://github.com/fuesika/mmtl for the latest sources.

**July 21, 2004**
After much struggling, waiting, deciding, waiting some more, and
eventually approving, TNT and MMTL are being released under the GNU
General Public License.  For the first time, these relatively
straight-foward signal integrity tools are available to the public at
large. See http://mmtl.sourceforge.net/ for the distribution.
