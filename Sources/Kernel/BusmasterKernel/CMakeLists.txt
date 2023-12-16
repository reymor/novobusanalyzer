set(PROJECT_NAME BusmasterKernel)

################################################################################
# Source groups
################################################################################
set(Header_Files
    "BusMasterKernel.h"
    "stdafx.h"
    "targetver.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "BusMasterKernel.cpp"
    "dllmain.cpp"
    "stdafx.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
    ${Header_Files}
    ${Source_Files}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} SHARED ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE BusmasterKernel)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_BUSMASTER_DEBUG "${TARGET_NAME}$ENV{TargetExt}"
    TARGET_NAME_DEBUG           "${TARGET_NAME}$ENV{TargetExt}"
    TARGET_NAME_RELEASE         "${TARGET_NAME}$ENV{TargetExt}"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_BUSMASTER_DEBUG "$<CONFIG>"
    OUTPUT_DIRECTORY_DEBUG           "$<CONFIG>"
    OUTPUT_DIRECTORY_RELEASE         "$<CONFIG>"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION_BUSMASTER_DEBUG "TRUE"
    INTERPROCEDURAL_OPTIMIZATION_RELEASE         "TRUE"
)
################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:busmaster_debug>:"
        "NDEBUG"
    ">"
    "$<$<CONFIG:Debug>:"
        "_DEBUG"
    ">"
    "$<$<CONFIG:Release>:"
        "NDEBUG"
    ">"
    "WIN32;"
    "_WINDOWS;"
    "_USRDLL;"
    "BUSMASTERKERNEL_EXPORTS;"
    "_MBCS"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:busmaster_debug>:
            /O2;
            /Oi;
            /Gy
        >
        $<$<CONFIG:Debug>:
            /Od
        >
        $<$<CONFIG:Release>:
            /O2;
            /Oi;
            /Gy
        >
        /sdl;
        /W3;
        ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
        ${DEFAULT_CXX_EXCEPTION_HANDLING};
        /Y-
    )
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    source_file_compile_options(dllmain.cpp ${FILE_CL_OPTIONS})
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:busmaster_debug>:
            /OPT:REF;
            /OPT:ICF;
            /INCREMENTAL:NO
        >
        $<$<CONFIG:Debug>:
            /INCREMENTAL
        >
        $<$<CONFIG:Release>:
            /OPT:REF;
            /OPT:ICF;
            /INCREMENTAL:NO
        >
        /DEBUG;
        /SUBSYSTEM:WINDOWS;
        "$(SolutionDir)/$(Configuration)/BusmasterDBNetwork.lib"
    )
endif()

################################################################################
# Post build events
################################################################################
add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ARGS "$<SHELL_PATH:${CMAKE_SOURCE_DIR}/>..\\BUSMASTER\\BIN\\$<CONFIG>\\"
    COMMAND ${CMAKE_COMMAND} -E copy ARGS "$<SHELL_PATH:$<TARGET_FILE:${PROJECT_NAME}>>" "$<SHELL_PATH:${CMAKE_SOURCE_DIR}/>..\\BUSMASTER\\BIN\\$<CONFIG>\\"
)

################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
    BusmasterDBNetwork
)

