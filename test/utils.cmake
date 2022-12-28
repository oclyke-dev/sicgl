# adds a shared library for test utilities

# create useful variables
set(TESTUTILS_ROOT_DIR ${TEST_ROOT_DIR}/utilities)
set(TESTUTILS_LIBRARIES testutils)

# create the shared library testutils
add_library(testutils SHARED
	${TESTUTILS_ROOT_DIR}/src/color_sequence.c
	${TESTUTILS_ROOT_DIR}/src/conversion.c
	${TESTUTILS_ROOT_DIR}/src/image.c
	${TESTUTILS_ROOT_DIR}/src/interface_libgd.c
	${TESTUTILS_ROOT_DIR}/src/png.c
	${TESTUTILS_ROOT_DIR}/src/screen.c

	${TESTUTILS_ROOT_DIR}/src/simultaneous/specific/display.c
	${TESTUTILS_ROOT_DIR}/src/simultaneous/specific/global.c
	${TESTUTILS_ROOT_DIR}/src/simultaneous/specific/interface.c
	${TESTUTILS_ROOT_DIR}/src/simultaneous/specific/screen.c
)
target_include_directories(testutils PRIVATE
	${SICGL_ROOT_DIR}/include
  ${TESTUTILS_ROOT_DIR}/include
  ${UNITY_ROOT_DIR}/src
  ${SPNG_ROOT_DIR}/spng
  ${LIBGD_ROOT_DIR}/include
)
target_link_libraries(testutils
  ${SICGL_LIBRARIES}
  ${SPNG_LIBRARIES}
  ${LIBGD}
)

message(STATUS "Adding testutils library done")
