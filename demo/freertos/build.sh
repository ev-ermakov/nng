#!/bin/bash -e

# Copyright 2021 Staysail Systems, Inc. <info@staysail.tech>
#
# This software is supplied under the terms of the MIT License, a
# copy of which should be located in the distribution where this
# file was obtained (LICENSE.txt).  A copy of the license may also be
# found online at https://opensource.org/licenses/MIT.

B=build

freertos_inc="$(pwd)
$(pwd)/$B/kernel/include
$(pwd)/$B/kernel/portable/ThirdParty/GCC/Posix"

if [ ! -d $B ]; then
	mkdir $B
fi

if [ ! -d $B/kernel ]; then
	git clone --depth=1 https://github.com/FreeRTOS/FreeRTOS-Kernel $B/kernel
	git -C $B/kernel checkout 18d4ba9c07
fi

if [ ! -d $B/nng ]; then
	mkdir -p $B/nng
	cmake -DCMAKE_INSTALL_PREFIX=$(pwd)/build \
	      -DCMAKE_SYSTEM_NAME=Generic \
	      -DCMAKE_BUILD_TYPE=Debug \
	      -DNNG_PLATFORM=FreeRTOS \
	      -DNNG_FREERTOS_INCDIRS="${freertos_inc//$'\n'/\;}" \
	      -S ../.. -B $B/nng
fi
( cd $B/nng && make -j$(nproc) && make install )

if [ ! -d $B/demo ]; then
	mkdir -p $B/demo
	cmake -DCMAKE_PREFIX_PATH=$(pwd)/$B/lib/cmake \
	      -DCMAKE_EXPORT_COMPILE_COMMANDS=YES \
	      -S . -B $B/demo
	ln -sfr $B/demo/compile_commands.json .
fi
( cd $B/demo && make && cp demo ../.. )
