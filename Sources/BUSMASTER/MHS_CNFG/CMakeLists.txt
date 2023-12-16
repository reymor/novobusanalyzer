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

add_library(mhsbmcfg STATIC ${sources} ${headers} ${resources})

include_directories(
  Res
  ..
  ${MFC_INCLUDE_DIRS})

# compiler options
set(CMAKE_MFC_FLAG 0)
add_definitions(-D_USRDLL -DMHSBMCFG_EXPORTS)

# linker options
set_target_properties(mhsbmcfg PROPERTIES LINK_FLAGS "/NODEFAULTLIB:daouuid")
target_link_libraries(mhsbmcfg
  comctl32)
