#ifndef LAB7_FUNCIONESAUXILIARES_H
#define LAB7_FUNCIONESAUXILIARES_H
#include "Utils.h"

// FUNCIONES SECUNDARIAS:
// Apertura de archivos
ifstream abrirInput(const char* nombArch);
ofstream abrirOutput(const char* nombArch);

// Lectura de datos
int leerInt(ifstream& arch);
double leerDouble(ifstream& arch);
int leerDuracion(ifstream& arch);

// Impresión
void imprimirDuracion(ofstream& arch, int duracion);
void imprimirLinea(ofstream& arch, char car);

// FUNCIONES PRINCIPALES:
// Función 1:
void leerCategorias(const char *nombArch, struct Categoria *arrCategorias, int &numCategorias);

// Función 2:
void leerReproducciones(const char *nombArch, struct Categoria *arrCategorias, int numCategorias);
int buscarCategoria(struct Categoria *arrCategorias, char *codigo, int numCategorias);
void insertarReproduccion(struct Categoria &c, struct Reproduccion r);

// Función 3:
void calcularPromediosYDuraciones(struct Categoria *arrCategorias, int numCategorias);
void acumularRatingYDuracion(struct Categoria &c);

// Función 4:
void verificarCategorias(const char *nombArch, const struct Categoria *arrCategorias, int numCategorias);
void imprimirReproducciones(ofstream &arch, const struct Categoria &c);
void imprimirRatingYDuracion(ofstream &arch, const struct Categoria &c);

#endif //LAB7_FUNCIONESAUXILIARES_H