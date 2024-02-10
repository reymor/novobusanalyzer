set(PROJECT_NAME Utils)

set(sources
  AlphaChar.cpp
  AlphanumiricEdit.cpp
  ButtonItem.cpp
  ColorSelector.cpp
  ColumnTreeCtrl.cpp
  ColumnTreeWnd.cpp
  ComboItem.cpp
  DirectoryWatcher.cpp
  EditItem.cpp
  FFListCtrl.cpp
  FlexListCtrl.cpp
  FlickerFreeListCtrl.cpp
  FlickerFreeTree.cpp
  KeyNumEdit.cpp
  MsgInterpretation.cpp
  MultiLanguageSupport.cpp
  NumEdit.cpp
  NumSpinCtrl.cpp
  OffScreenDC.cpp
  RadixEdit.cpp
  SignalMatrix.cpp
  SignalDetailsDlg.cpp
  UtilFunctions.cpp
  Utility.cpp
  Utility_Structs.cpp
  Utility_Thread.cpp
  TimeManager.cpp
  WaitIndicator.cpp)

set(headers
  AlphaChar.h
  AlphanumiricEdit.h
  ButtonItem.h
  ColorSelector.h
  ColumnTreeCtrl.h
  ColumnTreeWnd.h
  ComboItem.h
  EditItem.h
  FFListCtrl.h
  FlexListCtrl.h
  FlickerFreeListCtrl.h
  FlickerFreeTree.h
  KeyNumEdit.h
  MsgInterpretation.h
  MultiLanguageSupport.h
  NumEdit.h
  NumSpinCtrl.h
  OffScreenDC.h
  RadixEdit.h
  SignalMatrix.h
  UtilFunctions.h
  Utility.h
  Utility_Structs.h
  Utility_Thread.h
  Utils_stdafx.h
  WaitIndicator.h
  XMLUtils.h
)

add_library(${PROJECT_NAME} STATIC ${sources} ${headers})

include_directories(
  ..
  ${ICONV_INCLUDE_DIR}
  ${LIBXML2_INCLUDE_DIR}
  ${ATL_INCLUDE_DIRS}
  ${MFC_INCLUDE_DIRS})

# compiler options
add_definitions(-D_LIB)

# linker options
target_link_libraries(${PROJECT_NAME}
  PUBLIC ${LIBXML2_LIBRARY} ${GETTEXT_LIBRARY} ProtocolDefinitions
)

if(MSVC)
  target_link_options(${PROJECT_NAME} PRIVATE /DEBUG)
  target_compile_options(${PROJECT_NAME} PRIVATE /Zi)
endif()