#ifndef INC_2025_1_LAB_09_CSV_ESTRUCTURAS_DINAMICAS_INFRACCIONCOMETIDA_H
#define INC_2025_1_LAB_09_CSV_ESTRUCTURAS_DINAMICAS_INFRACCIONCOMETIDA_H

#include "Fecha.h"

struct InfraccionCometida{
    struct Fecha fechaDeInfraccion;
    char* placa;
    char* codigoDeLaInfraccion;
    double multa;
    char* descripcion;
    bool multaPagada;
    struct Fecha fechaDePago;
};

#endif //INC_2025_1_LAB_09_CSV_ESTRUCTURAS_DINAMICAS_INFRACCIONCOMETIDA_H