set(PROJECT_NAME DMGraph)

set(sources
  AnnoPropPage.cpp
  ColPickerBtn.cpp
  CursorPropPage.cpp
  DMGraph.cpp
  DMGraphCtrl.cpp
  DMGraphCursorState.cpp
  DMGraphPropPage.cpp
  DrawFct.cpp
  ElementPropPage.cpp
  FormatPropPage.cpp
  GraphAnno.cpp
  GraphAxis.cpp
  GraphCollection.cpp
  GraphCursor.cpp
  GraphElement.cpp
  PropPageBaseWnd.cpp
  RectTracker.cpp
  StdAfx.cpp)

set(headers
  about.h
  AnnoPropPage.h
  ColPickerBtn.h
  CursorPropPage.h
  DMGraph_Defines.h
  DMGraphCP.h
  DMGraphCtrl.h
  DMGraphCursorState.h
  DMGraphPropPage.h
  DMGraphVer.h
  DrawFct.h
  ElementPoint.h
  ElementPropPage.h
  FormatPropPage.h
  GraphAnno.h
  GraphAxis.h
  GraphCollection.h
  GraphCursor.h
  GraphElement.h
  GraphItem.h
  PropPageBaseWnd.h
  RectTracker.h
  Resource.h
  StdAfx.h)

set(resources
  DMGraph.def
  DMGraph.idl
  DMGraph.rc)

add_library(${PROJECT_NAME} SHARED ${sources} ${headers} ${resources})

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}/$(IntDir)
  ${ATL_INCLUDE_DIRS})

# compiler options
add_definitions(-Gy -GF -MT)
remove_definitions(-GR -MD)

# linker options
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:daouuid /NXCOMPAT:NO")
target_link_libraries(${PROJECT_NAME}
  comctl32)

# installer options
add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
  COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
)
