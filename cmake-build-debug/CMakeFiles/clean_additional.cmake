# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\ai-qt-app_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ai-qt-app_autogen.dir\\ParseCache.txt"
  "ai-qt-app_autogen"
  )
endif()
