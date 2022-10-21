# set some useful variables
set(TEST_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})

# set some useful variables for unity
include(${TEST_ROOT_DIR}/unity.cmake)

# set up shared library for spng
include(${TEST_ROOT_DIR}/spng.cmake)

# set up shared library for libgd
include(${TEST_ROOT_DIR}/libgd.cmake)

# set up shared library for test utilities
# (this depends on other library definitions
# therefore it should be the last include)
include(${TEST_ROOT_DIR}/utils.cmake)

# composite convenience lists
set(TESTS_INCLUDE_DIRECTORIES
  ${UNITY_ROOT_DIR}/src
  ${SPNG_ROOT_DIR}/spng
  ${LIBGD_ROOT_DIR}/include
  ${SICGL_ROOT_DIR}/include
  ${TESTUTILS_ROOT_DIR}/include
)
set(TESTS_SRC
  ${UNITY_SOURCES}
)
set(TESTS_LIBS
  ${SICGL_LIBRARIES}
  ${SPNG_LIBRARIES}
  ${LIBGD}
  ${TESTUTILS_LIBRARIES}
)

# include all tests
file(GLOB_RECURSE TESTS ${TEST_ROOT_DIR}/*/test.cmake)
foreach(TEST ${TESTS})
  message("INCLUDE ${TEST}")
  INCLUDE(${TEST})
endforeach(TEST)
