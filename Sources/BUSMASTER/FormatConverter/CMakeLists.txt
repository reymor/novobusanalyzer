# mfc
set(CMAKE_MFC_FLAG 2) # shared MFC library
add_definitions(-D_AFXDLL)

#
# sub projects
#
add_subdirectory(AscLogConverter)
add_subdirectory(BlfLibrary)
add_subdirectory(BlfLogConverter)
add_subdirectory(CAPL2CConverter)
add_subdirectory(DBC2DBFConverter)
add_subdirectory(DBC2DBFConverterLibrary)
add_subdirectory(DBF2DBCConverter)
add_subdirectory(FormatConverterApp)
add_subdirectory(J1939DBC2DBFConverter)
add_subdirectory(LogAscConverter)
add_subdirectory(LogToExcelConverter)
