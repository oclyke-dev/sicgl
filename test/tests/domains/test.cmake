get_filename_component(TEST_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
set(TARGET_NAME "test_${TEST_NAME}")

add_executable(${TARGET_NAME})
target_sources(${TARGET_NAME} PRIVATE
  ${TESTS_SRC}
  ${CMAKE_CURRENT_LIST_DIR}/main.c
	${CMAKE_CURRENT_LIST_DIR}/src/specific/interface.c
	${CMAKE_CURRENT_LIST_DIR}/src/specific/global.c
	${CMAKE_CURRENT_LIST_DIR}/src/specific/screen.c
)
target_include_directories(${TARGET_NAME} PRIVATE
  ${TESTS_INCLUDE_DIRECTORIES}
  ${CMAKE_CURRENT_LIST_DIR}
	${CMAKE_CURRENT_LIST_DIR}/include
)
target_link_libraries(${TARGET_NAME}
  ${TESTS_LIBS}
)
