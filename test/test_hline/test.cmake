get_filename_component(TEST_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)

add_executable(${TEST_NAME})
target_sources(${TEST_NAME} PRIVATE
  ${UNITY_SOURCES}
  ${CMAKE_CURRENT_LIST_DIR}/main.c
  ${TEST_ROOT_DIR}/bitmap_utils.c
)
target_include_directories(${TEST_NAME} PRIVATE
  ${UNITY_ROOT_DIR}/src
  ${SPNG_ROOT_DIR}/spng
  ${SICGL_ROOT_DIR}/include
  ${TEST_ROOT_DIR}
)
target_link_libraries(${TEST_NAME}
  ${SPNG_LIBRARIES}
  ${SICGL_LIBRARIES}
)
