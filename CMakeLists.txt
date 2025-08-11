cmake_minimum_required(VERSION 3.27)

################################################################################
# Common project definitions
################################################################################
set(CMAKE_GENERATOR_PLATFORM "Win32" CACHE INTERNAL "" FORCE)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Sources/BUSMASTER/BIN)
add_compile_definitions(NO_WARN_MBCS_MFC_DEPRECATION _CRT_SECURE_NO_WARNINGS)

project(NovoBusAnalyzer)

################################################################################
# Novo Bus Analyzer version
################################################################################
set(BUSMASTER_VER 0.0.1)
add_definitions(-DBUSMASTER_VER=\"${BUSMASTER_VER}\")

################################################################################
# Qt configuration
################################################################################
set(Qt5_DIR "C:/Qt/Qt5.14.2/5.14.2/msvc2017/lib/cmake/Qt5")
set(Qt5_BIN_DIR "C:/Qt/Qt5.14.2/5.14.2/msvc2017/bin")

################################################################################
# Sub-projects
################################################################################
add_subdirectory(Sources/Kernel)
add_subdirectory(Sources/BUSMASTER)
