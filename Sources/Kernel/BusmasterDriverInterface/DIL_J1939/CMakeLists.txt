# set(sources
#   ConnectionDet.cpp
#   DIL_J1939.cpp
#   DIL_J1939_stdafx.cpp
#   MonitorNode.cpp
#   NetworkMgmt.cpp
#   NodeConManager.cpp
#   ReadCanMsg.cpp
#   TransferLayer.cpp)

# set(headers
#   ConnectionDet.h
#   DIL_J1939.h
#   DIL_J1939_Extern.h
#   DIL_J1939_stdafx.h
#   J1939_UtilityFuncs.h
#   Macros.h
#   MonitorNode.h
#   NetworkMgmt.h
#   NodeConManager.h
#   ReadCanMsg.h
#   TransferLayer.h)

# add_library(DIL_J1939 SHARED ${sources} ${headers})

# include_directories(
#   ..
#   ${ICONV_INCLUDE_DIR}
#   ${LIBXML2_INCLUDE_DIR}
#   ${MFC_INCLUDE_DIRS})

# # compiler options
# add_definitions(-D_USRDLL)

# # linker options
# set_target_properties(DIL_J1939 PROPERTIES LINK_FLAGS "/NODEFAULTLIB:daouuid")
# target_link_libraries(DIL_J1939
#   Utils
#   DataTypes)

# # installer options
# add_custom_command(
#   TARGET DIL_J1939
#   POST_BUILD
#   COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${PROJECT_SOURCE_DIR}/BIN/${CMAKE_BUILD_TYPE}/
#   COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:DIL_J1939> ${PROJECT_SOURCE_DIR}/BIN/${CMAKE_BUILD_TYPE}/)


























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

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE DIL_J1939)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "MFCDLLProj"
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
    OUTPUT_DIRECTORY_DEBUG           "$<CONFIG>"
    OUTPUT_DIRECTORY_RELEASE         "$<CONFIG>"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_BUSMASTER_DEBUG "${CMAKE_SOURCE_DIR}//BIN/Libs"
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG           "${CMAKE_SOURCE_DIR}//BIN/Libs"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE         "${CMAKE_SOURCE_DIR}//BIN/Libs"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_NAME_BUSMASTER_DEBUG "${OUTPUT_DIRECTORY}DIL_J1939"
    ARCHIVE_OUTPUT_NAME_DEBUG           "${OUTPUT_DIRECTORY}DIL_J1939"
    ARCHIVE_OUTPUT_NAME_RELEASE         "${OUTPUT_DIRECTORY}DIL_J1939"
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    PDB_OUTPUT_DIRECTORY                 "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}s/PDB"
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
target_include_directories(${PROJECT_NAME} PUBLIC
    "$<$<CONFIG:Debug>:"
        "${CMAKE_CURRENT_SOURCE_DIR}/../EXTERNAL/libxml2/include"
    ">"
    "$<$<CONFIG:Release>:"
        "${CMAKE_CURRENT_SOURCE_DIR}/../BUSMASTER/EXTERNAL/libxml2/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../BUSMASTER/Include"
    ">"
    "${CMAKE_CURRENT_SOURCE_DIR}/../..;"
    "$ENV{VC_IncludePath};"
    "$ENV{WindowsSDK_IncludePath}"
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
            "$(SolutionDir)BIN/$(OutDir)Utilities.lib"
        >
        $<$<CONFIG:Debug>:
            /INCREMENTAL;
            "../../bin/Debug/Utilities.lib"
        >
        $<$<CONFIG:Release>:
            /NODEFAULTLIB:daouuid.lib;
            /STACK:8000000;
            "../../bin/Release/Utilities.lib"
        >
        /DEBUG;
        /MACHINE:X86;
        /SUBSYSTEM:WINDOWS;
        /OPT:REF;
        /OPT:ICF;
        /DYNAMICBASE:NO
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
    Utilities
)

target_link_directories(${PROJECT_NAME} PUBLIC
    "$ENV{VC_LibraryPath_x86};"
    "$ENV{WindowsSDK_LibraryPath_x86}"
)

