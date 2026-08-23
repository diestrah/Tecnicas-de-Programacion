#ifndef INC_2025_2_LAB_09_LISTAS_LIGADAS_FUNCIONESAUXILIARES_H
#define INC_2025_2_LAB_09_LISTAS_LIGADAS_FUNCIONESAUXILIARES_H
#include "Nodo.h"
#include "Utils.h"

// Sección leer "Categorias.csv"
void leerCategorias(const char* nombArch, struct Nodo*& lista);
void insertarCategoria(struct Nodo*& lista, const struct Categoria& c);

// Sección Impresión de reporte
void emitirReporte(const char* nombArch, struct Nodo* lista);
void imprimirCategoria(ofstream& arch, const struct Categoria& c);
void imprimirDescripcionCategoria(ofstream& arch, const struct Categoria& c);
void imprimirInformacionReproducciones(ofstream& arch, const struct Categoria& c);
void imprimirArrayDropOff(ofstream& arch, const double* arrDropOff, int cant);

// Sección leer "StreamsReproducidos.csv"
void leerStreams(const char* nombArch, struct Nodo* lista);
struct Nodo* buscarCategoria(struct Nodo* lista, char* codigo);
void completarDatosCategoria(ifstream& arch, struct Categoria& c);

// Sección calcular promedio dropOff
void calcularPromedio(struct Categoria& c);
void calcularDropOff(struct Nodo* lista);

// Sección eliminar categorias con dropOff < 3.5
void eliminarMenoresDropOff(struct Nodo*& lista);

#endif //INC_2025_2_LAB_09_LISTAS_LIGADAS_FUNCIONESAUXILIARES_H