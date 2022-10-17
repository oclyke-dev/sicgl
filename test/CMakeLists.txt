# set some useful variables
set(TEST_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})

# set some useful variables for unity
include(${TEST_ROOT_DIR}/unity.cmake)

# set up shared library for spng
include(${TEST_ROOT_DIR}/spng.cmake)

# set up shared library for libgd
include(${TEST_ROOT_DIR}/libgd.cmake)

# include all tests
file(GLOB_RECURSE TESTS ${TEST_ROOT_DIR}/*/test.cmake)
foreach(TEST ${TESTS})
  message("INCLUDE ${TEST}")
  INCLUDE(${TEST})
endforeach(TEST)
