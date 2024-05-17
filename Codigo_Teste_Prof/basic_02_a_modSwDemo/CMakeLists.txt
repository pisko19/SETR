# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(ModularSWDemo)

target_sources(app PRIVATE src/main.c) 

target_include_directories(app PRIVATE src/MyMath) #Add this line
target_sources(app PRIVATE src/MyMath/MyMath.c) # Add module c source



