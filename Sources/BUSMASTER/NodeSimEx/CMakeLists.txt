set(PROJECT_NAME NodeSimEx)

################################################################################
# Source, header and resources files
################################################################################
set(SOURCE_LIST
  AppServices.cpp
  AppServicesCAN.cpp
  AppServicesJ1939.cpp
  AppServicesLIN.cpp
  BuildProgram.cpp
  BusEventHandlerDlg.cpp
  DefineTimerHandler.cpp
  ConvertCpp.cpp
  DLLHandlerDlg.cpp
  EditFrameWnd.cpp
  ErrHandlerDlg.cpp
  ErrHandlerDlgLIN.cpp
  EventHandlerDlg.cpp
  ExecuteFunc.cpp
  ExecuteManager.cpp
  ExploreMsgSg.cpp
  FileView.cpp
  FnsTreeView.cpp
  FunctionEditorBase.cpp
  FunctionEditorDoc.cpp
  FunctionView.cpp
  GlobalObj.cpp
  HandlerFunc.cpp
  IncludeHeaderDlg.cpp
  KeyValue.cpp
  MsgHandlerDlg.cpp
  ../Application/MultiLanguage.cpp
  NodeDetailsDlg.cpp
  NodeSim.cpp
  NodeSimEx.cpp
  NodeSimEx_stdafx.cpp
  ../Utility/OffScreenDC.cpp
  OutWnd.cpp
  SelectFunctions.cpp
  SetResetTimer.cpp
  Sim_MDIChildBase.cpp
  SimSysManager.cpp
  SimSysNodeInfo.cpp
  SimSysTreeView.cpp
  SimSysWnd.cpp
  UtlityDlg.cpp
)

set(HEADER_LIST
  AppServices.h
  AppServicesCAN.h
  AppServicesJ1939.h
  AppServicesLIN.h
  BaseNodeSim.h
  BuildProgram.h
  BusEventHandlerDlg.h
  DefineTimerHandler.h
  DLLHandlerDlg.h
  EditFrameWnd.h
  ErrHandlerDlg.h
  ErrHandlerDlgLIN.h
  EventHandlerDlg.h
  ExecuteFunc.h
  ExecuteManager.h
  ExploreMsgSg.h
  Export_UserDll.h
  Export_UserDllCAN.h
  Export_UserDllJ1939.h
  FileView.h
  FnsTreeView.h
  FunctionEditorBase.h
  FunctionEditorDoc.h
  FunctionEditorStruct.h
  FunctionView.h
  GlobalObj.h
  HandlerFunc.h
  IncludeHeaderDlg.h
  KeyValue.h
  MsgHandlerDlg.h
  ../Application/MultiLanguage.h
  ../Application/CNVTCToolBar.cpp
  ../Application/CNVTCImageList.cpp
  NodeDetailsDlg.h
  NodeSim.h
  NodeSimEx_Extern.h
  NodeSimEx_resource.h
  NodeSimEx_stdafx.h
  ../Utility/OffScreenDC.h
  OutWnd.h
  SelectFunctions.h
  SetResetTimer.h
  Sim_MDIChildBase.h
  SimSysManager.h
  SimSysNodeInfo.h
  SimSysTreeView.h
  SimSysWnd.h
  UtlityDlg.h
)

set(RESOURCE_LIST
  NodeSimEx.rc
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
  Utilities
  BusmasterKernel
  Winmm
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
