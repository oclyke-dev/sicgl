# adds a shared library for sicgl

# create useful variables
set(SICGL_LIB_DEPS -lm)
set(SICGL_ROOT_DIR ${CMAKE_SOURCE_DIR})
set(SICGL_LIBRARIES sicgl ${SICGL_LIB_DEPS})

set(SICGL_SOURCES
	${SICGL_ROOT_DIR}/src/display.c
	${SICGL_ROOT_DIR}/src/iter.c
	${SICGL_ROOT_DIR}/src/screen.c

	${SICGL_ROOT_DIR}/src/specific/color_sequence.c
	${SICGL_ROOT_DIR}/src/specific/specific.c

	${SICGL_ROOT_DIR}/src/generic/generic.c
	${SICGL_ROOT_DIR}/src/generic/naive.c
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
