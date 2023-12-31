set(sources
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
  Tx_MDIChildBase.cpp
)

set(headers
  CCheckColumnTreeCtrl.h
  HashDefines.h
  LINScheduleDataStore.h
  ScheduleTableCfgDlg.h
  Tx_MDIChildBase.h
  TxMsgChildFrame.h
)

add_library(TXWindow SHARED ${sources} ${headers} ${resources})

include_directories(
  ..
  ${ICONV_INCLUDE_DIR}
  ${LIBXML2_INCLUDE_DIR}
  ${ATL_INCLUDE_DIRS}
  ${MFC_INCLUDE_DIRS})

# compiler options
add_definitions(-D_AFXEXT)

# linker options
target_link_libraries(TXWindow
  "${CMAKE_SOURCE_DIR}/../Kernel/Bin/$(Configuration)/Utilities.lib"
  "${CMAKE_SOURCE_DIR}/../Kernel/Bin/BusmasterKernel/$(Configuration)/BusmasterKernel.lib"  
  Winmm
  Utils
  DataTypes)

# installer options
add_custom_command(
  TARGET TXWindow
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${PROJECT_SOURCE_DIR}/BIN/${CMAKE_BUILD_TYPE}/
  COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:TXWindow> ${PROJECT_SOURCE_DIR}/BIN/${CMAKE_BUILD_TYPE}/)
