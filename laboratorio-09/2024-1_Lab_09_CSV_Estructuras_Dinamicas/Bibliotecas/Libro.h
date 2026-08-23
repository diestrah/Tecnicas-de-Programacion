#ifndef INC_2024_1_LAB_09_CSV_ESTRUCTURAS_DINAMICAS_LIBRO_H
#define INC_2024_1_LAB_09_CSV_ESTRUCTURAS_DINAMICAS_LIBRO_H

#include "Venta.h"

struct Libro{
    char* codigo;
    char* titulo;
    char* autor;
    double precio;
    struct Venta* ventas;
    int librosVendidos;
    int sumaDeCalificaciones;
    int ranking;
};

#endif //INC_2024_1_LAB_09_CSV_ESTRUCTURAS_DINAMICAS_LIBRO_H
