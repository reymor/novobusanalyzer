set(PROJECT_NAME FrameProcessor)

################################################################################
# Source, header and resources files
################################################################################
set(SOURCE_LIST
  ConfigMsgLogDlg.cpp
  ConfigMsgLogCANDlg.cpp
  ConfigMsgLogLINDlg.cpp
  ConfigMsgLogJ1939Dlg.cpp
  BaseLogObject.cpp
  Format/FormatMsgCAN.cpp
  Format/FormatMsgCommon.cpp
  Format/FormatMsgJ1939.cpp
  Format/FormatMsgLIN.cpp
  FrameProcessor.cpp
  FrameProcessor_CAN.cpp
  FrameProcessor_Common.cpp
  FrameProcessor_J1939.cpp
  FrameProcessor_LIN.cpp
  LogObjectCAN.cpp
  LogObjectJ1939.cpp
  LogObjectLIN.cpp
)

set(HEADER_LIST
  BaseFrameProcessor_CAN.h
  BaseFrameProcessor_J1939.h
  BaseFrameProcessor_LIN.h
  BaseLogObject.h
  Format/FormatMsgCAN.h
  Format/FormatMsgCommon.h
  Format/FormatMsgJ1939.h
  Format/FormatMsgLIN.h
  FrameProcessor.h
  FrameProcessor_CAN.h
  FrameProcessor_Common.h
  FrameProcessor_extern.h
  FrameProcessor_J1939.h
  FrameProcessor_LIN.h
  FrameProcessor_stdafx.h
  Logger_CommonDataTypes.h
  LogObjectCAN.h
  LogObjectJ1939.h
  LogObjectLIN.h
)

set(RESOURCE_LIST
  FrameProcessor.rc
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} SHARED ${SOURCE_LIST} ${HEADER_LIST} ${RESOURCE_LIST})

include_directories(
  ..
  ${ICONV_INCLUDE_DIR}
  ${LIBXML2_INCLUDE_DIR}
  ${ATL_INCLUDE_DIRS}
  ${MFC_INCLUDE_DIRS}
)

################################################################################
# Compile definitions
################################################################################
add_definitions(-D_AFXEXT)

################################################################################
# Compile and link options
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:daouuid")
target_link_libraries(${PROJECT_NAME}
  DataTypes
  Utils
  Filter
  Utilities
  BusmasterKernel
  CommonClass
)

################################################################################
# Post build events
################################################################################
add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
  COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
)
