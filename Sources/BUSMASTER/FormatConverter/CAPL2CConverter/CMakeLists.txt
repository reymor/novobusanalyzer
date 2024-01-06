set(PROJECT_NAME CAPL2CConverter)

################################################################################
# Source, header and resources files
################################################################################
set(SOURCE_LIST
  CAPL2CConverter.cpp
  CAPL2CConverterDLL.cpp
  CAPL2CPropertyPage.cpp
  EnvVarHandlerDlg.cpp
  SymbolTable.cpp
  ../FormatConverterApp/MultiLanguage.cpp
  ../../Utility/MultiLanguageSupport.cpp
  ../../Utility/WaitIndicator.cpp
)

set(HEADER_LIST
  CAPL_C_Lexer.h
  CAPL2CConverter.h
  CAPL2CConverter_Definitions.h
  CAPL2CConverter_Resource.h
  CAPL2CConverter_stdafx.h
  CAPL2CPropertyPage.h
  ConstString.h
  EnvVarHandlerDlg.h
  LexerHandlers.h
  LexerHandlers.hpp
  SymbolTable.h
  ../FormatConverterApp/MultiLanguage.h
  ../../Utility/MultiLanguageSupport.h
  ../../Utility/WaitIndicator.h
)

set(RESOURCE_LIST
  Resource.rc)

add_library(${PROJECT_NAME} SHARED ${SOURCE_LIST} ${HEADER_LIST} ${RESOURCE_LIST})

add_custom_command(OUTPUT CAPL_C_Lexer.h
  COMMAND ${FLEX_EXECUTABLE}
  ARGS -i -L -oCAPL_C_Lexer.h ${CMAKE_CURRENT_SOURCE_DIR}/lexer_rule.l
  DEPENDS lexer_rule.l
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${GETTEXT_INCLUDE_DIR}
  ${MFC_INCLUDE_DIRS}
)

# linker options
target_link_libraries(${PROJECT_NAME}
  DBC2DBFConverterLibrary
  ${GETTEXT_LIBRARY}
  ${MFC_LIBRARIES}
)

################################################################################
# Post build events
################################################################################
add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/ConverterPlugins/
  COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/ConverterPlugins/
)
