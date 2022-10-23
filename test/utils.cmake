# adds a shared library for test utilities

# create useful variables
set(TESTUTILS_ROOT_DIR ${TEST_ROOT_DIR}/utilities)
set(TESTUTILS_LIBRARIES testutils)

# create the shared library testutils
add_library(testutils SHARED
  ${TESTUTILS_ROOT_DIR}/conversion.c
  ${TESTUTILS_ROOT_DIR}/png.c
  ${TESTUTILS_ROOT_DIR}/screen.c
  ${TESTUTILS_ROOT_DIR}/simultaneous.c
  ${TESTUTILS_ROOT_DIR}/utilities.c

  ${TESTUTILS_ROOT_DIR}/interfaces/interface_bytes.c
  ${TESTUTILS_ROOT_DIR}/interfaces/interface_libgd.c
  ${TESTUTILS_ROOT_DIR}/interfaces/interface_png.c
)
target_include_directories(testutils PRIVATE
  ${TESTUTILS_ROOT_DIR}/include
  ${UNITY_ROOT_DIR}/src
  ${SPNG_ROOT_DIR}/spng
  ${LIBGD_ROOT_DIR}/include
  ${SICGL_ROOT_DIR}/include
)
target_link_libraries(testutils
  ${SICGL_LIBRARIES}
  ${SPNG_LIBRARIES}
  ${LIBGD}
)

message(STATUS "Adding testutils library done")
