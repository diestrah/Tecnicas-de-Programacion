cmake_minimum_required(VERSION 4.0)
project(2025_1_Lab_09_CSV_Estructuras_Dinamicas)

set(CMAKE_CXX_STANDARD 20)

add_executable(2025_1_Lab_09_CSV_Estructuras_Dinamicas main.cpp
        Bibliotecas/FuncionesAuxiliares.cpp
        Bibliotecas/FuncionesAuxiliares.h
        Bibliotecas/Fecha.h
        Bibliotecas/TablaDeInfracciones.h
        Bibliotecas/InfraccionCometida.h
        Bibliotecas/EmpresasRegistradas.h
)
