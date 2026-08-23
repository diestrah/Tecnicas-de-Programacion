#ifndef INC_2025_1_LAB_10_LISTAS_LIGADAS_FUNCIONESAUXILIARES_H
#define INC_2025_1_LAB_10_LISTAS_LIGADAS_FUNCIONESAUXILIARES_H

#include "Utils.h"
#include "Nodo.h"

/*
 *  Módulos Secundarios
*/
void abrirInput(ifstream& arch, const char* nombArch);
void abrirOutput(ofstream& arch, const char* nombArch);

int leerInt(ifstream& arch);
double leerDouble(ifstream& arch);
char* leerString(ifstream& arch, char delim);
int leerFecha(ifstream& arch);

void imprimirLinea(ofstream& arch, char car);
void imprimirFecha(ofstream& arch, int fecha);


/*
 *  Módulos Principales
*/

void leerCuentasBancarias(const char* nombArch, struct Nodo*& lista);
void insertarCuenta(Nodo*& lista, const struct Cuenta& c);

void leerMovimientosDeCuentas(const char* nombArch, struct Nodo* lista);
struct Nodo* buscarCuenta(Nodo* lista, int codCuenta);
void completarDatosCuenta(struct Nodo* cuenta, int fecha, double monto);

void emitirReporteCuentas(const char* nombArch, struct Nodo* lista);
void imprimirEncabezado(ofstream& arch);
void imprimirContador(ofstream& arch, int contador);
void imprimirCuenta(ofstream& arch, const struct Cuenta& c);

void eliminarCuentasConSaldoPositivo(struct Nodo*& lista);

#endif //INC_2025_1_LAB_10_LISTAS_LIGADAS_FUNCIONESAUXILIARES_H
