#ifndef INC_2025_1_LAB_09_CSV_ESTRUCTURAS_DINAMICAS_FUNCIONESAUXILIARES_H
#define INC_2025_1_LAB_09_CSV_ESTRUCTURAS_DINAMICAS_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#include "Fecha.h"
#include "InfraccionCometida.h"
#include "TablaDeInfracciones.h"
#include "EmpresasRegistradas.h"

void leerTablaDeInfracciones(const char* nombArch, struct TablaDeInfracciones* arrTablaDeInfracciones,
                             int& numInfracciones);
void verificarTablaDeInfracciones(const char* nombArch, const struct TablaDeInfracciones* arrTablaDeInfracciones,
                                  const int numInfracciones);
void leerEmpresasRegistradas(const char* nombArch, struct EmpresasRegistradas* arrEmpresasRegistradas,
                             int& numEmpresas);
void verificarEmpresasRegistradas(const char* nombArch, const struct EmpresasRegistradas* arrEmpresasRegistradas,
                                  const int numEmpresas);
void leerPlacasRegistradas(const char* nombArch, struct EmpresasRegistradas* arrEmpresasRegistradas,
                           const int numEmpresas);
int buscarEmpresaPorDni(const int dni, const struct EmpresasRegistradas* arrEmpresasRegistradas,
                        const int numEmpresas);
void leerInfraccionesCometidas(const char* nombArch,
                               const struct TablaDeInfracciones* arrTablaDeInfracciones, const int numInfracciones,
                               struct EmpresasRegistradas* arrEmpresasRegistradas, const int numEmpresas);
int buscarEmpresaPorPlaca(const char* placa, const struct EmpresasRegistradas* arrEmpresasRegistradas,
                          const int numEmpresas);
void insertarDatos(struct EmpresasRegistradas& e, struct InfraccionCometida i,
                   const struct TablaDeInfracciones* arrTablaDeInfracciones, const int numInfracciones);
int buscarInfraccion(const char* codigoInfraccion, const struct TablaDeInfracciones* arrTablaDeInfracciones,
                     const int numInfracciones);
void calcularTotales(struct EmpresasRegistradas* arrEmpresasRegistradas, const int numEmpresas);
void ordenarEmpresasRegistradas(struct EmpresasRegistradas* arrEmpresasRegistradas, const int numEmpresas);
void emitirReporte(const char* nombArch, const struct EmpresasRegistradas* arrEmpresasRegistradas,
                   const int numEmpresas);
void imprimirEncabezado(ofstream& arch);
void imprimirSubtitulosEmpresa(ofstream& arch, const struct EmpresasRegistradas e,
                               const int i);
char* concatenarPlacas(struct InfraccionCometida* arrInfracciones, const int numPlacas);
void imprimirSubtitulosPlacas(ofstream& arch);
void imprimirPlacas(ofstream& arch, const struct InfraccionCometida* arrInfracciones, const int numInfracciones);




#endif //INC_2025_1_LAB_09_CSV_ESTRUCTURAS_DINAMICAS_FUNCIONESAUXILIARES_H
