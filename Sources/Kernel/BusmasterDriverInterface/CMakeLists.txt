set(PROJECT_NAME BusmasterDriverInterface)

################################################################################
# Source groups
################################################################################
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
    ${Header_Files}
    ${Include}
    ${Source_Files}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} SHARED ${ALL_FILES})

set(ROOT_NAMESPACE BusmasterDriverInterface)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
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
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME}
    PRIVATE Include ${CMAKE_CURRENT_SOURCE_DIR}/../BusmasterDBNetwork/Include
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
    target_compile_options(${PROJECT_NAME} PRIVATE /Zi)
endif()

target_link_libraries(${PROJECT_NAME} 
    PUBLIC DIL_J1939
)

################################################################################
# Post build events
################################################################################
add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ARGS ${CMAKE_SOURCE_DIR}/Sources/BUSMASTER/BIN/${CMAKE_BUILD_TYPE}/
    COMMAND ${CMAKE_COMMAND} -E copy ARGS $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_SOURCE_DIR}/Sources/BUSMASTER/BIN/${CMAKE_BUILD_TYPE}/
)
