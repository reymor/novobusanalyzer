set(PROJECT_NAME FormatConverter)

################################################################################
# Source, header and resources files
################################################################################
set(SOURCE_LIST
  DefConverterPage.cpp
  FormatConverterApp.cpp
  FormatConverterWnd.cpp
  MultiLanguage.cpp
  PluginManagerBase.cpp
  PluginManagerDLL.cpp
  stdafx.cpp
  ../../Utility/MultiLanguageSupport.cpp
)

set(HEADER_LIST
  BaseConverter.h
  DefConverterPage.h
  Definitions.h
  FormatConverterApp.h
  FormatConverterWnd.h
  GettextBusmaster.h
  MultiLanguage.h
  PluginManagerBase.h
  PluginManagerDLL.h
  resource.h
  stdafx.h
  ../../Utility/MultiLanguageSupport.h
)

set(RESOURCE_LIST
  FormatConverter.rc
)

add_executable(${PROJECT_NAME} WIN32 ${SOURCE_LIST} ${HEADER_LIST} ${RESOURCE_LIST})

include_directories(
  ${GETTEXT_INCLUDE_DIR}
  ${MFC_INCLUDE_DIRS}
)

set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:daouuid /MANIFEST:NO")

# linker options
target_link_libraries(${PROJECT_NAME}
  ${GETTEXT_LIBRARY}
  ${MFC_LIBRARIES} 
  shlwapi.lib
  htmlhelp
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
