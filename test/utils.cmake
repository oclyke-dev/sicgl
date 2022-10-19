# adds a shared library for test utilities

# create useful variables
set(TESTUTILS_ROOT_DIR ${TEST_ROOT_DIR}/utilities)
set(TESTUTILS_LIBRARIES testutils)

# create the shared library testutils
add_library(testutils SHARED
  ${TESTUTILS_ROOT_DIR}/bitmap_utils.c
)
target_include_directories(testutils PRIVATE
  ${TESTUTILS_ROOT_DIR}/include
  ${SPNG_ROOT_DIR}/spng
  ${LIBGD_ROOT_DIR}/include
  ${SICGL_ROOT_DIR}/include
)
target_link_libraries(testutils
  ${SPNG_LIBRARIES}
)

message(STATUS "Adding testutils library done")
