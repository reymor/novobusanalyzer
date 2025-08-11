set(PROJECT_NAME BlfLibrary)

set(sources
  Src/Kernel/BinHelper.cpp
  Src/Kernel/BlfLibrary.cpp
  Src/Kernel/ErrorManager.cpp
  Src/Kernel/Out.cpp)

set(headers
  Src/IBlfLibrary.h
  Src/Kernel/BinHelper.h
  Src/Kernel/BlfFormat.h
  Src/Kernel/BlfLibrary.h
  Src/Kernel/ErrorManager.h
  Src/Kernel/Out.h
  Src/Kernel/Strings.h)

add_library(${PROJECT_NAME} SHARED ${sources} ${headers})

set_target_properties(${PROJECT_NAME} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/ConverterPlugins/
  RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/ConverterPlugins/)
  
target_include_directories(${PROJECT_NAME} 
  INTERFACE Src
)

include_directories(
  ${ZLIB_INCLUDE_DIR})

# compiler options
add_definitions(-DBLFLIBRARY_EXPORTS -D_WINDLL)

# linker options
target_link_libraries(${PROJECT_NAME}
  ${ZLIB_LIBRARY})
