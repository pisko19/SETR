# Definição da versão mínima do CMake
cmake_minimum_required(VERSION 3.10)

# Nome do projeto
project(ass02)

# Definição dos arquivos de código-fonte
set(SOURCES src/main.c src/Uart.c)

# Definição dos arquivos de cabeçalho
include_directories(header)

# Adiciona o executável, ligando os arquivos de código-fonte
add_executable(ass02 ${SOURCES})

