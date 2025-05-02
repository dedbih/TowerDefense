# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\appTorreDefensaJuego_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\appTorreDefensaJuego_autogen.dir\\ParseCache.txt"
  "appTorreDefensaJuego_autogen"
  )
endif()
