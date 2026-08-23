cmake_minimum_required(VERSION 4.0)
project(Lab7)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab7 main.cpp
        Bibliotecas/FuncionesAuxiliares.cpp
        Bibliotecas/FuncionesAuxiliares.h
        Bibliotecas/Reproduccion.h
        Bibliotecas/Categoria.h
        Bibliotecas/Utils.h
)
