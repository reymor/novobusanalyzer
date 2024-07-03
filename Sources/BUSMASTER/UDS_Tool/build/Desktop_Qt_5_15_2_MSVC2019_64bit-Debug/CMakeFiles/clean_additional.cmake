# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\UDS_Tool_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\UDS_Tool_autogen.dir\\ParseCache.txt"
  "UDS_Tool_autogen"
  )
endif()
