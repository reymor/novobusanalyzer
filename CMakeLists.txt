cmake_minimum_required(VERSION 3.27)
project(NovoBusAnalyzer)

################################################################################
# Novo Bus Analyzer version
################################################################################
set(BUSMASTER_VER 0.0.1)
add_definitions(-DBUSMASTER_VER=\"${BUSMASTER_VER}\")
set(CMAKE_BUILD_TYPE Release)

add_compile_definitions(NO_WARN_MBCS_MFC_DEPRECATION _CRT_SECURE_NO_WARNINGS)
################################################################################
# Sub-projects
################################################################################
add_subdirectory(Sources/Kernel)
add_subdirectory(Sources/BUSMASTER)
