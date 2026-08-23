#ifndef INC_2024_2_LAB_08_CSV_ESTRUCTURAS_DINAMICAS_CLIENTE_H
#define INC_2024_2_LAB_08_CSV_ESTRUCTURAS_DINAMICAS_CLIENTE_H

#include "Distrito.h"
#include "PlatoPedido.h"

struct Cliente{
    int dni;
    char* nombre;
    struct Distrito distrito;
    struct PlatoPedido pedidos[30];
    int cantidadDePedidos;
    double montoTotal;
};

#endif //INC_2024_2_LAB_08_CSV_ESTRUCTURAS_DINAMICAS_CLIENTE_H
