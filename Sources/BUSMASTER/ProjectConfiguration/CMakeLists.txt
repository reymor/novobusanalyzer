set(PROJECT_NAME ProjectConfiguration)

set(sources
  operations_file.cpp
  ProjConfig.cpp
  projConfigManager.cpp
  ProjectConfiguration.cpp)

set(headers
  operations_file.h
  ProjConfig.h
  projConfigManager.h
  ProjectConfiguration.h
  ProjectConfiguration_extern.h
  StdAfx_ProjectConfiguration.h)

add_library(${PROJECT_NAME} SHARED ${sources} ${headers})

include_directories(
  ..
  ${ICONV_INCLUDE_DIR}
  ${LIBXML2_INCLUDE_DIR}
  ${ATL_INCLUDE_DIRS}
  ${MFC_INCLUDE_DIRS}
)

# compiler options
add_definitions(-D_USRDLL)

# linker options
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:daouuid")
target_link_libraries(${PROJECT_NAME}
  DataTypes)

if(MSVC)
  target_link_options(${PROJECT_NAME} PRIVATE /DEBUG)
  target_compile_options(${PROJECT_NAME} PRIVATE /Zi)
endif()

# installer options
add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
  COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
)
