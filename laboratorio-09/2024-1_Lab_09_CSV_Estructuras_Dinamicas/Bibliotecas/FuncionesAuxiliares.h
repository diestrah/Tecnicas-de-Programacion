#ifndef INC_2024_1_LAB_09_CSV_ESTRUCTURAS_DINAMICAS_FUNCIONESAUXILIARES_H
#define INC_2024_1_LAB_09_CSV_ESTRUCTURAS_DINAMICAS_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#include "Cliente.h"
#include "Fecha.h"
#include "Venta.h"
#include "Libro.h"

void leerClientes(const char* nombArch, struct Cliente* arrClientes, int& numClientes);
void leerLibros(const char* nombArch, struct Libro* arrLibros, int& numLibros);
void leerVentas(const char* nombArch, struct Libro* arrLibros, const int numLibros);
int buscarLibro(const char* codLibro, const struct Libro* arrLibros, const int numLibros);
void determinarRankings(struct Libro* arrLibros, const int numLibros);
void ordenarLibrosPorRankingYTitulo(struct Libro* arrLibros, const int numLibros);
void emitirReporte(const char* nombArch, const struct Cliente* arrClientes, const int numClientes,
                   const struct Libro* arrLibros, const int numLibros);
void imprimirEncabezado(ofstream& arch);
void imprimirLibrosYVentas(ofstream& arch, const struct Cliente* arrClientes, const int numClientes,
                   const struct Libro* arrLibros, const int numLibros);
void imprimirSubtitulosLibros(ofstream& arch, const int i);
void imprimirVentas(ofstream& arch, const struct Cliente *arrClientes, const int numClientes,
                    const struct Venta *arrVentas, const int numVentas);
int buscarCliente(const int dni, const struct Cliente *arrClientes, const int numClientes);


#endif //INC_2024_1_LAB_09_CSV_ESTRUCTURAS_DINAMICAS_FUNCIONESAUXILIARES_H
