set(PROJECT_NAME DBC2DBFConverterLibrary)

set(sources
  dbc_dbf_Lexer.c
  DBC2DBFConverterDLL.cpp
  DBC2DBFConverterLibrary_stdafx.cpp
  DBFComment.cpp
  DBFConverter.cpp
  DBFMessage.cpp
  DBFParameter.cpp
  DBFParameterValues.cpp
  DBFSignal.cpp
  DBFValueDescriptor.cpp
  DBFValueTable.cpp
  Utility.cpp
  ../../Utility/MultiLanguageSupport.cpp)

set(headers
  DBC2DBFConverterLibrary_stdafx.h
  DBCConverterBase.h
  DBFComment.h
  DBFConverter.h
  DBFMessage.h
  DBFParameter.h
  DBFParameterValues.h
  DBFSignal.h
  DBFTagDefinitions.h
  DBFValueDescriptor.h
  DBFValueTable.h
  SignalValue.h
  Utility.h
  ../../Utility/MultiLanguageSupport.h)

add_library(${PROJECT_NAME} SHARED ${sources} ${headers})

set_target_properties(${PROJECT_NAME} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/ConverterPlugins/
  RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/ConverterPlugins/)

add_custom_command(OUTPUT dbc_dbf_Lexer.c
  COMMAND ${FLEX_EXECUTABLE}
  ARGS -i -L -odbc_dbf_Lexer.c ${CMAKE_CURRENT_SOURCE_DIR}/dbc_dbf_Lexer.l
  DEPENDS dbc_dbf_Lexer.l)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ../DBF2DBCConverter
  ${GETTEXT_INCLUDE_DIR}
  ${MFC_INCLUDE_DIRS})

# linker options
target_link_libraries(${PROJECT_NAME}
  ${GETTEXT_LIBRARY}
  ${MFC_LIBRARIES} -NODEFAULTLIB:daouuid)
