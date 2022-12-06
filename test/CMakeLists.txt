# set some useful variables
set(TEST_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})
set(BUILD_ROOT_DIR ${CMAKE_CURRENT_BINARY_DIR})

# set some useful variables for unity
include(${TEST_ROOT_DIR}/unity.cmake)

# set up shared library for spng
include(${TEST_ROOT_DIR}/spng.cmake)

# set up shared library for libgd
include(${TEST_ROOT_DIR}/libgd.cmake)

# set up shared library for test utilities
# (this depends on other library definitions
# therefore it should be the last include)
include(${TEST_ROOT_DIR}/utils.cmake)

# composite convenience lists
set(TESTS_INCLUDE_DIRECTORIES
  ${UNITY_ROOT_DIR}/src
  ${SPNG_ROOT_DIR}/spng
  ${LIBGD_ROOT_DIR}/include
  ${SICGL_ROOT_DIR}/include
  ${TESTUTILS_ROOT_DIR}/include
)
set(TESTS_SRC
  ${UNITY_SOURCES}
)
set(TESTS_LIBS
  ${SICGL_LIBRARIES}
  ${SPNG_LIBRARIES}
  ${LIBGD}
  ${TESTUTILS_LIBRARIES}
)

# set flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wno-error=unused-function -Wno-error=unused-label")

# include all tests
file(GLOB_RECURSE TESTS ${TEST_ROOT_DIR}/tests/*/test.cmake)
foreach(TEST ${TESTS})
  message("INCLUDE ${TEST}")
  INCLUDE(${TEST})
  if(DEFINED TEST_NAME)
    if(DEFINED TARGET_NAME)
      set(TEST_OUT_DIR ${BUILD_ROOT_DIR}/tests/${TEST_NAME})
      file(MAKE_DIRECTORY "${TEST_OUT_DIR}")
      file(MAKE_DIRECTORY "${TEST_OUT_DIR}/output")
      target_compile_definitions(${TARGET_NAME} PRIVATE
        -DTEST_OUTPUT_DIR="${TEST_OUT_DIR}/output"
      )
      set_target_properties(${TARGET_NAME} PROPERTIES
        OUTPUT_NAME test
        RUNTIME_OUTPUT_DIRECTORY "${TEST_OUT_DIR}"
      )
    else()
      message(SEND_ERROR "test ${TEST} did not define its TARGET_NAME")
    endif()
  else()
    message(SEND_ERROR "test ${TEST} did not define its TEST_NAME")
  endif()
  unset(TEST_NAME)
endforeach(TEST)
