# Install script for directory: /home/yoshi/gr-ownHeader/include/ownHeader

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ownHeader" TYPE FILE FILES
    "/home/yoshi/gr-ownHeader/include/ownHeader/api.h"
    "/home/yoshi/gr-ownHeader/include/ownHeader/append_header_bb.h"
    "/home/yoshi/gr-ownHeader/include/ownHeader/generate_header_bb.h"
    "/home/yoshi/gr-ownHeader/include/ownHeader/parse_header_bb.h"
    "/home/yoshi/gr-ownHeader/include/ownHeader/send_to_multiplexer_b.h"
    "/home/yoshi/gr-ownHeader/include/ownHeader/generate_short_bb.h"
    "/home/yoshi/gr-ownHeader/include/ownHeader/parse_short_bb.h"
    )
endif()

