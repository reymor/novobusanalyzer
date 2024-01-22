set(PROJECT_NAME CAN_STUB)

set(sources
  CAN_STUB.cpp)

set(headers
  CAN_STUB.h
  CAN_STUB_Extern.h
  CAN_STUB_stdafx.h)

add_library(${PROJECT_NAME} SHARED ${sources} ${headers})

include_directories(
  ..
  ${CMAKE_BINARY_DIR}/Sources/BUSMASTER/BusEmulation/BusEmulation.dir/${CMAKE_BUILD_TYPE}/ # workaround to find BusEmulation.h
  ${ICONV_INCLUDE_DIR}
  ${LIBXML2_INCLUDE_DIR}
  ${ATL_INCLUDE_DIRS}
  ${MFC_INCLUDE_DIRS})

add_dependencies(${PROJECT_NAME}
  BusEmulation)

# compiler options
add_definitions(-D_USRDLL)

# linker options
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:daouuid")
target_link_libraries(${PROJECT_NAME}
  DataTypes
  Utils)

if(MSVC)
  target_link_options(${PROJECT_NAME} PRIVATE /DEBUG)
endif()

# installer options
add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
  COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
)
