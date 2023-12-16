set(PROJECT_NAME BusmasterDriverInterface)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "ReadMe.txt"
)
source_group("" FILES ${no_group_source_files})

set(Header_Files
    "DIL_CAN.h"
    "Include/BusmasterDriverInterface.h"
    "stdafx.h"
    "targetver.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Include
    "Include/BaseDIL_CAN.h"
    "Include/BaseDIL_CAN_Controller.h"
    "Include/BaseDIL_FLEXRAY.h"
    "Include/BaseDIL_FLEXRAY_Controller.h"
    "Include/BaseDIL_J1939.h"
    "Include/BaseDIL_LIN.h"
    "Include/BaseDIL_LIN_Controller.h"
    "Include/CANDriverDefines.h"
    "Include/DeviceListInfo.h"
    "Include/Error.h"
    "Include/FlexRayDriverDefines.h"
    "Include/IBusService.h"
    "Include/J1939DriverDefines.h"
    "Include/LINDriverDefines.h"
)
source_group("Include" FILES ${Include})

set(Source_Files
    "BusmasterDriverInterface.cpp"
    "DIL_CAN.cpp"
    "DIL_LIN.cpp"
    "DILC_Dummy.cpp"
    "DILI_J1939.cpp"
    "DILL_Dummy.cpp"
    "dllmain.cpp"
    "stdafx.cpp"
)
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
    ${no_group_source_files}
    ${Header_Files}
    ${Include}
    ${Source_Files}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} SHARED ${ALL_FILES})

target_precompile_headers(${PROJECT_NAME} PRIVATE
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/stdafx.h>"
)

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE BusmasterDriverInterface)

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
# MSVC runtime library
################################################################################
get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)
string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
    $<$<CONFIG:Debug>:
        MultiThreadedDebugDLL
    >
    $<$<NOT:$<OR:$<CONFIG:Debug>>>:${MSVC_RUNTIME_LIBRARY_DEFAULT}>
)
set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

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
    "BUSMASTERDRIVERINTERFACE_EXPORTS;"
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
            /Od;
            /Y-
        >
        $<$<CONFIG:Release>:
            /O2;
            /Oi;
            /Gy
        >
        /W3;
        ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
        ${DEFAULT_CXX_EXCEPTION_HANDLING}
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
        /SUBSYSTEM:WINDOWS
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
# Link with other targets.
target_link_libraries(${PROJECT_NAME} PUBLIC
    DIL_J1939
)

