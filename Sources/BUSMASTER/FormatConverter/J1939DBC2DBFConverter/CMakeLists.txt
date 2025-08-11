set(PROJECT_NAME J1939DBC2DBFConverter)

set(sources
  J1939DBC2DBFConverter.cpp
  J1939DBC2DBFConverter_stdafx.cpp
  ../../Utility/MultiLanguageSupport.cpp)

set(headers
  J1939DBC2DBFConverter.h
  J1939DBC2DBFConverter_stdafx.h
  ../../Utility/MultiLanguageSupport.h)

add_library(${PROJECT_NAME} SHARED ${sources} ${headers})

set_target_properties(${PROJECT_NAME} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/ConverterPlugins/
  RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/ConverterPlugins/)

include_directories(
  ${GETTEXT_INCLUDE_DIR}
  ${MFC_INCLUDE_DIRS})

# linker options
target_link_libraries(${PROJECT_NAME}
  DBC2DBFConverterLibrary
  ${GETTEXT_LIBRARY}
  ${MFC_LIBRARIES})
