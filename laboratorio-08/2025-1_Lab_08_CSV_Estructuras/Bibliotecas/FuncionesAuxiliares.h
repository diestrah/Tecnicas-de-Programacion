#ifndef INC_2025_1_LAB_08_CSV_ESTRUCTURAS_FUNCIONESAUXILIARES_H
#define INC_2025_1_LAB_08_CSV_ESTRUCTURAS_FUNCIONESAUXILIARES_H

#include "Utils.h"

/*------------------------------------------------------------------*/
// Funciones Secundarias --------------------------------------------
/*------------------------------------------------------------------*/

// Funciones de apertura de archivos
ifstream abrirInput(const char*);
ofstream abrirOutput(const char*);

// Funciones de lectura de datos
int leerInt(ifstream&);
double leerDouble(ifstream&);
char leerChar(ifstream&);
char* leerString(ifstream&, char);
struct Fecha leerFecha(ifstream&);

// Funciones de manipulación de strings
void cambiarAMayus(char*);

// Funciónes ayuda de impresión
void imprimirLinea(ofstream&, char);
void imprimirFecha(ofstream&, struct Fecha);
void imprimirContador(ofstream&, int);

/*------------------------------------------------------------------*/
// Funciones Principales --------------------------------------------
/*------------------------------------------------------------------*/
// Módulo 1:
void leerTablaDeInfracciones(const char*, struct TablaDeInfracciones*, int&);

// Módulo 2:
void leerEmpresasRegistradas(const char*, struct EmpresasRegistradas*, int&);

// Módulo 3:
void leerPlacasRegistradas(const char*, struct EmpresasRegistradas*, int);
int buscarDni(int, const struct EmpresasRegistradas*, int);

// Módulo 4:
void leerInfraccionesCometidas(const char*, struct EmpresasRegistradas*, int,
                               struct TablaDeInfracciones*, int);
double buscarInfraccion(char*, struct TablaDeInfracciones*, int);
int buscarEmpresaPorPlaca(char*, struct EmpresasRegistradas*, int);
void insertarDatos(struct EmpresasRegistradas, double, char, struct EmpresasRegistradas&);

// Módulo 5:
void ordenarEmpresasRegistradas(struct EmpresasRegistradas*, int);
void cambiarStructEmpresas(struct EmpresasRegistradas&, struct EmpresasRegistradas&);

// Módulo 6:
void ordenarTablaDeInfracciones(struct TablaDeInfracciones*, int);
void cambiarStructInfracciones(struct TablaDeInfracciones&, struct TablaDeInfracciones&);

// Módulo 7:
void emitirReporte(const char*, struct EmpresasRegistradas*, int, struct TablaDeInfracciones*, int);
void imprimirInfraccionesDeEmpresas(ofstream&, struct EmpresasRegistradas*, int);
void imprimirEncabezadoYSubtitulos(ofstream&);
void imprimirPlacas(ofstream&, const struct EmpresasRegistradas&);
void imprimirTablaDeInfracciones(ofstream&, struct TablaDeInfracciones*, int);

#endif //INC_2025_1_LAB_08_CSV_ESTRUCTURAS_FUNCIONESAUXILIARES_H
