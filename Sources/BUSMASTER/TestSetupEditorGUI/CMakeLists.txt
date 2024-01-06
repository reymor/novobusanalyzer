set(PROJECT_NAME TestSetupEditorGUI)

################################################################################
# Source, header and resources files
################################################################################
set(SOURCE_LIST
  ListCtrlEx.cpp
  TreeViewEx.cpp
  TestAutomationEditor.cpp
  TSEditorGUI_ChildFrame.cpp
  TSEditorGUI_PropertyView.cpp
  TSEditorGUI_SettingsDlg.cpp
  TestAutomationEditorDoc.cpp
  stdafx.cpp
)

set(HEADER_LIST
  ListCtrlEx.h
  TreeViewEx.h
  TSEditorGUI_ChildFrame.h
  TSEditorGUI_Definitions.h
  TSEditorGUI_Extern.h
  TSEditorGUI_PropertyView.h
  TSEditorGUI_resource.h
  TSEditorGUI_SettingsDlg.h
  TSEditorGUI_stdafx.h
  TestAutomationEditor.h
  TestAutomationEditorDoc.h
  Resource.h
  stdafx.h
)

set(RESOURCE_LIST
  TestSetupEditorGUI.rc
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} WIN32 ${SOURCE_LIST} ${HEADER_LIST} ${RESOURCE_LIST})

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
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:daouuid /MANIFEST:NO")
target_link_libraries(${PROJECT_NAME}
  BusmasterDBNetwork
  HTMLHELP
  DataTypes
  TestSetupEditorLib
  Utils
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
