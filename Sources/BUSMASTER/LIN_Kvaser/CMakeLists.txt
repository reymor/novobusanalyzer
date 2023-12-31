set(PROJECT_NAME LIN_Kvaser)

set(sources
  ../DIL_Interface/CommanDIL_LIN.cpp
  ../DIL_Interface/HardwareListing.cpp
  LIN_Kvaser.cpp
  LIN_Kvaser_stdafx.cpp)

set(headers
  ../DIL_Interface/CommanDIL_LIN.h
  LIN_Kvaser.h
  LIN_Kvaser_Defines.h
  LIN_Kvaser_Extern.h
  LIN_Kvaser_Resource.h
  LIN_Kvaser_stdafx.h)

set(resources
  LIN_Kvaser.rc)

#add_library(LIN_Kvaser_1_4 SHARED ${sources} ${headers} ${resources})
add_library(${PROJECT_NAME} SHARED ${sources} ${headers} ${resources})
#add_library(LIN_Kvaser_2 SHARED ${sources} ${headers} ${resources})

include_directories(
  ..
  ${ICONV_INCLUDE_DIR}
  ${LIBXML2_INCLUDE_DIR}
  ${ATL_INCLUDE_DIRS}
  ${MFC_INCLUDE_DIRS})

# compiler options
add_definitions(-D_USRDLL)
#target_compile_definitions(LIN_Kvaser_1_4 PUBLIC -DBOA_VERSION=BOA_VERSION_1_4)
target_compile_definitions(${PROJECT_NAME} PUBLIC -DBOA_VERSION=BOA_VERSION_1_5)
#target_compile_definitions(LIN_Kvaser_2   PUBLIC -DBOA_VERSION=BOA_VERSION_2)

# linker options
#set_target_properties(LIN_Kvaser_1_4 PROPERTIES LINK_FLAGS "/NODEFAULTLIB:daouuid")
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:daouuid")
#set_target_properties(LIN_Kvaser_2   PROPERTIES LINK_FLAGS "/NODEFAULTLIB:daouuid")
#target_link_libraries(LIN_Kvaser_1_4
#  Advapi32
#  DataTypes
#  Utils)
target_link_libraries(${PROJECT_NAME}
  ${CMAKE_CURRENT_SOURCE_DIR}/EXTERNAL/Lib/MS/canlib32.lib
  ${CMAKE_CURRENT_SOURCE_DIR}/EXTERNAL/Lib/MS/linlib.lib
  Advapi32
  DataTypes
  Utils)
#target_link_libraries(LIN_Kvaser_2
#  Advapi32
#  DataTypes
#  Utils)

# installer options
#add_custom_command(
#  TARGET LIN_Kvaser_1_4
#  POST_BUILD
#  COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${PROJECT_SOURCE_DIR}/BIN/${CMAKE_BUILD_TYPE}/
#  COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:LIN_Kvaser_1_4> ${PROJECT_SOURCE_DIR}/BIN/${CMAKE_BUILD_TYPE}/)
add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
  COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/LIN_Kvaser.dll
)
#  COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:LIN_Kvaser_1_5> ${PROJECT_SOURCE_DIR}/BIN/${CMAKE_BUILD_TYPE}/)
#add_custom_command(
#  TARGET LIN_Kvaser_2
#  POST_BUILD
#  COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${PROJECT_SOURCE_DIR}/BIN/${CMAKE_BUILD_TYPE}/
#  COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:LIN_Kvaser_2> ${PROJECT_SOURCE_DIR}/BIN/${CMAKE_BUILD_TYPE}/)
