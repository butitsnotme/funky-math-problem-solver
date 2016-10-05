set(fmps_INCLUUDE_DIRS ${CMAKE_SOURCE_DIR}/inc)
file(GLOB_RECURSE fmps_SOURCES "*.cpp")

list(REMOVE_ITEM fmps_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
list(APPEND fmps_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/data.S)

include_directories(
  ${fmps_INCLUUDE_DIRS}
  ${CMAKE_SOURCE_DIR}/lib/args/)

SET(fmps_DATA_DIR "${CMAKE_SOURCE_DIR}/data")
set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/data.S
  PROPERTIES OBJECT_DEPENDS "${fmps_DATA_DIR}/VERSION;${fmps_DATA_DIR}/VERSION_TEMPLATE;${fmps_DATA_DIR}/VERSION_TEMPLATE_DEV;${fmps_DATA_DIR}/PROGRAM_DESCRIPTION")

add_library (fmpspart STATIC ${fmps_SOURCES})

add_executable (fmps ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_link_libraries (fmps fmpspart)

if (${DEVELOPMENT_BUILD} MATCHES True)
  add_definitions (-DDEVELOPMENT_BUILD)
endif()

install (TARGETS fmps DESTINATION bin)
install (TARGETS fmpspart DESTINATION lib)
