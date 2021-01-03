#
# Copyright 2021 Staysail Systems, Inc. <info@staysail.tech>
#
# This software is supplied under the terms of the MIT License, a
# copy of which should be located in the distribution where this
# file was obtained (LICENSE.txt).  A copy of the license may also be
# found online at https://opensource.org/licenses/MIT.

cmake_minimum_required (VERSION 3.13)

project(nng-freertos)

find_package(nng CONFIG REQUIRED)

set(FREERTOS_ROOT build/kernel)
set(FREERTOS_PORT ${FREERTOS_ROOT}/portable/ThirdParty/GCC/Posix)
set(FREERTOS_MMGR heap_3)

file(GLOB FREERTOS_SRCS ${FREERTOS_ROOT}/*.c
  ${FREERTOS_ROOT}/portable/MemMang/${FREERTOS_MMGR}.c)

file(GLOB_RECURSE FREERTOS_PORT_SRCS ${FREERTOS_PORT}/*.c)

add_executable(demo)

target_include_directories(demo PRIVATE .)
target_include_directories(demo PRIVATE ${FREERTOS_ROOT}/include)
target_include_directories(demo PRIVATE ${FREERTOS_PORT})
target_include_directories(demo PRIVATE ../../../)
target_include_directories(demo PRIVATE ../../src)

target_sources(demo PRIVATE main.c)
target_sources(demo PRIVATE ${FREERTOS_SRCS} ${FREERTOS_PORT_SRCS})

target_link_libraries(demo nng::nng)
