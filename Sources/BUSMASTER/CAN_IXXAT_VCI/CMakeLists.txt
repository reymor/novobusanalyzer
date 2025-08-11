set(PROJECT_NAME CAN_IXXAT_VCI)

set(sources
  CAN_IXXAT_VCI.cpp
  CAN_IXXAT_VCI_stdafx.cpp
  CANControllerConfigDlg.cpp
  CANSelectDlg.cpp
  ClientBuffer.cpp
  ClientList.cpp
  DIL_CAN_IXXAT_VCI.cpp
  IxxatCanChannel.cpp
  ../Application/MultiLanguage.cpp
  ../DIL_Interface/HardwareListingCAN.cpp
  vcinpldynl.cpp)

set(headers
  AllIncludes.h
  CAN_IXXAT_VCI.h
  CAN_IXXAT_VCI_Extern.h
  CAN_IXXAT_VCI_stdafx.h
  CANControllerConfigDlg.h
  CANSelectDlg.h
  ClientBuffer.h
  ClientList.h
  DIL_CAN_IXXAT_VCI.h
  IxxatCanChannel.h
  ../Application/MultiLanguage.h
  Resource.h
  targetver.h
  vcinpldynl.h)

set(resources
  CAN_IXXAT_VCI.rc)

add_library(${PROJECT_NAME} SHARED ${sources} ${headers} ${resources})

include_directories(
  ..
  ../Include
  EXTERNAL/inc
  ${ICONV_INCLUDE_DIR}
  ${LIBXML2_INCLUDE_DIR}
  ${ATL_INCLUDE_DIRS}
  ${MFC_INCLUDE_DIRS})

# compiler options
add_definitions(-D_USRDLL)

# linker options
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:daouuid")
target_link_libraries(${PROJECT_NAME}
  Utils)
