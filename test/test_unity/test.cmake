get_filename_component(TEST_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)

add_executable(${TEST_NAME})
target_sources(${TEST_NAME} PRIVATE
  ${UNITY_SOURCES}
  ${CMAKE_CURRENT_LIST_DIR}/main.c
)
target_include_directories(${TEST_NAME} PRIVATE
  ${UNITY_ROOT_DIR}/src
)
