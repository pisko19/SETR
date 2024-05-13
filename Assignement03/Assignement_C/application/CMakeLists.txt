# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)
set(BOARD "nrf52840dk/nrf52840")

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

# Adicione os arquivos fonte
target_sources(app PRIVATE
    main.c
    ../src-gen/Statechart.c
    ../src-gen/Statechart.h
    debug/debugprint.h
    timers/timers.c
    ../src/sc_types.h
)

# Inclua o diretório src e src-gen no caminho de busca
target_include_directories(app PRIVATE src src-gen)
