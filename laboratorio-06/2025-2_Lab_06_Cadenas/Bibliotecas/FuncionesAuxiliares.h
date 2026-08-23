#ifndef LAB6_FUNCIONESAUXILIARES_H
#define LAB6_FUNCIONESAUXILIARES_H

#include "Utils.h"

// Funciones secundarias:
// Apertura de archivos
ifstream abrirInput(const char* nombArch);
ofstream abrirOutput(const char* nombArch);

// Lectura de datos
int leerDuracion(ifstream& arch);
int leerFecha(ifstream& arch);
char* leerCadena(ifstream& arch);

// Impresión
void imprimirDuracion(ofstream& arch, int duracion);
void imprimirLinea(ofstream& arch, char car);


// Funciones principales:
// Parte 2:
void generaArchivoEnlace(const char* categoria, char*& nombArch, char*& enlace);

// Parte 3:
void leerCategorias(const char* nombArch, char** arrCodCate, char** arrNomCate, int& numCate);

// Parte 4:
void verificarCategorias(const char* nombArch, char** arrCodCate, char** arrNomCate, int numCate);

// Parte 5:
void leerReproducciones(const char* nombArch, int* arrFecha, char** arrNomCanal,
                        char** arrCodCateCanal, double* arrRating, double* arrDropOff,
                        int* arrDuracion, int& numStream);

// Parte 6:
void verificarReproducciones(const char* nombArch, int* arrFecha, char** arrNomCanal,
                             char** arrCodCateCanal, double* arrRating, double* arrDropOff,
                             int* arrDuracion, int numStream);

// Parte 7:
void emitirReportes(char** arrCodCate, char** arrNomCate, int numCate,
                    int* arrFecha, char** arrNomCanal, char** arrCodCateCanal, double* arrRating,
                    double* arrDropOff, int* arrDuracion, int numStream);
void imprimirEncabezado(ofstream& arch, char* codigo, char* nombre, char* enlace);
void imprimirReproducciones(ofstream& arch, char* codigo, int* arrFecha,
                            char** arrNomCanal, char** arrCodCateCanal, double* arrRating,
                            double* arrDropOff, int* arrDuracion, int numStream);
void imprimirSubtituloReproducciones(ofstream& arch);
void imprimirResumen(ofstream& arch, double promRating, double promDropOff, int duracionTotal, int cant);

#endif //LAB6_FUNCIONESAUXILIARES_H
