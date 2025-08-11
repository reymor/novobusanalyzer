set(PROJECT_NAME BlfLogConverter)

set(sources
  BlfLogConverter.cpp
  BlfLogConverterDLL.cpp
  ../../Utility/MultiLanguageSupport.cpp)

set(headers
  BlfLogConverter.h
  Resource.h
  ../../Utility/MultiLanguageSupport.h)

set(resources
  BlfLogConverter.rc)

add_library(${PROJECT_NAME} SHARED ${sources} ${headers} ${resources})

set_target_properties(${PROJECT_NAME} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/ConverterPlugins/
  RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/ConverterPlugins/)

include_directories(
  ${GETTEXT_INCLUDE_DIR}
  ${MFC_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME}
  BlfLibrary
  ${GETTEXT_LIBRARY}
  ${MFC_LIBRARIES})
