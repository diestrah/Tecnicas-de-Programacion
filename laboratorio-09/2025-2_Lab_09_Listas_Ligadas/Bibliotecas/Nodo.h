#ifndef INC_2025_2_LAB_09_LISTAS_LIGADAS_NODO_H
#define INC_2025_2_LAB_09_LISTAS_LIGADAS_NODO_H

#include "Categoria.h"
struct Nodo{
    struct Categoria categoria;
    struct Nodo* siguiente;
};

#endif //INC_2025_2_LAB_09_LISTAS_LIGADAS_NODO_H