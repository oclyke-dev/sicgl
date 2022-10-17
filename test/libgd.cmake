# adds a shared library for libgd

# it is necessary (for now) to manually build and install libgd...
# cd third-party/libgd
# mkdir build
# cd build
# cmake -DBUILD_TEST=1 ENABLE_PNG=1 ..
# cmake --build .
# make install DESTDIR=${SICGL_ROOT}/build/libgd-install

# once this is done use the installed location to find resources

# create useful variables
set(LIBGD_LIB_DEPS)
set(LIBGD_ROOT_DIR ${CMAKE_SOURCE_DIR}/build/libgd-install/usr/local)
find_library(LIBGD libgd NAMES libgd.dylib libgd.so PATHS ${SICGL_ROOT_DIR}/build/libgd-install/usr/local/lib)

message(STATUS "Adding libgd library done")
