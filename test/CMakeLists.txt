# set some useful variables
set(TEST_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})

# set some useful variables for unity
include(${CMAKE_CURRENT_LIST_DIR}/unity.cmake)

# set up shared library for spng
include(${CMAKE_CURRENT_LIST_DIR}/spng.cmake)

# include all tests
file(GLOB_RECURSE TESTS ${CMAKE_CURRENT_LIST_DIR}/*/test.cmake)
foreach(TEST ${TESTS})
  message("INCLUDE ${TEST}")
  INCLUDE(${TEST})
endforeach(TEST)
