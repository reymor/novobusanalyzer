set(PROJECT_NAME PSDI_CAN)

################################################################################
# Source, header and resources files
################################################################################
set(SOURCE_LIST
  MsgContainer_CAN.cpp
  MsgContainer_J1939.cpp
  MsgContainer_LIN.cpp
  PSDI_CAN.cpp
  ../Application/MessageAttrib.cpp
)

set(HEADER_LIST
  MsgContainer_CAN.h
  MsgContainer_J1939.h
  MsgContainer_LIN.h
  PSDI_CAN.h
  stdafx_CAN.h
  ../Utility/Utility_Thread.h
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} SHARED ${SOURCE_LIST} ${HEADER_LIST})

include_directories(
  ..
  ${ICONV_INCLUDE_DIR}
  ${LIBXML2_INCLUDE_DIR}
  ${MFC_INCLUDE_DIRS}
)

################################################################################
# Compile definitions
################################################################################
add_definitions(-D_USRDLL)

################################################################################
# Compile and link options
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:daouuid")
target_link_libraries(${PROJECT_NAME}
  CommonClass
  DataTypes
  Utils
  "${CMAKE_SOURCE_DIR}/../Kernel/Bin/$(Configuration)/Utilities.lib"
  "${CMAKE_SOURCE_DIR}/../Kernel/Bin/BusmasterKernel/$(Configuration)/BusmasterKernel.lib"
  UDS_Protocol
)

################################################################################
# Post build events
################################################################################
add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${PROJECT_SOURCE_DIR}/BIN/$<CONFIG>/
  COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:${PROJECT_NAME}> ${PROJECT_SOURCE_DIR}/BIN/$<CONFIG>/
)
