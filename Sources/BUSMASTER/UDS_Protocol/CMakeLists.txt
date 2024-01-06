set(PROJECT_NAME UDS_Protocol)

################################################################################
# Source, header and resources files
################################################################################
set(SOURCE_LIST
  stdafx.cpp
  UDS_NegRespMng.cpp
  UDS_Protocol.cpp
  UDS_TimmingWnd.cpp
  UDSMainWnd.cpp
  UDSSettingsWnd.cpp
)

set(HEADER_LIST
  resource.h
  stdafx.h
  UDS_Extern.h
  UDS_NegRespMng.h
  UDS_Protocol.h
  UDS_Resource.h
  UDS_TimmingWnd.h
  UDSMainWnd.h
  UDSSettingsWnd.h
  UDSWnd_Defines.h
)

set(RESOURCE_LIST
  uds.rc
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} SHARED ${SOURCE_LIST} ${HEADER_LIST} ${RESOURCE_LIST})

include_directories(
  ..
  ${ICONV_INCLUDE_DIR}
  ${LIBXML2_INCLUDE_DIR}
  ${MFC_INCLUDE_DIRS}
)

################################################################################
# Compile definitions
################################################################################
add_definitions(-D_AFXEXT)

################################################################################
# Dependencies
################################################################################
target_link_libraries(${PROJECT_NAME}
  BusmasterKernel
  HTMLHELP
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
