set(PROJECT_NAME DBC2DBFConverter)

set(sources
  DBC2DBFConverter.cpp
  DBC2DBFConverter_stdafx.cpp
  ../../Utility/MultiLanguageSupport.cpp)

set(headers
  DBC2DBFConverter.h
  DBC2DBFConverter_stdafx.h
  ../../Utility/MultiLanguageSupport.h)

set(resources
  DBC2DBFConverter.rc)

add_library(${PROJECT_NAME} SHARED ${sources} ${headers} ${resources})

set_target_properties(${PROJECT_NAME} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/ConverterPlugins/
  RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/ConverterPlugins/)

include_directories(
  ../DBF2DBCConverter
  ${GETTEXT_INCLUDE_DIR}
  ${MFC_INCLUDE_DIRS})

# linker options
target_link_libraries(${PROJECT_NAME}
  DBC2DBFConverterLibrary
  ${GETTEXT_LIBRARY}
  ${MFC_LIBRARIES})
