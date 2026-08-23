#ifndef INC_2025_2_LAB_09_LISTAS_LIGADAS_CATEGORIA_H
#define INC_2025_2_LAB_09_LISTAS_LIGADAS_CATEGORIA_H

struct Categoria{
    char* codigo;
    char* nombre;
    char* descripcion;
    char* canalConDuracionMaxima;
    int duracionMaxima;
    int duracionTotal;
    double arrDropOff[20];
    int cantidadDeReproducciones;
    double promedioDropOff;
};

#endif //INC_2025_2_LAB_09_LISTAS_LIGADAS_CATEGORIA_H