set(PROJECT_NAME SignalDefiner)

################################################################################
# Source, header and resources files
################################################################################
set(SOURCE_LIST
  ../Application/MultiLanguage.cpp
  SignalDefiner.cpp
  SignalDefinerDlg.cpp
)

set(HEADER_LIST
  ../Application/MultiLanguage.h
  SignalDefiner.h
  SignalDefiner_Extern.h
  SignalDefiner_Resource.h
  SignalDefiner_stdafx.h
  SignalDefinerDlg.h
)

set(RESOURCE_LIST
  SignalDefiner.rc
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} SHARED ${SOURCE_LIST} ${HEADER_LIST} ${RESOURCE_LIST})

include_directories(
  ..
  ${CMAKE_CURRENT_BINARY_DIR}/../EXTERNAL/DMGraph/DMGraph.dir/$<CONFIG>/ # workaround to find DMGraph.tlb
  ${ICONV_INCLUDE_DIR}
  ${LIBXML2_INCLUDE_DIR}
  ${ATL_INCLUDE_DIRS}
  ${MFC_INCLUDE_DIRS})

add_dependencies(${PROJECT_NAME}
  DMGraph
)

################################################################################
# Compile definitions
################################################################################
add_definitions(-D_USRDLL)

################################################################################
# Compile and link options
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:daouuid")

################################################################################
# Post build events
################################################################################
add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${PROJECT_SOURCE_DIR}/BIN/$<CONFIG>/
  COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:${PROJECT_NAME}> ${PROJECT_SOURCE_DIR}/BIN/$<CONFIG>/
)
