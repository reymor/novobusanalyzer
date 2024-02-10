set(PROJECT_NAME SignalWatch)

################################################################################
# Source, header and resources files
################################################################################
set(SOURCE_LIST
  ../Application/MultiLanguage.cpp
  BaseSignalWatchImp.cpp
  CheckBoxTree.cpp
  SignalWatch.cpp
  SignalWatch_CAN.cpp
  SignalWatch_J1939.cpp
  SignalWatchListBox.cpp
  MsgSignalSelect.cpp
  SignalWatch_LIN.cpp
  SigWatchDlg.cpp
)

set(HEADER_LIST
  ../Application/MultiLanguage.h
  CheckBoxTree.h
  SignalWatch.h
  SignalWatch_CAN.h
  SignalWatch_Extern.h
  SignalWatch_J1939.h
  MsgSignalSelect.h
  SignalWatch_LIN.h
  SignalWatch_Resource.h
  SignalWatch_stdafx.h
  SignalWatchDefs.h
  SignalWatchListBox.h
  SigWatchDlg.h
)

set(RESOURCE_LIST
  SignalWatch.rc
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
add_definitions(-D_USRDLL)

################################################################################
# Compile and link options
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:daouuid")
target_link_libraries(${PROJECT_NAME}
  DataTypes
  Utils
  Utilities
  BusmasterKernel
)

if(MSVC)
  target_link_options(${PROJECT_NAME} PRIVATE /DEBUG)
  target_compile_options(${PROJECT_NAME} PRIVATE /Zi)
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
