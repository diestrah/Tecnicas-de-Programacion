#ifndef INC_2025_1_LAB_07_CSV_CADENAS_FUNCIONESAUXIIARES_H
#define INC_2025_1_LAB_07_CSV_CADENAS_FUNCIONESAUXIIARES_H

#include "Utils.h"

// FUNCIONES SECUNDARIAS
// Apertura de archivos
ifstream abrirInput(const char* nombArch);
ofstream abrirOutput(const char* nombArch);

// Lectura de datos
int leerInt(ifstream& arch);
double leerDouble(ifstream& arch);
char leerChar(ifstream& arch);
int leerFecha(ifstream& arch);
char* leerString(ifstream& arch, char delim);

// Manipulación de cadenas
void cambiarAMayus(char* cadena);

// Impresión
void imprimirLinea(ofstream& arch, char car);
void imprimirContador(ofstream& arch, int num);
void imprimirFecha(ofstream& arch, int fecha);

// Intercambiar
void swapInt(int& a, int& b);
void swapString(char*& a, char*& b);
void swapDouble(double& a, double& b);

// FUNCIONES PRINCIPALES
// Función 1:
void inicializarPlacas(char** arrPlacas, int maxLongitud, int maxEmpresas);

// Función 2:
void leerEmpresasRegistradas(const char* nombArch, int* arrDni, char** arrNombre,
                             char** arrDistrito, int& numEmpresas);

// Función 3:
void leerPlacasRegistradas(const char* nombArch, int* arrDni, char** arrPlacas, int numEmpresas);
int buscarDni(int dni, int* arrDni, int numEmpresas);

// Función 4:
void verificarEmpresasYPlacasRegistradas(const char* nombArch, int* arrDni, char** arrNombre,
                                         char** arrDistrito, char** arrPlacas, int numEmpresas);

// Función 5:
void leerTablaDeInfracciones(const char* nombArch, char** arrCodInfrac, double* arrMulta,
                             char** arrDesInfrac, int& numInfracciones);

// Función 6:
void verificarTablaDeInfracciones(const char* nombArch, char** arrCodInfrac, double* arrMulta,
                                  char** arrDesInfrac, int& numInfracciones);

// Función 7:
void leerInfraccionesCometidas(const char* nombArch, char** arrPlacas, int* arrFechaAnt,
                               int* arrFechaNueva, double* arrTotalLeves, double* arrTotalGraves,
                               double* arrTotalMuyGraves, int* arrCantFaltas, int numEmpresas,
                               char** arrCodInfrac, double* arrMulta, int numInfracciones);
bool verificaSiEstaLaPlaca(const char* listaDePlacas, char* placa);
int buscarInfraccion(char* infraccion, char** arrCodInfrac, int numInfracciones);
int buscarEmpresa(char* placa, char** arrPlacas, int numEmpresas);
void actualizarDatos(char* infraccion, double multa, int fechaInfrac, int fechaPago,
                     int& fechaInfracAnt, int& fechaPagoNueva, double& totalLeves,
                     double& totalGraves, double& totalMuyGraves, int& cantFaltas);

// Función 8:
void ordenarArreglos(int* arrDni, char** arrNombre, char** arrDistrito, char** arrPlacas,
                     int* arrFechaAnt, int* arrFechaNueva, double* arrTotalLeves,
                     double* arrTotalGraves, double* arrTotalMuyGraves, int* arrCantFaltas,
                     int numEmpresas);

// Función 9:
void emitirReporte(const char* nombArch, int* arrDni, char** arrNombre, char** arrDistrito,
                   char** arrPlacas, int* arrFechaAnt, int* arrFechaNueva, double* arrTotalLeves,
                   double* arrTotalGraves, double* arrTotalMuyGraves, int* arrCantFaltas, int numEmpresas);

#endif //INC_2025_1_LAB_07_CSV_CADENAS_FUNCIONESAUXIIARES_H
