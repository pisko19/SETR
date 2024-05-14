# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)
project(Assignement03)
set(BOARD "nrf52840dk/nrf52840")

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

# Adicione os arquivos fonte
target_sources(app PRIVATE
    application/main.c
    application/timers/timers.c
    src-gen/Statechart.c
    
)

# Inclua o diretório src e src-gen no caminho de busca
target_include_directories(app PRIVATE src src-gen build application/debug aplication/timers)

add_executable(ass03)
