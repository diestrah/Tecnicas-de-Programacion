#ifndef INC_2025_1_LAB_10_LISTAS_LIGADAS_NODO_H
#define INC_2025_1_LAB_10_LISTAS_LIGADAS_NODO_H

#include "Cuenta.h"

struct Nodo{
    struct Cuenta cuenta;
    struct Nodo* siguiente;
};

#endif //INC_2025_1_LAB_10_LISTAS_LIGADAS_NODO_H