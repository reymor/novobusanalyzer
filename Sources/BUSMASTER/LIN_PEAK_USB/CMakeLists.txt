set(PROJECT_NAME LIN_PEAK_USB)

set(sources
  ../DIL_Interface/CommanDIL_LIN.cpp
  ../DIL_Interface/HardwareListing.cpp
  LIN_PEAK_USB.cpp
  LIN_PEAK_USB_Channel.cpp
  LIN_PEAK_USB_Network.cpp
  LIN_PEAK_USB_stdafx.cpp)

set(headers
  ../DIL_Interface/CommanDIL_LIN.h
  EXTERNAL/PLinApi.h
  LIN_PEAK_USB.h
  LIN_PEAK_USB_Channel.h
  LIN_PEAK_USB_Extern.h
  LIN_PEAK_USB_Network.h
  LIN_PEAK_USB_Resource.h
  LIN_PEAK_USB_stdafx.h)

set(resources
  LIN_PEAK_USB.rc)

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
  DataTypes
  Utils)

# installer options
add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
  COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
)
