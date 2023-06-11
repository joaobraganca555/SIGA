cmake_minimum_required(VERSION 3.25)
project(SIGA_Mauricio)

set(CMAKE_CXX_STANDARD 14)

add_executable(SIGA_Mauricio
        main.c Lib.h ficheiros.h ficherios.c compraVenda.h compraVenda.c estatisticas.h estatisticas.c relatorios.h relatorios.c Lib.c)

target_include_directories(SIGA_Mauricio PRIVATE data)

