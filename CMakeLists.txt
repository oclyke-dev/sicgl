# https://cliutils.gitlab.io/modern-cmake
cmake_minimum_required(VERSION 3.21...3.24)
project(
  sicgl
  VERSION 0.0
  LANGUAGES C
)

set(CMAKE_C_STANDARD 17)

# set some useful variables
set(SICGL_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})

# create sicgl shared lib
include(${CMAKE_CURRENT_LIST_DIR}/sicgl.cmake)

# include tests
include(${CMAKE_CURRENT_LIST_DIR}/test/CMakeLists.txt)
