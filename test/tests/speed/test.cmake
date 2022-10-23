get_filename_component(TEST_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)

add_executable(${TEST_NAME})
target_sources(${TEST_NAME} PRIVATE
  ${TESTS_SRC}
  ${CMAKE_CURRENT_LIST_DIR}/main.c
)
target_include_directories(${TEST_NAME} PRIVATE
  ${TESTS_INCLUDE_DIRECTORIES}
  ${CMAKE_CURRENT_LIST_DIR}
)
target_link_libraries(${TEST_NAME}
  ${TESTS_LIBS}
)

message("speed cmake TESTS_LIBS=${TESTS_LIBS}")
