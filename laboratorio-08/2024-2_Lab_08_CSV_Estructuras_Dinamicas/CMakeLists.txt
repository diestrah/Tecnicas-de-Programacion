cmake_minimum_required(VERSION 4.0)
project(2024_2_Lab_08_CSV_Estructuras_Dinamicas)

set(CMAKE_CXX_STANDARD 20)

add_executable(2024_2_Lab_08_CSV_Estructuras_Dinamicas main.cpp
        Bibliotecas/FuncionesAuxiliares.cpp
        Bibliotecas/FuncionesAuxiliares.h
        Bibliotecas/Distrito.h
        Bibliotecas/Plato.h
        Bibliotecas/PlatoPedido.h
        Bibliotecas/Cliente.h)
