Quick start
-----------

For a quick start, see "Building and testing" section [on wiki](https://github.com/roc-project/roc/wiki#building-and-testing).

Dependencies
------------

**Build-time:**
* GCC >= 4.1 or clang >= 3.4
* python 2.x >= 2.6
* scons
* pkg-config (optional, use if you want installed dependencies to be auto-detected)
* gengetopt (optional, use if you want to build tools)
* doxygen >= 1.6, graphviz (optional, use if you want to build internal documentation)
* clang-tidy (optional, use if you want to run static analyzer)
* clang-format >= 3.8 (optional, use if you want to format code)
* libtool, autoconf, automake, make, cmake (optional, use if you want to download and build external dependencies automatically)

**Runtime:**
* [libuv](http://libuv.org) >= 1.4
* [OpenFEC](http://openfec.org) (optional but recommended, use if you want FEC support)
* [SoX](http://sox.sourceforge.net) >= 14.4.0 (optional, use if you want to build tools)
* [CppUTest](http://cpputest.github.io) >= 3.4 (optional, use if you want to build tests)

**Notes:**
* If you use CppUTest 3.4 or earlier, build it with `--disable-memory-leak-detection` option. It's leak detection doesn't work for us. Instead, we support building with clang sanitizers which include LeakSanitizer as well.
* If you use OpenFEC, it's recommended to use [our fork](https://github.com/roc-project/openfec) or manually apply patches from it. It is automatically selected by `--build-3rdparty=openfec` option. The fork contains several bugfixes and minor improvements that are not available in the upstream yet.

Building
--------

    $ scons --help
    $ scons <options> <variables> <targets>

After building, tools and libraries are inside `bin/` directory.

**Options**

* `-Q` - enable pretty output
* `-n` - dry run
* `-j N` - run N jobs in parallel
* `--build=BUILD`- system name where Roc is being compiled, e.g. `x86_64-pc-linux-gnu`, auto-detect if empty
* `--host=HOST` - system name where Roc will run, e.g. `arm-linux-gnueabihf`, equal to `--build` if empty
* `--platform=PLATFORM` - platform name where Roc will run, supported values: empty (detect from host), `linux`, `darwin`
* `--compiler=COMPILER` - compiler name and optional version, e.g. `gcc-4.9`, supported names: empty (detect what available), `gcc`, `clang`
* `--enable-debug` - enable debug build
* `--enable-debug-3rdparty` - enable debug build for 3rdparty libraries
* `--enable-sanitizers` - enable gcc/clang sanitizers
* `--enable-werror` - enable -Werror compiler option
* `--disable-lib` - disable libroc building
* `--disable-tools` - disable tools building
* `--disable-tests` - disable tests building
* `--disable-doc` - disable Doxygen documentation generation
* `--disable-openfec` - disable OpenFEC support required for FEC codes
* `--build-3rdparty=BUILD_3RDPARTY` - download and build specified 3rdparty libraries, pass a comma-separated list of library names and optional versions, e.g. `uv:1.4.2,openfec`
* `--override-targets=OVERRIDE_TARGETS` - override targets to use, pass a comma-separated list of target names, e.g. `gnu,posix,uv,openfec,...`
                                
**Variables**

These variables can be set either via command line or environment variables.
* `CC`
* `CXX`
* `LD`
* `AR`
* `RANLIB`
* `GENGETOPT`
* `DOXYGEN`
* `PKG_CONFIG`
* `CFLAGS`
* `CXXFLAGS`
* `LDFLAGS`

**Targets**

* *omitted* - build everything
* `test` - build everything and run unit tests
* `doxygen` - build documentation
* `clean` - remove build results
* `fmt` - format source code (if [clang-format](http://clang.llvm.org/docs/ClangFormat.html) >= 3.6 is found in PATH, it's used with [.clang-format](.clang-format) config)
* `tidy` - run clang static analyzer (requires clang-tidy to be installed)
* `{module}` - build only specific module
* `test/{module}` - build and run tests only for specific module

Examples
--------

Automatically detect platform and compiler, and build everything:

    $ scons -Q

Also build and run tests:

    $ scons -Q test

Select compiler and enable debugging:

    $ scons -Q --compiler=gcc --enable-debug --enable-sanitizers test

Select specific compiler version:

    $ scons -Q --compiler=gcc-4.8
    $ scons -Q --compiler=gcc-4.8.5

Build specific module (see [modules](src/modules/) directory):

    $ scons -Q roc_audio

And run tests:

    $ scons -Q test/roc_audio

Download and build libuv, OpenFEC and CppUTest, then build everything:

    $ scons -Q --build-3rdparty=uv,openfec,cpputest

Download and build all external dependencies, then build everything:

    $ scons -Q --build-3rdparty=all

Minimal build:

    $ scons -Q --disable-tools --disable-tests --disable-doc --disable-openfec

Cross-compile to armv7:

    $ scons -Q --host=arm-linux-gnueabihf --with-3rdparty=uv,openfec,alsa,pulseaudio,sox,cpputest
