set(PROJECT_NAME Replay)

################################################################################
# Source, header and resources files
################################################################################
set(SOURCE_LIST
  MsgReplayWnd.cpp
  ../Application/MultiLanguage.cpp
  OwnerDataListCtrl.cpp
  Replay.cpp
  ReplayFile.cpp
  ReplayFileConfigDlg.cpp
  ReplayManager.cpp
  ReplayProcess.cpp
  Utility_Replay.cpp
)

set(HEADER_LIST
  MsgReplayWnd.h
  ../Application/MultiLanguage.h
  OwnerDataListCtrl.h
  Replay_Extern.h
  Replay_resource.h
  Replay_stdafx.h
  Replay_Struct.h
  ReplayFile.h
  ReplayFileConfigDlg.h
  ReplayManager.h
  ReplayProcess.h
  Utility_Replay.h
)

set(RESOURCE_LIST
  Replay.rc)

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
  BusmasterKernel
  Filter
  Winmm
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
  COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
  COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
)
