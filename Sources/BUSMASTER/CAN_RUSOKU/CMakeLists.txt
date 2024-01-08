set(PROJECT_NAME CAN_RUSOKU)

set(sources
  CAN_RUSOKU.cpp
  CAN_RUSOKU_stdafx.cpp
  ../DIL_Interface/HardwareListingCAN.cpp
)

set(headers
  CAN_RUSOKU.h
  CAN_RUSOKU_Extern.h
  CAN_RUSOKU_stdafx.h
  resource.h
  EXTERNAL/canal.h)

set(resources
  CAN_RUSOKU.rc)

add_library(${PROJECT_NAME} SHARED ${sources} ${headers} ${resources})

include_directories(
  ..
  ${ICONV_INCLUDE_DIR}
  ${LIBXML2_INCLUDE_DIR}
  ${ATL_INCLUDE_DIRS}
  ${MFC_INCLUDE_DIRS})

# compiler options
add_definitions(-D_USRDLL)

# linker options
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:daouuid")
target_link_libraries(${PROJECT_NAME}
  ${CMAKE_CURRENT_SOURCE_DIR}/EXTERNAL/canal.lib
  DataTypes
  Utils)

# installer options
add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
  COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
  COMMAND ${CMAKE_COMMAND} ARGS -E copy ${CMAKE_CURRENT_SOURCE_DIR}/EXTERNAL/canal.dll ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
)
