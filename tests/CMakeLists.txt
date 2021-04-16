if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
  add_library(main_test SHARED main_test.cpp)
  target_link_libraries(main_test PUBLIC doctest mpx)

  file(GLOB_RECURSE TEST_SRCS CONFIGURE_DEPENDS "*.test.cpp")
  foreach(TEST_SRC ${TEST_SRCS})
    get_filename_component(TEST_NAME ${TEST_SRC} NAME_WLE)

    message(STATUS "Adding test ${TEST_NAME} in ${TEST_SRC}")

    add_executable(${TEST_NAME} ${TEST_SRC})
    target_link_libraries(${TEST_NAME} main_test)

    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
  endforeach() 
endif()
