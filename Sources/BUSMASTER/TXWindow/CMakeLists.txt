set(PROJECT_NAME TXWindow)

################################################################################
# Source, header and resources files
################################################################################
set(SOURCE_LIST
  TXWindow_Extern.cpp
  TxMsgChildFrame.cpp
  CCheckColumnTreeCtrl.cpp
  CANTxFormView.cpp
  CANTransmitter.cpp
  CANTxMsgItem.cpp
  TxDataStore.cpp
  LINScheduleDataStore.cpp
  LINTxFormView.cpp
  LinTransmitter.cpp
  LINTxMsgItem.cpp
  ITxFormView.cpp
  ScheduleTableCfgDlg.cpp
  stdafx.cpp
  Tx_MDIChildBase.cpp
)

set(HEADER_LIST
  CCheckColumnTreeCtrl.h
  CANTxFormView.h
  CANTransmitter.h
  CANTxMsgItem.h
  HashDefines.h
  LINTxMsgItem.h
  LINScheduleDataStore.h
  LINTxFormView.h
  LINTransmitter.h
  ITxFormView.h
  ITxMsgItem.h
  ITransmitter.h
  ScheduleTableCfgDlg.h
  Tx_MDIChildBase.h
  TxDataStore.h
  TxMsgChildFrame.h
  TXWindow_Extern.h
  resource.h
  stdafx.h
)

set(RESOURCE_LIST
  TXWindow.rc
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
  ${MFC_INCLUDE_DIRS})

################################################################################
# Compile definitions
################################################################################
add_definitions(-D_AFXEXT)

################################################################################
# Compile and link options
################################################################################
target_link_libraries(${PROJECT_NAME}
  Utilities
  BusmasterKernel  
  Winmm
  Utils
  DataTypes
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
