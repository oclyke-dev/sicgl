get_filename_component(TEST_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)

add_executable(${TEST_NAME})
target_sources(${TEST_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/main.c
  ${TEST_ROOT_DIR}/bitmap_utils.c
)
target_include_directories(${TEST_NAME} PRIVATE
  ${SICGL_ROOT_DIR}/include
  ${LIBGD_ROOT_DIR}/include
  ${SPNG_ROOT_DIR}/spng
  ${TEST_ROOT_DIR}
)
target_link_libraries(${TEST_NAME}
  ${LIBGD}
  ${SPNG_LIBRARIES}
)
