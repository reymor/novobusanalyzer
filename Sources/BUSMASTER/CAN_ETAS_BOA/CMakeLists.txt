set(sources
  CAN_ETAS_BOA.cpp
  ChangeRegisters_CAN_ETAS_BOA.cpp
  ../Application/MultiLanguage.cpp
  ../DIL_Interface/HardwareListingCAN.cpp
)

set(headers
  CAN_ETAS_BOA.h
  CAN_ETAS_BOA_Extern.h
  CAN_ETAS_BOA_Resource.h
  CAN_ETAS_BOA_stdafx.h
  ChangeRegDefines.h
  ChangeRegisters_CAN_ETAS_BOA.h
  ../Application/MultiLanguage.h
  ../DIL_Interface/HardwareListingCAN.h
)

set(resources
  CAN_ETAS_BOA.rc)

add_library(CAN_ETAS_BOA_1_4 SHARED ${sources} ${headers} ${resources})
add_library(CAN_ETAS_BOA_1_5 SHARED ${sources} ${headers} ${resources})
add_library(CAN_ETAS_BOA_2 SHARED ${sources} ${headers} ${resources})

include_directories(
  ..
  ${ICONV_INCLUDE_DIR}
  ${LIBXML2_INCLUDE_DIR}
  ${ATL_INCLUDE_DIRS}
  ${MFC_INCLUDE_DIRS})

# compiler options
add_definitions(-D_USRDLL)
target_compile_definitions(CAN_ETAS_BOA_1_4 PUBLIC -DBOA_VERSION=BOA_VERSION_1_4)
target_compile_definitions(CAN_ETAS_BOA_1_5 PUBLIC -DBOA_VERSION=BOA_VERSION_1_5)
target_compile_definitions(CAN_ETAS_BOA_2   PUBLIC -DBOA_VERSION=BOA_VERSION_2)

# linker options
set_target_properties(CAN_ETAS_BOA_1_4 PROPERTIES LINK_FLAGS "/NODEFAULTLIB:daouuid")
set_target_properties(CAN_ETAS_BOA_1_5 PROPERTIES LINK_FLAGS "/NODEFAULTLIB:daouuid")
set_target_properties(CAN_ETAS_BOA_2   PROPERTIES LINK_FLAGS "/NODEFAULTLIB:daouuid")
target_link_libraries(CAN_ETAS_BOA_1_4
  Advapi32
  DataTypes
  Utils)
target_link_libraries(CAN_ETAS_BOA_1_5
  Advapi32
  DataTypes
  Utils)
target_link_libraries(CAN_ETAS_BOA_2
  Advapi32
  DataTypes
  Utils)

# installer options
add_custom_command(
  TARGET CAN_ETAS_BOA_1_4
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
  COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:CAN_ETAS_BOA_1_4> ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
)
add_custom_command(
  TARGET CAN_ETAS_BOA_1_5
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
  COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:CAN_ETAS_BOA_1_5> ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
)
add_custom_command(
  TARGET CAN_ETAS_BOA_2
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
  COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:CAN_ETAS_BOA_2> ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
)
