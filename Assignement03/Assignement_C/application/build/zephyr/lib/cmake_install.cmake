# Install script for directory: /home/pedro/zephyrproject/zephyr/lib

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

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/pedro/zephyrproject/zephyr/samples/basic/Assignement_C/application/build/zephyr/lib/crc/cmake_install.cmake")
  include("/home/pedro/zephyrproject/zephyr/samples/basic/Assignement_C/application/build/zephyr/lib/libc/cmake_install.cmake")
  include("/home/pedro/zephyrproject/zephyr/samples/basic/Assignement_C/application/build/zephyr/lib/posix/cmake_install.cmake")
  include("/home/pedro/zephyrproject/zephyr/samples/basic/Assignement_C/application/build/zephyr/lib/hash/cmake_install.cmake")
  include("/home/pedro/zephyrproject/zephyr/samples/basic/Assignement_C/application/build/zephyr/lib/heap/cmake_install.cmake")
  include("/home/pedro/zephyrproject/zephyr/samples/basic/Assignement_C/application/build/zephyr/lib/mem_blocks/cmake_install.cmake")
  include("/home/pedro/zephyrproject/zephyr/samples/basic/Assignement_C/application/build/zephyr/lib/os/cmake_install.cmake")
  include("/home/pedro/zephyrproject/zephyr/samples/basic/Assignement_C/application/build/zephyr/lib/utils/cmake_install.cmake")

endif()

