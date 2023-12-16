set(PROJECT_NAME BusmasterDBNetwork)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "ReadMe.txt"
)
source_group("" FILES ${no_group_source_files})

set(Header_Files
    "AccessDBManager.h"
    "BusMasterNetWork.h"
    "Include/IBMNetWorkGetService.h"
    "Include/IBMNetWorkService.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "AccessDBManager.cpp"
    "BusMasterNetWork.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
    ${no_group_source_files}
    ${Header_Files}
    ${Source_Files}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE BusmasterDBNetwork)

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
    OUTPUT_DIRECTORY_BUSMASTER_DEBUG "${CMAKE_SOURCE_DIR}/Bin/$<CONFIG>"
    OUTPUT_DIRECTORY_DEBUG           "${CMAKE_SOURCE_DIR}/Bin/$<CONFIG>"
    OUTPUT_DIRECTORY_RELEASE         "${CMAKE_SOURCE_DIR}/Bin/$<CONFIG>"
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
    "_LIB;"
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
        /W3;
        ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
        ${DEFAULT_CXX_EXCEPTION_HANDLING};
        /Y-
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:busmaster_debug>:
            /OPT:REF;
            /OPT:ICF
        >
        $<$<CONFIG:Release>:
            /OPT:REF;
            /OPT:ICF
        >
        /SUBSYSTEM:WINDOWS
    )
endif()

