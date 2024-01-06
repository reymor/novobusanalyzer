project(NovoBusAnalyzerKernel CXX)

################################################################################
# Sub-projects
################################################################################
add_subdirectory(BusmasterDBNetwork)
add_subdirectory(BusmasterDriverInterface)
add_subdirectory(BusmasterDriverInterface/DIL_J1939)
add_subdirectory(BusmasterKernel)
add_subdirectory(ProtocolDefinitions)
add_subdirectory(Utilities)
