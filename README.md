# sicgl
\ si-kəl \
small iterator graphics library

# todo

* perform bounds checking within the library based on 
  passed in parameters of the screen but not in tight loops

# principles

* hardware agnostic
* entirely in c
* speed over memory
* tested

# tests
unit tests are handled with [unity](https://github.com/ThrowTheSwitch/Unity) and functional tests are enabled using [libgd](https://github.com/libgd/libgd) and [libspng](https://github.com/randy408/libspng).

**building tests**
``` sh
# create build dir
~/sicgl % mkdir build

# install libgd
~/sicgl % cd third-party/libgd
~/third-party/libgd % mkdir build
~/third-party/libgd/build % cmake -DBUILD_TEST=1 ..
~/third-party/libgd/build % cmake --build .
~/third-party/libgd/build % make install DESTDIR=../../../build/libgd
~/third-party/libgd/build % cd ../../../build

# build the tests
~/sicgl/build % cmake ..
~/sicgl/build % cmake --build .

# clean the build dir
~/sicgl/build % cmake --build . --target=clean
```

**running tests**
``` sh
# run all tests
~/sicgl/build % ../tools/run-tests.sh

# run individual tests
~/sicgl/build % ./test_unity
~/sicgl/build % ./test_libspng_manual_pixels
...
```

**finding tests**
on mac you could use this regex to find tests...
```find -E . -regex '\.\/build\/test_[^\.]*$'```

on mac from within the build directory you could run all the tests like this:
```find -E . -regex '\.\/test_[^\.]*$' -exec '{}' -v \;```

# code formatting
this project uses clang-format and [run-clang-format.py](https://github.com/Sarcasm/run-clang-format). to format all the right code:

```bash
# once, to set up virtual environment
python3 -m venv venv

# once per session, activate virtual environment
source ./venv/bin/activate

# to check code formatting
./tools/third-party/run-clang-format/run-clang-format.py -r include src test

# to format all code
./tools/third-party/run-clang-format/run-clang-format.py -r include src test -i
```

# debug mode
```cmake .. -DDEBUG=true```

# speed over memory footprint
in its early conception sicgl was meant to be hardware-agnostic and extremely
easy to tailor to any hardware. this was acheieved through a function-pointer
based interface. this did in fact achieve great flexibility (if some hardware
required 3-bit color definitions then the pixel, hline, vline and region
implementations could be carefully constructed to handle memory access 
efficiently or even write directly to unique hardware), however it did this at
the cost of speed. another style of interface traded some of that flexibility
for efficient memory manipulation. speed tests (available in the tests) revealed
an ~100x speed increase for filled region drawing in some cases. the complexity
of supporting both interface styles is unattractive for the goals of this
library when the fast interface still affords hardware-independence in many
use cases. below are some additional considerations:

* the fast interface assumes integer byte lengths for color representations, so
odd cases such as three-bit color depth (as seen in some E-ink displays, for 
example) will find this interface to be wasteful in terms of memory usage.
* the fast interface does not provide user 'hooks' into drawing operation. these
would either be implemented as either runtime (function pointers) or compile-time
(macros, header replacement, etc..) modifications which are respectively slow and
cumbersome. this means that the library requires the user to handle display
device memory update on a case-by-case basis - for instance by pushing the entire
display memory again or possibly intelligently updating only the affected area of
the display. this also makes it impossible to handle direct-to-display writing
(where the pixel, hline, and vline implementations control the display device
directly).
* the fast interface is particularly well-suited to display drivers which natively
support integer byte length color types and require a full display update - one
great example of which are the serially-controlled addressable LED cascades such
as the APA102 or WS2812B chipsets.

future work on this codebase could revive work on the generic interface, as it is
in fact farticularly well suited for use in many embedded systems: areas where
memory footprint is a major concern and the size of displays (and therefore the
importance of speed) is lesser. one way to support this interface would be to
duplicate the API with a second set of functions, perhaps with some suffix
indicating their alternative role. this will have drawbacks such as increasing the
size of the library, but those may be mitigated in various ways.

all this is to say that the general use case is not forgotten. this project
welcomes proposals for how to bring the generic interface into parity with the
fully-featured specific counterpart.

# run-sliced lines

```c
uext_t min_run;       // minimum length to run
uext_t run_len;       // actual length of run for each step
ext_t accumulator;    // accumulates error from intended line location
ext_t remainder, reset; // amounts by which to manipulate the accumulator
                        // remainder tracks error in the major axis from having to choose an integer number of steps
                        // reset tracks minor axis adjustment which accounts for the cumulative movement in the major axis
uext_t len0, len1;    // special run lengths for the first and last runs
ext_t unext, vnext;   // working coordinates
```
