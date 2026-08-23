#ifndef INC_2025_2_LABORATORIO_03_FUNCIONESAUXILIARES_H
#define INC_2025_2_LABORATORIO_03_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

void leerTarifa(double &tarifa);

void leerDatosYEmitirReporte(const char* nombArchCana,
                             const char* nombArchEtiq,
                             const char* nombArchRepro,
                             const char* nombArchRepo,
                             double tarifa);

void imprimirEncabezado(ofstream &archRepo, double tarifa);

void imprimirCanales(ifstream& archCana, ifstream& archRepro, ifstream& archEtiq,
                     ofstream& archRepo, double tarifa);
void imprimirSubtitulosCanales(ofstream &arch, int contadorCanal);
void imprimirDatosCanales(ofstream &archRepo, char letra, int codigo, int fecha, double rating);

void imprimirReproducciones(ifstream &archRepro, ifstream &archEtiq, ofstream &archRepo,
    double tarifa, char letra, int codigo, double rating);
void imprimirSubtitulosReproducciones(ofstream &archRepo);
void imprimirDatosReproducciones(ifstream& archEtiq, ofstream& archRepo, int contadorEtiq,
                                 int fecha, int codEtiqueta, int reproducciones, int& duracionTotal);
void imprimirEtiquetas(ifstream &archEtiq, ofstream &archRepo, int codEtiqueta, int &duracion);
void imprimirRating(ofstream& archRepo, double rating, int& porcentaje);
void imprimirResumenReproducciones(ofstream& archRepo, int duracionTotal, double rating, double tarifa);

#endif //INC_2025_2_LABORATORIO_03_FUNCIONESAUXILIARES_H