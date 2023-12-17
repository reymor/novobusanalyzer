set(PROJECT_NAME Include)

################################################################################
# Source groups
################################################################################
set(Header_Files
    "BaseDefs.h"
    "ModuleID.h"
    "Utils_macro.h"
    "XMLDefines.h"
)
source_group("Header Files" FILES ${Header_Files})

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/../../Kernel/BusmasterDriverInterface/Include/
)

set(ALL_FILES
    ${Header_Files}
)

add_custom_target(${PROJECT_NAME} SOURCES ${ALL_FILES})

