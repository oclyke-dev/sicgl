# creates useful variables for unity

# create useful variables
set(UNITY_ROOT_DIR ${CMAKE_SOURCE_DIR}/third-party/Unity)
set(UNITY_SOURCES
  ${UNITY_ROOT_DIR}/src/unity.c
)
set(UNITY_INCLUDES
  ${UNITY_ROOT_DIR}/src
)

message(STATUS "Adding unity definitions done")
