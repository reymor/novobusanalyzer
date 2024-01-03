
set(PROJECT_NAME MHS_CNFG)

set(sources
  src/about.c
  src/can_setup.cpp
  src/gui_util.cpp
  src/mhsbmcfg.cpp
  src/util.c)

set(headers
  src/can_setup.h
  src/global.h
  src/gui_util.h
  src/mhsbmcfg.h)

set(resources
  Res/mhsbmcfg.rc)

add_library(${PROJECT_NAME} STATIC ${sources} ${headers} ${resources})

include_directories(
  Res
  .
  ${MFC_INCLUDE_DIRS})

# compiler options
set(CMAKE_MFC_FLAG 0)
add_definitions(-D_USRDLL -DMHSBMCFG_EXPORTS)

# linker options
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/NODEFAULTLIB:daouuid")
target_link_libraries(${PROJECT_NAME}
  comctl32)
