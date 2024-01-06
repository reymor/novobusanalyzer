set(PROJECT_NAME DIL_J1939)

################################################################################
# Source groups
################################################################################
set(Header_Files
    "ConnectionDet.h"
    "DIL_J1939.h"
    "DIL_J1939_Extern.h"
    "DIL_J1939_stdafx.h"
    "J1939_UtilityFuncs.h"
    "Macros.h"
    "MonitorNode.h"
    "NetworkMgmt.h"
    "NodeConManager.h"
    "ReadCanMsg.h"
    "TransferLayer.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "ConnectionDet.cpp"
    "DIL_J1939.cpp"
    "DIL_J1939_stdafx.cpp"
    "MonitorNode.cpp"
    "NetworkMgmt.cpp"
    "NodeConManager.cpp"
    "ReadCanMsg.cpp"
    "TransferLayer.cpp"
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

set(ROOT_NAMESPACE DIL_J1939)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "MFCDLLProj"
)

################################################################################
# MSVC runtime library
################################################################################
get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)
string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
    $<$<CONFIG:busmaster_debug>:
        MultiThreadedDLL
    >
    $<$<CONFIG:Debug>:
        MultiThreadedDebugDLL
    >
    $<$<CONFIG:Release>:
        MultiThreadedDLL
    >
    $<$<NOT:$<OR:$<CONFIG:busmaster_debug>,$<CONFIG:Debug>,$<CONFIG:Release>>>:${MSVC_RUNTIME_LIBRARY_DEFAULT}>
)
set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../Include
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
    "WINVER=0x0502;"
    "_MBCS"
    "_AFXDLL"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:busmaster_debug>:
            /Od;
            /Zi
        >
        $<$<CONFIG:Debug>:
            /Gm;
            /Od;
            /Zi
        >
        $<$<CONFIG:Release>:
            /O2;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
        >
        /W3;
        /I;
        "$(SolutionDir)/Localization/include";
        ${DEFAULT_CXX_EXCEPTION_HANDLING};
        /Zc:wchar_t;
        /Y-
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:busmaster_debug>:
            /STACK:8000000;
            /INCREMENTAL:NO;
        >
        $<$<CONFIG:Debug>:
            /INCREMENTAL;
        >
        $<$<CONFIG:Release>:
            /NODEFAULTLIB:daouuid.lib;
            /STACK:8000000;
        >
        /DEBUG;
        /MACHINE:X86;
        /SUBSYSTEM:WINDOWS;
        /OPT:REF;
        /OPT:ICF;
        /DYNAMICBASE:NO
    )
endif()

target_link_libraries(${PROJECT_NAME} 
    PUBLIC Utilities ProtocolDefinitions
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
