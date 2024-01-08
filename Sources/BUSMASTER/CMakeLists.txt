################################################################################
# required tools
################################################################################
include(FindPackageHandleStandardArgs)

# bison
find_path(BISON_PATH
  bison.exe
  PATHS ../../Tools/bison)
find_program(BISON_EXECUTABLE
  NAMES bison.exe
  PATHS ${BISON_PATH})
find_package_handle_standard_args(BISON
  REQUIRED_VARS BISON_EXECUTABLE)

# flex
find_path(FLEX_PATH
  flex.exe
  PATHS ../../Tools/flex)
find_program(FLEX_EXECUTABLE
  NAMES flex.exe
  PATHS ${FLEX_PATH})
find_package_handle_standard_args(FLEX
  REQUIRED_VARS FLEX_EXECUTABLE)

# gettext
find_path(GETTEXT_PATH
  lib/intl.lib
  PATHS EXTERNAL/GetText)
find_library(GETTEXT_LIBRARY
  NAMES intl
  PATHS ${GETTEXT_PATH}/lib)
find_path(GETTEXT_INCLUDE_DIR
  NAMES libintl.h
  PATHS ${GETTEXT_PATH}/include)
find_package_handle_standard_args(GETTEXT
  REQUIRED_VARS GETTEXT_LIBRARY GETTEXT_INCLUDE_DIR)

# libxml2
find_path(LIBXML2_PATH
  lib/libxml2.lib
  PATHS EXTERNAL/libxml2)
find_library(LIBXML2_LIBRARY
  NAMES libxml2
  PATHS ${LIBXML2_PATH}/lib)
find_path(LIBXML2_INCLUDE_DIR
  NAMES libxml/xmlversion.h
  PATHS ${LIBXML2_PATH}/include)
find_package_handle_standard_args(LIBXML2
  REQUIRED_VARS LIBXML2_LIBRARY LIBXML2_INCLUDE_DIR)

# zlib
find_path(ZLIB_PATH
  lib/zlib.lib
  PATHS EXTERNAL/zlib)
find_library(ZLIB_LIBRARY
  NAMES zlib
  PATHS ${ZLIB_PATH}/lib)
find_path(ZLIB_INCLUDE_DIR
  NAMES zlib.h
  PATHS ${ZLIB_PATH}/include)
find_package_handle_standard_args(ZLIB
  REQUIRED_VARS ZLIB_LIBRARY ZLIB_INCLUDE_DIR)

################################################################################
# common compiler/linker settings
################################################################################
# add_definitions(-DWINVER=0x0500) # Windows 2000
#add_definitions(-DWINVER=0x0501) # Windows XP
#add_definitions(-DWINVER=0x0502) # Windows Server 2003
#add_definitions(-DWINVER=0x0600) # Windows Vista
# add_definitions(-DWINVER=0x0601) # Windows 7
# add_definitions(-DWINVER=0x19044) # Windows 10, Version 21H2
#add_definitions(-D_VC80_UPGRADE=0x0710)
link_directories(
  ${ATL_PATH}/lib/ATL/i386
  ${MFC_PATH}/lib/Mfc/i386)
set(CMAKE_MFC_FLAG 2) # shared MFC library
add_definitions(-D_CRT_SECURE_NO_WARNINGS -wd4996) # warning C4996: '...': This function or variable may be unsafe. Consider using ... instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.

cmake_policy(SET CMP0020 NEW)
################################################################################
# Global include directories
################################################################################
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/../Kernel/BusmasterDriverInterface/Include/
  ${CMAKE_CURRENT_SOURCE_DIR}/../Kernel/BusmasterDBNetwork/Include/
  ${CMAKE_CURRENT_SOURCE_DIR}/../Kernel/Utilities/
  ${CMAKE_CURRENT_SOURCE_DIR}/../Kernel/BusmasterKernel/
  ${CMAKE_CURRENT_SOURCE_DIR}/../Kernel/BusmasterDBNetwork/
)

################################################################################
# Sub-projects
################################################################################
add_subdirectory(Application)
add_subdirectory(BusEmulation)
add_subdirectory(CAN_ETAS_BOA)
add_subdirectory(CAN_ICS_neoVI)
add_subdirectory(CAN_ISOLAR_EVE_VCAN)
add_subdirectory(CAN_iView)
add_subdirectory(CAN_IXXAT_VCI)
add_subdirectory(CAN_Kvaser_CAN)
add_subdirectory(CAN_MHS)
add_subdirectory(CAN_NSI)
# add_subdirectory(CAN_PEAK_USB)
add_subdirectory(CAN_STUB)
add_subdirectory(CAN_Vector_XL)
add_subdirectory(CAN_VSCOM)
add_subdirectory(CAN_RUSOKU)
add_subdirectory(CommonClass)
add_subdirectory(DataTypes)
# add_subdirectory(DIL_Interface)
# add_subdirectory(DIL_J1939)
add_subdirectory(EXTERNAL/DmGraph)
add_subdirectory(EXTERNAL/AdvancedUIPlugin)
add_subdirectory(Filter)
# add_subdirectory(FLEXRAY_ETAS_BOA)
add_subdirectory(FormatConverter)
add_subdirectory(FrameProcessor)
add_subdirectory(LIN_ETAS_BOA)
add_subdirectory(LIN_ISOLAR_EVE_VLIN)
add_subdirectory(LIN_PEAK_USB)
add_subdirectory(LIN_Vector_XL)
# add_subdirectory(Localization)
add_subdirectory(MHS_CNFG)
add_subdirectory(NodeSimEx)
add_subdirectory(ProjectConfiguration)
add_subdirectory(PSDI_CAN)
add_subdirectory(Replay)
add_subdirectory(SigGrphWnd)
add_subdirectory(SignalDefiner)
add_subdirectory(SignalWatch)
add_subdirectory(TestSetupEditorGUI)
add_subdirectory(TestSetupEditorLib)
add_subdirectory(TestSuiteExecutorGUI)
add_subdirectory(TXWindow)
# add_subdirectory(TXWindowFlexRay)
add_subdirectory(UDS_Protocol)
add_subdirectory(Utility)
# add_subdirectory(Include)
add_subdirectory(LIN_Kvaser)
add_subdirectory(LDFEditor)
add_subdirectory(LDFViewer)
