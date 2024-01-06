set(PROJECT_NAME CAN_Kvaser_CAN)

set(sources
  AcceptanceFilterDlg.cpp
  CAN_Kvaser_CAN.cpp
  CANRegAnalysis.cpp
  ChangeRegisters.cpp
  ../Application/MultiLanguage.cpp
  ../DIL_Interface/HardwareListingCAN.cpp
)

set(headers
  AcceptanceFilterDlg.h
  CAN_Kvaser_CAN.h
  CAN_Kvaser_CAN_Extern.h
  CAN_Kvaser_CAN_Resource.h
  CAN_Kvaser_CAN_stdafx.h
  ChangeRegDefines.h
  ChangeRegisters.h
  ContrConfigPeakUsbDefs.h
  ../Application/MultiLanguage.h)

set(resources
  CAN_Kvaser_CAN.rc)

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
  ${CMAKE_CURRENT_SOURCE_DIR}/EXTERNAL/Lib/MS/canlib32.lib
  CommonClass
  DataTypes
  Utils)

# installer options
add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
  COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
)
