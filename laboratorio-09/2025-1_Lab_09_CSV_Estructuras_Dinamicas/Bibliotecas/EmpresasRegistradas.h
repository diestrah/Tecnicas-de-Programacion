#ifndef INC_2025_1_LAB_09_CSV_ESTRUCTURAS_DINAMICAS_EMPRESASREGISTRADAS_H
#define INC_2025_1_LAB_09_CSV_ESTRUCTURAS_DINAMICAS_EMPRESASREGISTRADAS_H

#include "InfraccionCometida.h"

struct EmpresasRegistradas{
    int dni;
    char* nombre;
    char* distrito;
    char* placas[10];
    int numPlacas;
    struct InfraccionCometida* infraccion;
    int cantidadDeInfracciones;
    double totalPagado;
    double totalAdeudado;
};


#endif //INC_2025_1_LAB_09_CSV_ESTRUCTURAS_DINAMICAS_EMPRESASREGISTRADAS_H
