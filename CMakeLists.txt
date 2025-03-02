cmake_minimum_required(VERSION 3.13)

if (DEFINED ENV{PICO_SDK_PATH})
  include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
else()
  message(FATAL_ERROR "PICO_SDK_PATH environment variable not set")
endif()

project(airFreshener)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(
  airFreshener
  main.c
  MyTimer.c
)

pico_enable_stdio_usb(airFreshener 1)

pico_add_extra_outputs(airFreshener)

target_link_libraries(
  airFreshener
  pico_stdlib
  hardware_pwm
)
