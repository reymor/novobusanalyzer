set(PROJECT_NAME Filter)

set(sources
  Filter.cpp
  FilterConfigDlg.cpp
  MainSubListDlg.cpp
  ../Application/MultiLanguage.cpp)

set(headers
  Filter_defines.h
  Filter_extern.h
  Filter_resource.h
  Filter_stdafx.h
  FilterConfigDlg.h
  MainSubListDlg.h
  ../Application/MultiLanguage.h)

set(resources
  Filter.rc)

add_library(${PROJECT_NAME} SHARED ${sources} ${headers} ${resources})

include_directories(
  ..
  ${ICONV_INCLUDE_DIR}
  ${LIBXML2_INCLUDE_DIR}
  ${ATL_INCLUDE_DIRS}
  ${MFC_INCLUDE_DIRS})

# compiler options
add_definitions(-D_AFXEXT)

# linker options
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:daouuid")
target_link_libraries(${PROJECT_NAME}
  DataTypes
  Utils)

if(MSVC)
  target_link_options(${PROJECT_NAME} PRIVATE /DEBUG)
endif()

# installer options
add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
  COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
)