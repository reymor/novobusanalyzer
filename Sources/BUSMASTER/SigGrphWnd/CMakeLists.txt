set(PROJECT_NAME SigGrphWnd)

set(sources
  GraphBottomView.cpp
  GraphChildFrame.cpp
  GraphConfiguration.cpp
  GraphElement.cpp
  GraphExportDlg.cpp
  GraphLeftView.cpp
  GraphList.cpp
  GraphParameters.cpp
  GraphRightView.cpp
  GraphSink.cpp
  MDIChildBase.cpp
  MessageList.cpp
  ../Application/MultiLanguage.cpp
  SigGrphWnd.cpp)

set(headers
  GraphBottomView.h
  GraphChildFrame.h
  GraphConfiguration.h
  GraphElement.h
  GraphExportDlg.h
  GraphLeftView.h
  GraphList.h
  GraphParameters.h
  GraphRightView.h
  GraphSink.h
  MDIChildBase.h
  MessageList.h
  ../Application/MultiLanguage.h
  SigGrphWnd_Defines.h
  SigGrphWnd_Extern.h
  SigGrphWnd_Resource.h
  SigGrphWnd_stdafx.h)

set(resources
  SigGrphWnd.rc)

add_library(${PROJECT_NAME} SHARED ${sources} ${headers} ${resources})

include_directories(
  ..
  ${CMAKE_CURRENT_BINARY_DIR}/../EXTERNAL/DMGraph/DMGraph.dir/${CMAKE_BUILD_TYPE}/ # workaround to find DMGraph.tlb
  ${ICONV_INCLUDE_DIR}
  ${LIBXML2_INCLUDE_DIR}
  ${ATL_INCLUDE_DIRS}
  ${MFC_INCLUDE_DIRS})

# compiler options
add_definitions(-D_AFXEXT)

# linker options
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:daouuid")
target_link_libraries(${PROJECT_NAME}
  DMGraph
  DataTypes
  Utils
  Utilities
)

# installer options
add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
  COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
)
