cmake_minimum_required(VERSION 4.0)
project(Lab8)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab8 main.cpp
        Bibliotecas/FuncionesAuxiliares.cpp
        Bibliotecas/FuncionesAuxiliares.h
        Bibliotecas/Reproduccion.h
        Bibliotecas/Categoria.h
        Bibliotecas/Utils.h)
