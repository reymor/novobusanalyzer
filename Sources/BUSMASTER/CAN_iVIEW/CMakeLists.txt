set(PROJECT_NAME CAN_i-VIEW)

set(sources
  ../DIL_Interface/HardwareListingCAN.cpp
  AcceptanceFilterDlg.cpp
  CAN_i-VIEW.cpp
  CANRegAnalysis.cpp
  ChangeRegisters.cpp
)

set(headers
  AcceptanceFilterDlg.h
  CAN_i-VIEW.h
  CAN_i-VIEW_Extern.h
  CAN_i-VIEW_Resource.h
  CAN_i-VIEW_stdafx.h
  ChangeRegisters.h
  ContrConfigDefs.h
  ContrConfigPeakUsbDefs.h
  VCiViewIF.h)

set(resources
  CAN_i-VIEW.rc)

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
  Ws2_32
  Utils)

# installer options
add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
  COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
)
