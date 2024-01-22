set(PROJECT_NAME LDFViewer)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Widgets Gui Core REQUIRED)

################################################################################
# Source groups
################################################################################
set(FORM_LIST
    "ldfviewer.ui"
)
source_group("Form Files" FILES ${FORM_LIST})

set(HEADER_LIST
    "LDFHighlighter.h"
    "ldfviewer.h"
)
source_group("Header Files" FILES ${HEADER_LIST})

set(RESOURCE_LIST
    "ldfviewer.qrc"
)
source_group("Resource Files" FILES ${RESOURCE_LIST})

set(SOURCE_LIST
    "LDFHighlighter.cpp"
    "ldfviewer.cpp"
    "main.cpp"
)
source_group("Source Files" FILES ${SOURCE_LIST})

set(ALL_FILES
    ${FORM_LIST}
    ${HEADER_LIST}
    ${RESOURCE_LIST}
    ${SOURCE_LIST}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

################################################################################
# Includes for CMake from *.props
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Qt4VSv1.0"
)
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_DEBUG   "${PROJECT_NAME}"
    TARGET_NAME_RELEASE "${PROJECT_NAME}"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
    OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>"
)
################################################################################
# MSVC runtime library
################################################################################
get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)
string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
    $<$<CONFIG:Debug>:
        MultiThreadedDebugDLL
    >
    $<$<CONFIG:Release>:
        MultiThreadedDLL
    >
    $<$<NOT:$<OR:$<CONFIG:Debug>,$<CONFIG:Release>>>:${MSVC_RUNTIME_LIBRARY_DEFAULT}>
)
set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/GeneratedFiles;"
    "${CMAKE_CURRENT_SOURCE_DIR}/.;"
    "$ENV{QTDIR}/include;"
    "${CMAKE_CURRENT_SOURCE_DIR}/GeneratedFiles/$<CONFIG>;"
    ${QtCore_INCLUDE_DIRS}
    ${QtGui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:Release>:"
        "QT_NO_DEBUG;"
        "NDEBUG"
    ">"
    "UNICODE;"
    "WIN32;"
    "WIN64;"
    "QT_DLL;"
    "QT_CORE_LIB;"
    "QT_GUI_LIB;"
    "QT_WIDGETS_LIB"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /Od;
            /Zi
        >
        $<$<CONFIG:Release>:
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
        >
        ${DEFAULT_CXX_EXCEPTION_HANDLING};
        /Zc:wchar_t
    )
    string(CONCAT FILE_CL_OPTIONS
        "/Y-"
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /DEBUG
        >
        /SUBSYSTEM:WINDOWS
    )
endif()

################################################################################
# Dependencies
################################################################################
target_link_directories(${PROJECT_NAME} PRIVATE
    "${Qt5_DIR}/../../"
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${Qt5Widgets_LIBRARIES} ${QtGui_LIBRARIES} ${QtCore_LIBRARIES} qtmain)

################################################################################
# Post build events
################################################################################
add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
  COMMAND ${CMAKE_COMMAND} ARGS -E copy $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/
)
