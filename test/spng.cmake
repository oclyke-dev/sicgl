# adds a shared library for libspng

# require ZLIB
find_package(ZLIB REQUIRED)

# create useful variables
set(SPNG_LIB_DEPS -lm ${ZLIB_LIBRARIES})
set(SPNG_ROOT_DIR ${CMAKE_SOURCE_DIR}/third-party/libspng)
set(SPNG_LIBRARIES spng ${SPNG_LIB_DEPS})

# create the shared library spng
add_library(spng SHARED ${SPNG_ROOT_DIR}/spng/spng.c)
target_include_directories(spng PRIVATE
  ${ZLIB_INCLUDE_DIRS}
)
target_link_libraries(spng
  ${SPNG_LIB_DEPS}
)

message(STATUS "Adding spng library done")
