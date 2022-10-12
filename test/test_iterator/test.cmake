get_filename_component(TEST_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)

add_executable(${TEST_NAME})
target_sources(${TEST_NAME} PRIVATE
  ${UNITY_SOURCES}
  ${CMAKE_CURRENT_LIST_DIR}/main.c
  ${CMAKE_CURRENT_LIST_DIR}/bare_range.c
  ${CMAKE_CURRENT_LIST_DIR}/range.c
)
target_include_directories(${TEST_NAME} PRIVATE
  ${UNITY_ROOT_DIR}/src
  ${SICGL_ROOT_DIR}/include
)
target_link_libraries(${TEST_NAME} ${SICGL_LIBRARIES})
