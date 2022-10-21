# tests
these are a collection of tests for sicgl.

# a general process

## build and run all tests
``` bash
mkdir build

# build and install libgd
cd third-party/libgd/build
cmake -DBUILD_TEST=1 ..
cmake --build .
make install DESTDIR=../../../build/libgd

# build sicgl
cd ../../../build
cmake ..
cmake --build .

# run tests
../tools/run_tests.sh
```

## build and run a single test
sometimes you want to just build and run a single test because it is faster when iterating.
to do this you can simply build the corresponding target with cmake

```bash
TEST=pixels
cmake --build . --target ${TEST}
./tests/${TEST}/test
```

# build system
the top-level CMakeLists.txt collects cmake files matching ```${TEST_ROOT_DIR}/*/test.cmake```. each of these should add a target named after the test. when building each of these targets will be built.

there are several available libraries which accomplish different goals in testing:
* libspng: enables encoding / decoding of PNG images (useful for visualization)
* libgd: acts as the reference implementation for drawing functions
* unity: provides a unit testing framework for c
* testutils: a collection of helper functions

these libraries are each configured and available for use independently within the test cmake stubs. see the corresponding ```*.cmake``` files for details.

the resources necessary to use these libraries are also consolidated into a few convenience lists:
* ```${TESTS_INCLUDE_DIRECTORIES}```: list of include directories to be use with ```target_include_directories```
* ```${TESTS_SRC}```: list of source files to compile to be used with ```target_sources```
* ```${TESTS_LIBS}```: list of libraries to link against to be used with ```target_link_libraries```

this makes it very simple to create a cmake stub for a new test. the following example adds a new executable target based on its own main.c with access to the standard set of tools for tests.

``` c
get_filename_component(TEST_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)

add_executable(${TEST_NAME})
target_sources(${TEST_NAME} PRIVATE
  ${TESTS_SRC}
  ${CMAKE_CURRENT_LIST_DIR}/main.c
)
target_include_directories(${TEST_NAME} PRIVATE
  ${TESTS_INCLUDE_DIRECTORIES}
  ${CMAKE_CURRENT_LIST_DIR}
)
target_link_libraries(${TEST_NAME}
  ${TESTS_LIBS}
)
```
