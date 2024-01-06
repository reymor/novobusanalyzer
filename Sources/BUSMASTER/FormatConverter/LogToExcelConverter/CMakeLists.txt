set(PROJECT_NAME LogToExcelConverter)

set(sources
  ExportLogFileDlg.cpp
  LogToExcel.cpp
  LogToExcelConverter.cpp
  ../FormatConverterApp/MultiLanguage.cpp
  ../../Utility/MultiLanguageSupport.cpp)

set(headers
  Defines.h
  ExportLogFileDlg.h
  LogToExcel.h
  LogToExcelConverter.h
  Resource.h
  ../FormatConverterApp/MultiLanguage.h
  ../../Utility/MultiLanguageSupport.h)

set(resources
  LogToExcelConverter.rc)

add_library(${PROJECT_NAME} SHARED ${sources} ${headers} ${resources})

include_directories(
  ${GETTEXT_INCLUDE_DIR}
  ${MFC_INCLUDE_DIRS})

# linker options
target_link_libraries(${PROJECT_NAME}
  ${GETTEXT_LIBRARY}
  ${MFC_LIBRARIES})

# installer options
add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/ConverterPlugins/
  COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/ConverterPlugins/
)
