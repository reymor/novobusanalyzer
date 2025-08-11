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

set_target_properties(${PROJECT_NAME} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/ConverterPlugins/
  RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/ConverterPlugins/)

include_directories(
  ${GETTEXT_INCLUDE_DIR}
  ${MFC_INCLUDE_DIRS})

# linker options
target_link_libraries(${PROJECT_NAME}
  ${GETTEXT_LIBRARY}
  ${MFC_LIBRARIES})
