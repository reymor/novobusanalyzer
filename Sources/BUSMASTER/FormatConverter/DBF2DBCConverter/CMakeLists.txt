set(PROJECT_NAME DBF2DBCConverter)

set(sources
  Comment.cpp
  Converter.cpp
  DBF2DBCConverter.cpp
  DBF2DBCConverterDLL.cpp
  Message.cpp
  Parameter.cpp
  ParameterVal.cpp
  Signal.cpp
  Utility.cpp
  ValueDescriptor.cpp
  ValueTable.cpp
  ../../Utility/MultiLanguageSupport.cpp)

set(headers
  Comment.h
  Converter.h
  DBF2DBCConverter.h
  Definitions.h
  Message.h
  Parameter.h
  ParameterVal.h
  Signal.h
  SignalValue.h
  tag.h
  Utility.h
  ValueDescriptor.h
  ValueTable.h
  ../../Utility/MultiLanguageSupport.h)

set(resources
  DBF2DBCConverter.rc)

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
