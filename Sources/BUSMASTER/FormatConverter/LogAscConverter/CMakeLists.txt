set(PROJECT_NAME LogAscConverter)

################################################################################
# Source, header and resources files
################################################################################
set(SOURCE_LIST
  Log_Asc_Lexer.c
  Log_Asc_Parser.c
  LogAscConverter.cpp
  LogAscConverterDLL.cpp
  Utility.cpp
  ../../Utility/MultiLanguageSupport.cpp
)

set(HEADER_LIST
  Log_Asc_Parser.h
  LogAscConverter.h
  ../../Utility/MultiLanguageSupport.h
)

set(RESOURCE_LIST
  LogAscConverter.rc
)

add_library(${PROJECT_NAME} SHARED ${SOURCE_LIST} ${HEADER_LIST} ${RESOURCE_LIST})

set_target_properties(${PROJECT_NAME} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/ConverterPlugins/
  RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/ConverterPlugins/)

add_custom_command(OUTPUT Log_Asc_Lexer.c
  COMMAND ${FLEX_EXECUTABLE}
  ARGS -i -L -oLog_Asc_Lexer.c ${CMAKE_CURRENT_SOURCE_DIR}/Log_Asc_Lexer.l
  DEPENDS Log_Asc_Lexer.l)

add_custom_command(OUTPUT Log_Asc_Parser.c Log_Asc_Parser.h
  COMMAND ${BISON_EXECUTABLE}
  ARGS -d -l -o${CMAKE_CURRENT_BINARY_DIR}/Log_Asc_Parser.c ${CMAKE_CURRENT_SOURCE_DIR}/Log_Asc_Parser.y
  DEPENDS Log_Asc_Parser.y
  WORKING_DIRECTORY ${BISON_PATH})
add_custom_target(generate_log_asc_parser DEPENDS Log_Asc_Parser.c)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${GETTEXT_INCLUDE_DIR}
  ${MFC_INCLUDE_DIRS})

# linker options
target_link_libraries(${PROJECT_NAME}
  ${GETTEXT_LIBRARY}
  ${MFC_LIBRARIES}
)
