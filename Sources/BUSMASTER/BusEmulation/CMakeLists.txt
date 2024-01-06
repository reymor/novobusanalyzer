set(PROJECT_NAME BusEmulation)

set(sources
  BusEmulation.cpp
  SimENG.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/BusEmulation.dir/${CMAKE_CFG_INTDIR}/BusEmulation_i.c # workaround
  ${CMAKE_CURRENT_BINARY_DIR}/BusEmulation.dir/${CMAKE_CFG_INTDIR}/BusEmulation_p.c # workaround
  ${CMAKE_CURRENT_BINARY_DIR}/BusEmulation.dir/${CMAKE_CFG_INTDIR}/dlldata.c) # workaround

set(headers
  resource_BusSim.h
  SimENG.h
  ${CMAKE_CURRENT_BINARY_DIR}/BusEmulation.dir/${CMAKE_CFG_INTDIR}/BusEmulation.h) # workaround

set(resources
  BusEmulation.idl
  BusEmulation.rc
  BusEmulationPS.def)

set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/BusEmulation.dir/${CMAKE_CFG_INTDIR}/BusEmulation_i.c PROPERTIES GENERATED TRUE)
set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/BusEmulation.dir/${CMAKE_CFG_INTDIR}/BusEmulation_p.c PROPERTIES GENERATED TRUE)
set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/BusEmulation.dir/${CMAKE_CFG_INTDIR}/BusEmulation.h PROPERTIES GENERATED TRUE)
set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/BusEmulation.dir/${CMAKE_CFG_INTDIR}/dlldata.c PROPERTIES GENERATED TRUE)

add_executable(${PROJECT_NAME} WIN32 ${sources} ${headers} ${resources})

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}/$(IntDir)
  ..
  ${ICONV_INCLUDE_DIR}
  ${LIBXML2_INCLUDE_DIR}
  ${ATL_INCLUDE_DIRS}
  ${MFC_INCLUDE_DIRS})

# compiler options
set(CMAKE_MFC_FLAG 0)

# linker options
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:daouuid")
target_link_libraries(${PROJECT_NAME}
  Utilities
  BusmasterKernel
  RpcRT4
  comctl32
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
