set(sources
  Filter_Datatypes.cpp
  J1939_DataTypes.cpp
  Log_Datatypes.cpp
  MainSubEntry.cpp
  MsgSignal_Datatypes.cpp
  ProjConfig_DataTypes.cpp
  Struct_BUS.cpp
  UDS_DataTypes.cpp)

set(headers
  Base_WrapperErrorLogger.h
  BaseAppServices.h
  DataTypes_stdafx.h
  DIL_Datatypes_.h
  Filter_Datatypes.h
  J1939_DataTypes.h
  Log_Datatypes.h
  MainSubEntry.h
  MsgSignal_Datatypes.h
  ProjConfig_DataTypes.h
  SigGrphWnd_Datatypes.h
  UDS_DataTypes.h)

add_library(DataTypes STATIC ${sources} ${headers})

include_directories(
  ..
  ${ICONV_INCLUDE_DIR}
  ${LIBXML2_INCLUDE_DIR}
  ${ATL_INCLUDE_DIRS}
  ${MFC_INCLUDE_DIRS})

# compiler options
add_definitions(-D_LIB)

# linker options
target_link_libraries(DataTypes
  ${GETTEXT_LIBRARY})
