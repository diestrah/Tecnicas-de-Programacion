#ifndef LAB8_CATEGORIA_H
#define LAB8_CATEGORIA_H
#include "Reproduccion.h"
struct Categoria{
    char *codigo;
    char *nombre;
    char *descripcion;
    struct Reproduccion *reproducciones;
    int numReproducciones;
    double promedioRating;
    int duracionTotal;
};
#endif //LAB8_CATEGORIA_H