set(PROJECT_NAME CAN_ISOLAR_EVE_VCAN)

set(sources
  CAN_ISOLAR_EVE_VCAN.cpp
  CAN_ISOLAR_EVE_VCAN_stdafx.cpp)

set(headers
  CAN_ISOLAR_EVE_VCAN.h
  CAN_ISOLAR_EVE_VCAN_Defines.h
  CAN_ISOLAR_EVE_VCAN_Extern.h
  CAN_ISOLAR_EVE_VCAN_stdafx.h)

add_library(${PROJECT_NAME} SHARED ${sources} ${headers})

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
  Advapi32
  DataTypes
  Utils)

# installer options
add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
  COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
)
