# creates useful variables for unity

# create useful variables
set(UNITY_ROOT_DIR ${CMAKE_SOURCE_DIR}/third-party/Unity)
set(UNITY_SOURCES
  ${UNITY_ROOT_DIR}/src/unity.c
)

# we cannot create a shared library for unity because it relies
# on the setUp and tearDown functions defined in the test app.

message(STATUS "Adding unity definitions done")
