#ifndef LAB5_FUNCIONESAUXILIARES_H
#define LAB5_FUNCIONESAUXILIARES_H

#include "Utils.h"

// Funciones secundarias:
// De apertura de archivos
ifstream abrirInput(const char* nombArch);
ofstream abrirOutput(const char* nombArch);

// De lectura
int leerDuracion(ifstream& arch);
int leerFecha(ifstream& arch);

// De impresión
void imprimirDuracion(ofstream& arch, int duracion);
void imprimirFecha(ofstream& arch, int fecha);
void imprimirLinea(ofstream& arch, char car);

// De suprimir
void suprimir(ifstream& arch, char car);

// Funciones de intercambio
void cambiarInt(int& i, int& j);
void cambiarDouble(double& i, double& j);
void cambiarChar(char& i, char& j);


// Funciones de lectura, impresión y ordenación:

// Funciones parte a:
void leerStreamsOrdenado(const char* nombArch,
                         int* arrCodStream, int* arrDuracion, int* arrIdioma,
                         char* arrLetraCate, int* arrCodCate, int& numStream);
void insertarOrdenado(int codStream, int duracion, int idioma, char letraCate, int codCate,
                      int* arrCodStream, int* arrDuracion, int* arrIdioma,
                      char* arrLetraCate, int* arrCodCate, int& numStream);

// Función parte b:
void verificarArraysDeStreams(const char* nombArch,
                              int* arrCodStream, int* arrDuracion, int* arrIdioma,
                              char* arrLetraCate, int* arrCodCate,
                              int numStream);

// Funciones parte c:
void leerCanales(const char* nombArch, int* arrCodStream, int numStream,
                 int* arrCantReprod, int* arrTotalReprod, int* arrRepAntigua,
                 int* arrRepReciente, double* arrPromRating, double* arrPromDropOff);
void leerInfoStreams(ifstream& arch, int* arrCodStream, int numStream,
                     int* arrCantReprod, int* arrTotalReprod, int* arrRepAntigua,
                     int* arrRepReciente, double* arrPromRating, double* arrPromDropOff);
int buscarStream(int codigo, int* arrCodStream, int numStream);
void insertarDatos(ifstream& arch, int& cantReprod, int& totalReprod, int& repAntigua,
                   int& repReciente, double& promRating, double& promDropOff);

// Funciones parte d:
void ordernarPorRatingYDropOff(int* arrCodStream, int* arrDuracion,
                               int* arrIdioma, char* arrLetraCate, int* arrCodCate,
                               int* arrCantReprod, int* arrTotalReprod, int* arrRepAntigua,
                               int* arrRepReciente, double* arrPromRating, double* arrPromDropOff,
                               int numStream);

// Funciones parte e:
void emitirReporte(const char* nombArch, int* arrCodStream, int* arrDuracion,
                   int* arrIdioma, char* arrLetraCate, int* arrCodCate,
                   int* arrCantReprod, int* arrTotalReprod, int* arrRepAntigua,
                   int* arrRepReciente, double* arrPromRating, double* arrPromDropOff,
                   int numStream, bool resumen);
void imprimirEncabezado(ofstream& arch, bool resumen);
void filtrarDuraciones(int codigo, int duracion, int& maxStream,
                       int& maxDura, int& minStream, int& minDura);
void imprimirResumen(ofstream& arch, int maxStream, int maxDura, int minStream, int minDura);

#endif //LAB5_FUNCIONESAUXILIARES_H
