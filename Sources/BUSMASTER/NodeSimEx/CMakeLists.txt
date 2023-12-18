set(sources
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
  UtlityDlg.cpp)

set(headers
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
  UtlityDlg.h)

set(resources
  NodeSimEx.rc)

add_library(NodeSimEx SHARED ${sources} ${headers} ${resources})

include_directories(
  ..
  ${ICONV_INCLUDE_DIR}
  ${LIBXML2_INCLUDE_DIR}
  ${ATL_INCLUDE_DIRS}
  ${MFC_INCLUDE_DIRS})

# compiler options
add_definitions(-D_AFXEXT)

# linker options
set_target_properties(NodeSimEx PROPERTIES LINK_FLAGS "/NODEFAULTLIB:daouuid")
target_link_libraries(NodeSimEx
  DataTypes
  Utils
  "${CMAKE_SOURCE_DIR}/../Kernel/Bin/$(Configuration)/Utilities.lib"
  "${CMAKE_SOURCE_DIR}/../Kernel/Bin/BusmasterKernel/$(Configuration)/BusmasterKernel.lib"
  Winmm)

# installer options
add_custom_command(
  TARGET NodeSimEx
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${PROJECT_SOURCE_DIR}/BIN/${CMAKE_BUILD_TYPE}/
  COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:NodeSimEx> ${PROJECT_SOURCE_DIR}/BIN/${CMAKE_BUILD_TYPE}/)
