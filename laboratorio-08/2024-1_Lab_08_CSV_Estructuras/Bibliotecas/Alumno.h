#ifndef INC_2024_1_LAB_08_CSV_ESTRUCTURAS_ALUMNO_H
#define INC_2024_1_LAB_08_CSV_ESTRUCTURAS_ALUMNO_H

#include "Facultad.h"
#define TAM_NOM 40

struct Alumno{
    int codigo;
    char nombre[TAM_NOM];
    int numCursos;
    double sumaPonderada;
    double numCreditos;
    double promPonderado;
    struct Facultad facultad;
};

#endif //INC_2024_1_LAB_08_CSV_ESTRUCTURAS_ALUMNO_H