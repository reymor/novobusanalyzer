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

include_directories(
  ${GETTEXT_INCLUDE_DIR}
  ${MFC_INCLUDE_DIRS})

# linker options
target_link_libraries(${PROJECT_NAME}
  DBC2DBFConverterLibrary
  ${GETTEXT_LIBRARY}
  ${MFC_LIBRARIES})

# installer options
add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/ConverterPlugins/
  COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/ConverterPlugins/
)
