# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/Hoang/esp/esp-idf/components/bootloader/subproject"
  "D:/VIDEOS/code_device/HSmartHome/Gateway/doc/ESP32/sample_project/build/bootloader"
  "D:/VIDEOS/code_device/HSmartHome/Gateway/doc/ESP32/sample_project/build/bootloader-prefix"
  "D:/VIDEOS/code_device/HSmartHome/Gateway/doc/ESP32/sample_project/build/bootloader-prefix/tmp"
  "D:/VIDEOS/code_device/HSmartHome/Gateway/doc/ESP32/sample_project/build/bootloader-prefix/src/bootloader-stamp"
  "D:/VIDEOS/code_device/HSmartHome/Gateway/doc/ESP32/sample_project/build/bootloader-prefix/src"
  "D:/VIDEOS/code_device/HSmartHome/Gateway/doc/ESP32/sample_project/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/VIDEOS/code_device/HSmartHome/Gateway/doc/ESP32/sample_project/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/VIDEOS/code_device/HSmartHome/Gateway/doc/ESP32/sample_project/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
