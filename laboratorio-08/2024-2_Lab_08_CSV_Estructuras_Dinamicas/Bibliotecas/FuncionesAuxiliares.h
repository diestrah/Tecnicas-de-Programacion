#ifndef INC_2024_2_LAB_08_CSV_ESTRUCTURAS_DINAMICAS_FUNCIONESAUXILIARES_H
#define INC_2024_2_LAB_08_CSV_ESTRUCTURAS_DINAMICAS_FUNCIONESAUXILIARES_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;
#include "PlatoPedido.h"
#include "Cliente.h"
#include "Plato.h"
#include "Distrito.h"


void leerPlatosOfrecidos(const char* nombArch, struct Plato* arrPlatos, int& numPlatos);
void leerClientes(const char* nombArch, struct Cliente* arrClientes, int& numClientes);
void leerDistritos(const char* nombArch, struct Distrito* arrDistritos, int& numDistritos);
void verificarPlatosOfrecidos(const char* nombArch, const struct Plato* arrPlatos, const int numPlatos);
void verificarClientes(const char* nombArch, const struct Cliente* arrClientes, const int numClientes);
void verificarDistritos(const char* nombArch, const struct Distrito* arrDistritos, const int numDistritos);
void leerPedidosYCompletarArrays(const char* nombArch, struct Plato* arrPlatos, const int numPlatos,
                                 struct Cliente* arrClientes, const int numClientes,
                                 const struct Distrito* arrDistritos, const int numDistritos);
int buscarCliente(const int dni, const struct Cliente* arrClientes, const int numClientes);
void actualizarDistrito(struct Cliente& c, const struct Distrito* arrDistritos, int numDistritos);
int buscarDistrito(char* codDistrito, const struct Distrito* arrDistritos, const int numDistritos);
void completarDatosClientes(const int codPedido, const char* codPlato, const int cant,
                            struct Cliente& c, struct Plato* arrPlatos, const int numPlatos);
int buscarPlato(const char* codPlato, const struct Plato* arrPlatos, const int numPlatos);
void ordenarClientes(struct Cliente* arrClientes, const int numClientes);
void ordenarPlatos(struct Plato* arrPlatos, const int numPlatos);
void emitirReporte(const char* nombArch, const struct Cliente* arrClientes, const int numClientes);
void imprimirEncabezado(ofstream& arch);
void imprimirClientes(ofstream& arch, const struct Cliente* arrClientes, const int numClientes);
void imprimirSubtitulosClientes(ofstream& arch, const int i);
void imprimirPedidos(ofstream& arch, const struct PlatoPedido* arrPedidos, const int numPedidos);
void imprimirSubtitulosPedidos(ofstream& arch);

#endif //INC_2024_2_LAB_08_CSV_ESTRUCTURAS_DINAMICAS_FUNCIONESAUXILIARES_H
