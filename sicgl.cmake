# adds a shared library for sicgl

# create useful variables
set(SICGL_LIB_DEPS -lm)
set(SICGL_ROOT_DIR ${CMAKE_SOURCE_DIR})
set(SICGL_LIBRARIES sicgl ${SICGL_LIB_DEPS})

# create the shared library sicgl
add_library(sicgl SHARED
  ${SICGL_ROOT_DIR}/src/generic.c
  ${SICGL_ROOT_DIR}/src/iter.c
  ${SICGL_ROOT_DIR}/src/naive.c
  ${SICGL_ROOT_DIR}/src/sicgl.c
  ${SICGL_ROOT_DIR}/src/specific.c
  ${SICGL_ROOT_DIR}/src/transformations.c
)
target_include_directories(sicgl PRIVATE
  ${SICGL_ROOT_DIR}/include
)
target_link_libraries(sicgl
  ${SICGL_LIB_DEPS}
)

message(STATUS "Adding sicgl library done")
