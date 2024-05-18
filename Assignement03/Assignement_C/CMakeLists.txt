# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(Assignement03)

# Adicione os arquivos fonte
target_sources(app PRIVATE main.c src-gen/Statechart.c)

# Inclua o diretório src e src-gen no caminho de busca
target_include_directories(app PRIVATE src src-gen)

