# tests
these are a collection of tests for sicgl.

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
