cmake_minimum_required(VERSION 4.0)
project(2025_1_Lab_08_CSV_Estructuras)

set(CMAKE_CXX_STANDARD 20)

add_executable(2025_1_Lab_08_CSV_Estructuras main.cpp
        Bibliotecas/FuncionesAuxiliares.cpp
        Bibliotecas/FuncionesAuxiliares.h
        Bibliotecas/TablaDeInfracciones.h
        Bibliotecas/Fecha.h
        Bibliotecas/EmpresasRegistradas.h
        Bibliotecas/Utils.h
)
