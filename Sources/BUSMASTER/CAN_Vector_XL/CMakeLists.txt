set(PROJECT_NAME CAN_Vector_XL)

set(sources
  AcceptanceFilterDlg.cpp
  CAN_Vector_XL.cpp
  CANRegAnalysis.cpp
  ChangeRegisters.cpp
  ../Application/MultiLanguage.cpp
  ../DIL_Interface/HardwareListingCAN.cpp
)

set(headers
  AcceptanceFilterDlg.h
  CAN_Vector_XL.h
  CAN_Vector_XL_Extern.h
  CAN_Vector_XL_Resource.h
  CAN_Vector_XL_stdafx.h
  ChangeRegDefines.h
  ChangeRegisters.h
  ContrConfigPeakUsbDefs.h
  ../Application/MultiLanguage.h)

set(resources
  CAN_Vector_XL.rc)

add_library(${PROJECT_NAME} SHARED ${sources} ${headers} ${resources})

include_directories(
  ..
  ${ICONV_INCLUDE_DIR}
  ${LIBXML2_INCLUDE_DIR}
  ${ATL_INCLUDE_DIRS}
  ${MFC_INCLUDE_DIRS})

# compiler options
add_definitions(-D_USRDLL)

# linker options
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:daouuid")
target_link_libraries(${PROJECT_NAME}
  Advapi32
  DataTypes
  Utils
)

# installer options
add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
  COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
)
