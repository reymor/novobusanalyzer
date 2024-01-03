set(PROJECT_NAME CAN_NSI)

set(sources
  AcceptanceFilterDlg.cpp
  CAN_NSI.cpp
  CAN_NSI_stdafx.cpp
  CANRegAnalysis.cpp
  ChangeRegisters.cpp
  ../Application/MultiLanguage.cpp
  ../DIL_Interface/HardwareListingCAN.cpp
)

set(headers
  AcceptanceFilterDlg.h
  CAN_NSI.h
  CAN_NSI_Extern.h
  CAN_NSI_Resource.h
  CAN_NSI_stdafx.h
  ChangeRegDefines.h
  ChangeRegisters.h
  ../Application/MultiLanguage.h)

set(resources
  CAN_NSI.rc)

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
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/SAFESEH:NO")
target_link_libraries(${PROJECT_NAME}
  ${CMAKE_CURRENT_SOURCE_DIR}/NSICANEX.lib
  DataTypes
  Utils)

# installer options
add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${PROJECT_SOURCE_DIR}/BIN/${CMAKE_BUILD_TYPE}/
  COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:${PROJECT_NAME}> ${PROJECT_SOURCE_DIR}/BIN/${CMAKE_BUILD_TYPE}/)
