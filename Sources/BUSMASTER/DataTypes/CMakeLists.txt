set(PROJECT_NAME DataTypes)

################################################################################
# Source, header and resources files
################################################################################
set(SOURCE_LIST
  CanNsCodeGenHelper.cpp
  Filter_Datatypes.cpp
  J1939_DataTypes.cpp
  Log_Datatypes.cpp
  LinNsCodeGenHelper.cpp
  MainSubEntry.cpp
  MsgSignal_Datatypes.cpp
  NSCodeGenHelperFactory.cpp
  NodeSimCodeGenerator.cpp
  J1939NsCodeGenHelper.cpp
  ProjConfig_DataTypes.cpp
  UDS_DataTypes.cpp
)

set(HEADER_LIST
  Base_WrapperErrorLogger.h
  BaseAppServices.h
  DataTypes_stdafx.h
  Filter_Datatypes.h
  J1939_DataTypes.h
  INsCodeGenHelper.h
  Log_Datatypes.h
  MainSubEntry.h
  MsgSignal_Datatypes.h
  ProjConfig_DataTypes.h
  SigGrphWnd_Datatypes.h
  UDS_DataTypes.h
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${SOURCE_LIST} ${HEADER_LIST})

include_directories(
  ..
  ${ICONV_INCLUDE_DIR}
  ${LIBXML2_INCLUDE_DIR}
  ${ATL_INCLUDE_DIRS}
  ${MFC_INCLUDE_DIRS}
)

################################################################################
# Compile definitions
################################################################################
add_definitions(-D_LIB)

################################################################################
# Compile and link options
################################################################################
target_link_libraries(${PROJECT_NAME}
  ${GETTEXT_LIBRARY} ProtocolDefinitions
)
