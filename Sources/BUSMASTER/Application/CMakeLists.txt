set(PROJECT_NAME NovoBusAnalyzer)

################################################################################
# Source, header and resources files
################################################################################
set(SOURCE_LIST
  Application.cpp
  AppServices_Impl.cpp
  AboutDlg.cpp
  BUSMASTER.cpp
  BusmasterDump.cpp
  BusStatisticCAN.cpp
  BusStatisticLIN.cpp
  BusStatistics.cpp
  BusStatisticsDlg.cpp
  CNVTCImageList.cpp
  CNVTCToolBar.cpp
  ConfigData.cpp
  ConfigMsgDispPropPg.cpp
  ClientManager.cpp
  CANSignalExtractor.cpp
  DatabaseDissociateDlg.cpp
  DisplayIntMsg.cpp
  DriverInfoDlg.cpp
  ElementSelection.cpp
  ChannelConfigurationDlg.cpp
  Flags.cpp
  FlexTxHandler.cpp
  GraphConfiguration.cpp
  GraphElement.cpp
  GraphList.cpp
  GraphParameters.cpp
  InterfaceGetter.cpp
  ImportLogToolbar.cpp
  J1939TimeOutCfg.cpp
  LINBusStatisticsDlg.cpp
  LINSignalExtractor.cpp
  MainFrm.cpp
  MDIChildBase.cpp
  MessageWindowSettingsDialog.cpp
  MessageAttrib.cpp
  MessageDetailsDlg.cpp
  MessageInterpretation.cpp
  MessageList.cpp
  MsgBufferConfigPage.cpp
  MsgFilterConfigPage.cpp
  MsgFrmtWnd.cpp
  MsgIDAttr.cpp
  MsgSgDetView.cpp
  MsgSgTreeView.cpp
  MsgSignal.cpp
  MsgSignalDBWnd.cpp
  MsgWndHdrInfo.cpp
  MsgWndThread.cpp
  MFCRibbonBarEx.cpp
  MultiLanguage.cpp
  NetworkStatistics.cpp
  NotificListbox.cpp
  NotificWnd.cpp
  PPageMessage.cpp
  Properties.cpp
  ProgressBarDlg.cpp
  RxMsgList.cpp
  SigGrphConfigDlg.cpp
  BusmasterPluginManager.cpp
  SigGrphWndHandler.cpp
  SignalDetailsDlg.cpp
  Splash.cpp
  SplFileDlg.cpp
  StdAfx.cpp
  Struct.cpp
  TreeItemParam.cpp
  TSEditorHandler.cpp
  TSExecutorHandler.cpp
  TxMsgWndJ1939.cpp
  UI/MenuCreator.cpp
  UI/Menus.cpp
  UI/BusmasterMenuItem.cpp
  UI/IdGenerator.cpp
  UI/IIdGenerator.cpp
  UI/UICreator.cpp
  UIThread.cpp
  Utility.cpp
  ValueDescriptionDlg.cpp
  VariableLayer.cpp
  WaveFormDataHandler.cpp
  WaveformSelectionDlg.cpp
  WaveformTransmitter.cpp
  WrapperErrorLogger.cpp
)

set(HEADER_LIST
  AppServices_Impl.h
  BaseBusStatisticCAN.h
  BaseBusStatisticLIN.h
  BUSMASTER.h
  AboutDlg.h
  StdAfx.h
  BusmasterEvents.h
  BusmasterDump.h
  BusStatisticCAN.h
  BusStatisticLIN.h
  BusStatistics.h
  BusStatisticsDlg.h
  CFilesDefs_CAN.h
  CNVTCImageList.h
  CNVTCToolBar.h
  common.h
  ConfigData.h
  CANSignalExtractor.h
  ClientManager.h
  CSignalGeneration.h
  DatabaseDissociateDlg.h
  DataType.h
  DisplayIntMsg.h
  DriverInfoDlg.h
  ElementSelection.h
  ChannelConfigurationDlg.h
  Flags.h
  FlexTxHandler.h
  GraphConfiguration.h
  GraphElement.h
  GraphList.h
  GraphParameters.h
  HashDefines.h
  InterfaceGetter.h
  IBusmasterBusPlugin.h
  IMenuInterface.h
  IVariableLayer.h
  J1939TimeOutCfg.h
  LINBusStatisticsDlg.h
  LINSignalExtractor.h
  LinChannelParam.h
  MainFrm.h
  MDIChildBase.h
  MessageAttrib.h
  MessageDetailsDlg.h
  MessageInterpretation.h
  MessageList.h
  MsgBufferConfigPage.h
  MsgFilterConfigPage.h
  MsgFrmtWnd.h
  MsgIDAttr.h
  MsgSgDetView.h
  MsgSgTreeView.h
  MsgSignal.h
  MsgSignalDBWnd.h
  MFCRibbonBarEx.h
  MsgWndHdrInfo.h
  MsgWndThread.h
  MultiLanguage.h
  IBusmasterPluginInterface.h
  IBusmasterPlugInManager.h
  IBusmasterPluginConnection.h
  IBusmasterPlugin.h
  NetworkStatistics.h
  NotificListbox.h
  NotificWnd.h
  PPageMessage.h
  Properties.h
  PSDI_Extern.h
  Resource.h
  RxMsgList.h
  SectionNames.h
  SigGrphConfigDlg.h
  SigGrphWndHandler.h
  SignalDetailsDlg.h
  Splash.h
  SplFileDlg.h
  Struct.h
  TreeItemParam.h
  TSEditorHandler.h
  TSExecutorHandler.h
  TxHandler.h
  TxMsgWndJ1939.h
  UIThread.h
  Utility.h
  UI/IMenuCreator.h
  UI/MenuCreator.h
  UI/Menus.h
  UI/BusmasterMenuItem.h
  UI/IdGenerator.h
  UI/IUICreator.h
  UI/UICreator.h
  UI/ToolBarCreator.h
  ValueDescriptionDlg.h
  VariableLayer.h
  WaveFormDataHandler.h
  WaveformSelectionDlg.h
  WaveformTransmitter.h
  WrapperErrorLogger.h
)

set(MIDL_FILE BUSMASTER.idl)

set(RESOURCE_LIST
  BUSMASTER.rc
  ${MIDL_FILE}
)

set(PCH_HEADER_FILES
  StdAfx.cpp
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} WIN32 ${SOURCE_LIST} ${HEADER_LIST} ${RESOURCE_LIST})

target_precompile_headers(${PROJECT_NAME} PRIVATE ${PCH_HEADER_FILES})

set_property(SOURCE ${MIDL_FILE} PROPERTY VS_SETTINGS 
            "InterfaceIdentifierFileName=BUSMASTER_Interface.c" 
            "HeaderFileName=BUSMASTER_Interface.h"
            "DllDataFileName=dlldata.c"
            "TypeLibraryName=BUSMASTER.tlb"
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}/$(IntDir)
  ${CMAKE_BINARY_DIR}/Sources/BUSMASTER/BusEmulation/BusEmulation.dir/${CMAKE_BUILD_TYPE}/ # workaround to find BusEmulation.h
  ..
  ${MFC_INCLUDE_DIRS}
  ${ATL_INCLUDE_DIRS}
  ${LIBXML2_INCLUDE_DIR}
  ${ICONV_INCLUDE_DIR}
  ../Include
)

add_dependencies(${PROJECT_NAME}
  BusEmulation
  BusmasterDriverInterface
  CAN_STUB
)

################################################################################
# Compile definitions
################################################################################
add_definitions(-Od -GF)

################################################################################
# Compile and link options
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:daouuid /MANIFEST:NO")
target_link_libraries(${PROJECT_NAME}
  Winmm shlwapi htmlhelp psapi
  CommonClass
  DataTypes
  Utils
  Filter
  FrameProcessor
  NodeSimEx
  ProjectConfiguration
  PSDI_CAN
  Replay
  SigGrphWnd
  SignalDefiner
  SignalWatch
  TestSuiteExecutorGUI
  TXWindow
  UDS_Protocol
)

if(MSVC)
  target_link_options(${PROJECT_NAME} PRIVATE /DEBUG)
endif()

################################################################################
# Post build events
################################################################################
add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory ARGS ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
  COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
  COMMAND ${CMAKE_COMMAND} ARGS -E copy ${CMAKE_CURRENT_SOURCE_DIR}/Res/Splsh16.bmp ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
  COMMAND ${CMAKE_COMMAND} ARGS -E copy ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.dir/${CMAKE_CFG_INTDIR}/BUSMASTER.tlb ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/BUSMASTER.tlb
  COMMAND ${CMAKE_COMMAND} ARGS -E copy ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.dir/${CMAKE_CFG_INTDIR}/BUSMASTER_Interface.h ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/BUSMASTER_Interface.h
  COMMAND ${CMAKE_COMMAND} ARGS -E copy ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.dir/${CMAKE_CFG_INTDIR}/BUSMASTER_Interface.c ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/BUSMASTER_Interface.c
)
