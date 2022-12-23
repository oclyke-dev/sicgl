# adds a shared library for sicgl

# create useful variables
set(SICGL_LIB_DEPS -lm)
set(SICGL_ROOT_DIR ${CMAKE_SOURCE_DIR})
set(SICGL_LIBRARIES sicgl ${SICGL_LIB_DEPS})

set(SICGL_SOURCES
	${SICGL_ROOT_DIR}/src/color_sequence.c
	${SICGL_ROOT_DIR}/src/interpolation.c
	${SICGL_ROOT_DIR}/src/iter.c
	${SICGL_ROOT_DIR}/src/screen.c
	${SICGL_ROOT_DIR}/src/translate.c

	${SICGL_ROOT_DIR}/src/specific/blit.c
	${SICGL_ROOT_DIR}/src/specific/direct.c
	${SICGL_ROOT_DIR}/src/specific/display.c
	${SICGL_ROOT_DIR}/src/specific/field.c
	${SICGL_ROOT_DIR}/src/specific/global.c
	${SICGL_ROOT_DIR}/src/specific/screen.c

	${SICGL_ROOT_DIR}/src/generic/direct.c
	${SICGL_ROOT_DIR}/src/generic/display.c
	${SICGL_ROOT_DIR}/src/generic/global.c
	${SICGL_ROOT_DIR}/src/generic/naive.c
	${SICGL_ROOT_DIR}/src/generic/screen.c
)
if(DEFINED DEBUG)
	set(SICGL_SOURCES ${SICGL_SOURCES}
		# ${SICGL_ROOT_DIR}/src/debug/debug.c
	)
endif()

# create the shared library sicgl
add_library(sicgl SHARED
	${SICGL_SOURCES}
)
target_include_directories(sicgl PRIVATE
  ${SICGL_ROOT_DIR}/include
)
target_link_libraries(sicgl
  ${SICGL_LIB_DEPS}
)
target_compile_definitions(sicgl PRIVATE
  ${SICGL_COMPILE_DEFINITIONS}
)

message("SICGL_COMPILE_DEFINITIONS=${SICGL_COMPILE_DEFINITIONS}")

message(STATUS "Adding sicgl library done")
