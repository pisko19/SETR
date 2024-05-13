# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)
set(BOARD "nrf52840dk/nrf52840")

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

target_sources(app PRIVATE
    src/main.c
    ../src-gen/Statechart_required.h
    ../src-gen/Statechart.h
)

