include_directories (${CMAKE_SOURCE_DIR}/inc)

file(GLOB_RECURSE fmps_TEST_SOURCES "*.cpp")

add_executable(unit_tests ${fmps_TEST_SOURCES})
target_link_libraries (unit_tests fmpspart)

if (${TESTING_ENABLED})
  install (TARGETS unit_tests DESTINATION bin)
endif ()
