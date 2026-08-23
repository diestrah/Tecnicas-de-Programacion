#ifndef LAB7_CATEGORIA_H
#define LAB7_CATEGORIA_H

#define TAM_COD 10
#define TAM_NOM_CAT 40
#define MAX_REPROD 15

#include "Reproduccion.h"
struct Categoria{
    char codigo[TAM_COD];
    char nombre[TAM_NOM_CAT];
    struct Reproduccion reproducciones[MAX_REPROD];
    int numReproducciones;
    double promedioRating;
    int duracionTotal;
};
#endif //LAB7_CATEGORIA_H