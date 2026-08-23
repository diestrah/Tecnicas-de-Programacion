#ifndef LAB4_FUNCIONESAUXILIARES_H
#define LAB4_FUNCIONESAUXILIARES_H
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

void leerTarifa(double& tarifa);

void leerCanales(const char* nombArch,
                 int* arrFechaCanal, int* arrCodCanal, char* arrLetraCodCanal,
                 double* arrRatingCanal, int& numCanal);

void leerEtiquetas(const char* nombArch,
                   int* arrCodEtiq, int* arrDuraEtiq, int& numEtiqueta);

void verificarArrays(const char* nombArch,
                     int* arrFechaCanal, int* arrCodCanal, char* arrLetraCodCanal,
                     double* arrRatingCanal, int numCanal,
                     int* arrCodEtiq, int* arrDuraEtiq, int numEtiqueta);

void verificarArrays(const char* nombArch,
                     int* arrFechaCanal, int* arrCodCanal, char* arrLetraCodCanal,
                     double* arrRatingCanal, int numCanal,
                     int* arrCodEtiq, int* arrDuraEtiq, int numEtiqueta);

void leerReproduccionesYCompletarArraysAuxiliares(const char* nombArch,
                                                  char* arrLetraCodCanal, int* arrCodCanal, double* arrRatingCanal,
                                                  int numCanal,
                                                  int* arrCodEtiq, int* arrDuraEtiq, int numEtiqueta, double tarifa,
                                                  int* arrTotalReprodCanal, int* arrCantReprodCanal,
                                                  int* arrPorcentRating, double* arrIngresosCanal,
                                                  int* arrTotalReprodEtiq, int* arrCantReprodEtiq);

int buscarEtiqueta(int codEtiq, int* arrCodEtiq, int numEtiqueta);

void completarArraysDeEtiquetas(int& totalReprodEtiq, int& cantReprod,
                                int duracion, int cant);

int buscarCanal(char letraCanal, int codCanal, char* arrLetraCodCanal,
                int* arrCodCanal, int numCanal);

void completarArraysDeCanales(int& totalReprodCanal, int& cantReprodCanal, int& porcentRating, double& ingresosCanal,
                              double ratingCanal, int duracion, int cant, double tarifa);


void emitirReporte(const char* nombArch,
                 int* arrFechaCanal, int* arrCodCanal, char* arrLetraCodCanal,
                 double* arrRatingCanal,
                 int* arrTotalReprodCanal, int* arrCantReprodCanal,
                 int* arrPorcentRating, double* arrIngresosCanal, int numCanal,
                 int* arrCodEtiq, int* arrDuraEtiq, int* arrTotalReprodEtiq, int* arrCantReprodEtiq,
                 int numEtiqueta, double tarifa);

void imprimirEncabezado(ofstream& arch, double tarifa);

void imprimirSubtitulos(ofstream& arch, char parametro);


#endif //LAB4_FUNCIONESAUXILIARES_H
