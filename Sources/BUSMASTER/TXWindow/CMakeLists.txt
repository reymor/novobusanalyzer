set(sources
  CCheckColumnTreeCtrl.cpp
  LINScheduleDataStore.cpp
  ScheduleTableCfgDlg.cpp
  Tx_MDIChildBase.cpp
  TxMsgChildFrame.cpp)

set(headers
  CCheckColumnTreeCtrl.h
  HashDefines.h
  LINScheduleDataStore.h
  ScheduleTableCfgDlg.h
  Tx_MDIChildBase.h
  TxMsgChildFrame.h)

add_library(TXWindowFlexRay SHARED ${sources} ${headers} ${resources})

include_directories(
  ..
  ${ICONV_INCLUDE_DIR}
  ${LIBXML2_INCLUDE_DIR}
  ${ATL_INCLUDE_DIRS}
  ${MFC_INCLUDE_DIRS})

# compiler options
add_definitions(-D_AFXEXT)

# linker options
target_link_libraries(TXWindowFlexRay
  Winmm
  DIL_Interface
  Utils
  DataTypes)

# installer options
add_custom_command(
  TARGET TXWindowFlexRay
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${PROJECT_SOURCE_DIR}/BIN/${CMAKE_BUILD_TYPE}/
  COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:TXWindowFlexRay> ${PROJECT_SOURCE_DIR}/BIN/${CMAKE_BUILD_TYPE}/)
