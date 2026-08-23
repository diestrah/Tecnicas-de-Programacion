#ifndef INC_2024_1_LAB_08_CSV_ESTRUCTURAS_FUNCIONESAUXILIARES_H
#define INC_2024_1_LAB_08_CSV_ESTRUCTURAS_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#include "Facultad.h"
#include "Alumno.h"

void leerCalificaciones(const char* nombArch, struct Alumno *arrAlumnos, int& numAlumnos);
void leerDatosAlumnos(ifstream& arch, const double creditos, struct Alumno* arrAlumnos, int& numAlumnos);
int buscarAlumno(const int codAlumno, const struct Alumno* arrAlumnos, const int numAlumnos);
void actualizarDatos(const double creditos, const int nota, struct Alumno &a);
void leerAlumnos(const char* nombArch, struct Alumno *arrAlumnos, const int numAlumnos);
void leerFacultades(const char* nombArch, struct Alumno *arrAlumnos, const int numAlumnos);
void emitirReporte(const char* nombArch, const struct Alumno *arrAlumnos, const int numAlumnos);
void imprimirEncabezado(ofstream& arch);
void imprimirSubtitulos(ofstream& arch);
void imprimirRegistrosDeAlumnos(ofstream& arch, const struct Alumno *arrAlumnos, const int numAlumnos);

#endif //INC_2024_1_LAB_08_CSV_ESTRUCTURAS_FUNCIONESAUXILIARES_H