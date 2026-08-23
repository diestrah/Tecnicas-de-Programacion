#ifndef INC_2025_1_LAB_08_CSV_ESTRUCTURAS_EMPRESASREGISTRADAS_H
#define INC_2025_1_LAB_08_CSV_ESTRUCTURAS_EMPRESASREGISTRADAS_H

#include "Fecha.h"
struct EmpresasRegistradas{
    int dni;
    char* nombre;
    char *distrito;
    char** placas;
    int numPlacas;
    struct Fecha fechaDeInfraccion;
    struct Fecha fechaDePago;
    double totalDeMultas;
    double totalPagado;
    double totalAdeudado;
    int cantidadDeFaltas;
};

#endif //INC_2025_1_LAB_08_CSV_ESTRUCTURAS_EMPRESASREGISTRADAS_H