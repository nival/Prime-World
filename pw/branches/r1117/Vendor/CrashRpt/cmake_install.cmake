# Install script for directory: D:/Work/pw/trunk/Vendor/CrashRpt

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/CrashRpt")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("D:/Work/pw/trunk/Vendor/CrashRpt/demos/ConsoleDemo/cmake_install.cmake")
  include("D:/Work/pw/trunk/Vendor/CrashRpt/demos/WTLDemo/cmake_install.cmake")
  include("D:/Work/pw/trunk/Vendor/CrashRpt/demos/MFCDemo/cmake_install.cmake")
  include("D:/Work/pw/trunk/Vendor/CrashRpt/reporting/crashrpt/cmake_install.cmake")
  include("D:/Work/pw/trunk/Vendor/CrashRpt/reporting/crashsender/cmake_install.cmake")
  include("D:/Work/pw/trunk/Vendor/CrashRpt/processing/crashrptprobe/cmake_install.cmake")
  include("D:/Work/pw/trunk/Vendor/CrashRpt/processing/crprober/cmake_install.cmake")
  include("D:/Work/pw/trunk/Vendor/CrashRpt/tests/cmake_install.cmake")
  include("D:/Work/pw/trunk/Vendor/CrashRpt/thirdparty/tinyxml/cmake_install.cmake")
  include("D:/Work/pw/trunk/Vendor/CrashRpt/thirdparty/jpeg/cmake_install.cmake")
  include("D:/Work/pw/trunk/Vendor/CrashRpt/thirdparty/libpng/cmake_install.cmake")
  include("D:/Work/pw/trunk/Vendor/CrashRpt/thirdparty/minizip/cmake_install.cmake")
  include("D:/Work/pw/trunk/Vendor/CrashRpt/thirdparty/zlib/cmake_install.cmake")
  include("D:/Work/pw/trunk/Vendor/CrashRpt/thirdparty/libogg/cmake_install.cmake")
  include("D:/Work/pw/trunk/Vendor/CrashRpt/thirdparty/libtheora/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

file(WRITE "D:/Work/pw/trunk/Vendor/CrashRpt/${CMAKE_INSTALL_MANIFEST}" "")
foreach(file ${CMAKE_INSTALL_MANIFEST_FILES})
  file(APPEND "D:/Work/pw/trunk/Vendor/CrashRpt/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
endforeach()
