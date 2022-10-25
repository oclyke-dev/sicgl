# adds a shared library for test utilities

# create useful variables
set(TESTUTILS_ROOT_DIR ${TEST_ROOT_DIR}/utilities)
set(TESTUTILS_LIBRARIES testutils)

# create the shared library testutils
add_library(testutils SHARED
	${TESTUTILS_ROOT_DIR}/color_sequence.c
	${TESTUTILS_ROOT_DIR}/conversion.c
	${TESTUTILS_ROOT_DIR}/display.c
	${TESTUTILS_ROOT_DIR}/image.c
	${TESTUTILS_ROOT_DIR}/interface_libgd.c
	${TESTUTILS_ROOT_DIR}/png.c
	${TESTUTILS_ROOT_DIR}/screen.c
	${TESTUTILS_ROOT_DIR}/simultaneous_generic_display.c
	${TESTUTILS_ROOT_DIR}/simultaneous_generic_screen.c
	${TESTUTILS_ROOT_DIR}/simultaneous_specific_display.c
	${TESTUTILS_ROOT_DIR}/simultaneous_specific_screen.c
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
