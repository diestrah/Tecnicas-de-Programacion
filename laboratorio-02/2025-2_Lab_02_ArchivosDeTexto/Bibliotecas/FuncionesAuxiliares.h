#ifndef INC_2025_2_FIXED_FUNCIONESAUXILIARES_H
#define INC_2025_2_FIXED_FUNCIONESAUXILIARES_H
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

void solicitarFechas(int& fechaIni, int& fechaFin, double& tarifaReprod, double& tarifaDura);
void leerEImprimirReporte(const char* nombArchDat, const char* nombArchRep,
                          int fechaIni, int fechaFin, double tarifaReprod, double tarifaDura);
void imprimirEncabezado(ofstream& archRep, int fechaIni, int fechaFin, double tarifaReprod, double tarifaDura);
void imprimirDatos(ifstream& archDat, ofstream& archRep,
                   int& cantFinal, int& duraFinal, double& ingresoDuraFinal, double& ingresoPubliFinal,
                   int fechaIni, int fechaFin, double tarifaReprod, double tarifaDura);
void imprimirSubtitulos(ifstream& archDat, ofstream& archRep, int fecha, int contador, double& index);

void imprimirReproduccionesYResumen(ifstream& archDat, ofstream& archRep, int& duraTotal, int& cantFinal,
                                    double& ingresoRepTotal,
                                    double& ingresoDuraTotal, double tarifaReprod, double tarifaDura, double index);
void imprimirResumenCanal(ofstream& archRep, int duraTotal, double ingresoDuraTotal, int repTotal,
                          double ingresoRepTotal, double index);
void imprimirResumenFinal(ofstream& archRep, int cantFinal, int duraFinal, double ingresoDuraFinal,
                          double ingresoRepFinal);

#endif //INC_2025_2_FIXED_FUNCIONESAUXILIARES_H
