# PURIFY 

## Description

PURIFY is a collection of routines written in C that implements different tools for radio
interferometric imaging including file handling (for both visibilities and fits files),
implementation of the measurement operator and set-up of the different optimization problems
used for image deconvolution. The code calls the generic Sparse OPTimization (SOPT) package to solve
the imaging optimization problems.

# Creators

* [R. E. Carrillo](http://people.epfl.ch/rafael.carrill)
* [J. D. McEwen](http://www.jasonmcewen.org)
* [Y. Wiaux](http://basp.eps.hw.ac.uk)

## Contributors

* Luke Pratley
* Mayeul d'Avezac


## Running the main purify executable

The main purify executable lives either in the build directory or in the in the `bin` subdirectory
of the installation directory.

## Reference

When referencing this code, please cite our related paper:

[1] R. E. Carrillo, J. D. McEwen and Y. Wiaux.  "PURIFY: a new
approach to radio-interferometric
imaging". Mon. Not. Roy. Astron. Soc., 439(4):3591-3604, 2014,
`arXiv:1307.4370 <http://arxiv.org/abs/1307.4370>`__

## Webpage

http://basp-group.github.io/purify/

## Installation

### C++ pre-requisites and dependencies

- [CMake](http://www.cmake.org/): a free software that allows cross-platform compilation
- [fftw3](www.fftw.org): Fastest Fourier Transform in the West
- [tiff](http://www.libtiff.org/): Tag Image File Format library
- [OpenMP](http://openmp.org/wp/): Optional. Speeds up some of the operations.
- [casacore](http://casacore.github.io/casacore/): Optional. Needed to interface with measurement
  sets. The main purify program requires this library (and its dependencies)
- [UCL/GreatCMakeCookOff](https://github.com/UCL/GreatCMakeCookOff): Collection of cmake recipes.
  Downloaded automatically if absent.
- [astro-informatics/sopt](https://github.com/astro-informatics/sopt): Sparse Optimization
  Compressed Sensing library. Downloaded automatically if absent.
- [Eigen 3](http://eigen.tuxfamily.org/index.php?title=Main_Page): Modern C++ linear algebra.
  Downloaded automatically if absent.
- [spdlog](https://github.com/gabime/spdlog): Optional. Logging library. Downloaded automatically if
   absent.
- [cfitsio](http://heasarc.gsfc.nasa.gov/fitsio/fitsio.html): library of C and Fortran subroutines
  for reading and writing data files in FITS (Flexible Image Transport System) data format.
  Downloaded automatically if absent. Needed by CCFits.
- [CCFits](http://heasarc.gsfc.nasa.gov/fitsio/ccfits/): c++ wrappers for cfitsio. Downloaded
  automatically if absent.
- [philsquared/Catch](https://github.com/philsquared/Catch): Optional - only for testing. A C++
  unit-testing framework. Downloaded automatically if absent.
- [google/benchmark](https://github.com/google/benchmar): Optional - only for benchmarks. A C++
  micro-benchmarking framework. Downloaded automatically if absent.

### Installing Purify

Once the dependencies are present, the program can be built with:

```
cd /path/to/code
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

To test everything went all right:

```
cd /path/to/code/build
ctest .
```

To install in directory `/X`, with libraries going to `X/lib`, python modules to
`X/lib/pythonA.B/site-packages/sopt`, etc, do:

```
cd /path/to/code/build
cmake -DCMAKE_INSTALL_PREFIX=/X ..
make install
```

### CMake Tips

It is possible to tell ``CMake`` exactly which libraries to compile and link against. The general
idea is to add ``-DVARIABLE=something`` to the command-line arguments of CMake. CMake can be called
any number of times: previous settings will not be overwritten unless specifically
requested. Some of the more common options are the following:

-  ``CMAKE_PREFIX_PATH``: CMake will look in "CMAKE\_PREFIX\_PATH/lib"
   for libraries, "CMAKE\_PREFIX\_PATH/include" for headers, etc.
-  ``PYTHON_EXECUTABLE``, ``PYTHON_LIBRARIES``, ``PYTHON_INCLUDE_DIRS``
-  ``FFTW3_LIBRARIES``, ``FFTW3_INCLUDE_DIR``
-  ``BLAS_INCLUDE_DIRS``, ``BLAS_LIBRARIES``

All these variables and more can be found and modified in the ``CMakeCache.txt`` file in the build
directory.

## SUPPORT

If you have any questions or comments, feel free to contact Rafael Carrillo or Jason McEwen, or add
an issue in the [issue tracker](https://github.com/astro-informatics/sopt/issues).

## NOTES

The code is given for educational purpose. The code is in beta and still under development.

## LICENSE

    PURIFY Copyright (C) 2013 Rafael Carrillo, Jason McEwen, Yves Wiaux

    This program is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This program is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
    Public License for more details (LICENSE.txt).

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.