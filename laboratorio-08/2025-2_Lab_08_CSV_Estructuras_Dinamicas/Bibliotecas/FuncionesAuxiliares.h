#ifndef LAB8_FUNCIONESAUXILIARES_H
#define LAB8_FUNCIONESAUXILIARES_H

#include "Utils.h"

/*------------------------------------------------------------------*/
// Funciones SECUNDARIAS --------------------------------------------
/*------------------------------------------------------------------*/
// Funciones de apertura de archivos
ifstream abrirInput(const char* nombArch);
ofstream abrirOutput(const char* nombArch);

// Funciones de lectura de datos
int leerInt(ifstream& arch);
double leerDouble(ifstream& arch);
char* leerString(ifstream& arch, char delim);
int leerDuracion(ifstream& arch);

// Funciones ayuda de impresión
void imprimirDuracion(ofstream& arch, int duracion);
void imprimirLinea(ofstream& arch, char car);

/*------------------------------------------------------------------*/
// Funciones PRINCIPALES --------------------------------------------
/*------------------------------------------------------------------*/
// Función 1:
void leerCategorias(const char* nombArch, struct Categoria* arrCategorias, int& numCate);

// Función 2:
void leerStreams(const char* nombArch, struct Categoria* arrCategorias, int numCate);
int buscarCategoria(const struct Categoria* arrCategorias, char* codigo, int numCate);
void insertarReproduccion(struct Categoria& c, const struct Reproduccion& r);

// Función 3:
void ordenarArray(struct Categoria* arrCategorias, int numCate);
void cambiarStruct(struct Categoria& i, struct Categoria& j);

// Función 4:
void leerComentarios(const char* nombArch, struct Categoria* arrCategorias, int numCate);
void recorrerCanalesEInsertarComentario(struct Categoria* arrCategorias, char* canal, char* comentario, int numCate);
void insertarComentarioEnCanal(struct Categoria& c, char* canal, char* comentario, int numReprod);

// Función 5:
void verificarCategorias(const char* nombArch, const struct Categoria* arrCategorias, int numCate);
void imprimirReproducciones(ofstream& arch, const struct Categoria& c);
void imprimirComentarios(ofstream& arch, const struct Reproduccion& r);

#endif //LAB8_FUNCIONESAUXILIARES_H
