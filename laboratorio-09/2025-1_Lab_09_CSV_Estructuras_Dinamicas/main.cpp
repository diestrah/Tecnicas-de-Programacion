#include "Bibliotecas/FuncionesAuxiliares.h"
#define MAX_INFR 150
#define MAX_EMPR 50

int main() {
    struct TablaDeInfracciones arrTablaDeInfracciones[MAX_INFR]{};
    struct EmpresasRegistradas arrEmpresasRegistradas[MAX_EMPR]{};
    int numInfracciones = 0, numEmpresas = 0;

    leerTablaDeInfracciones("ArchivosDeDatos/TablaDeInfracciones_Lab09.csv",
                            arrTablaDeInfracciones, numInfracciones);
    verificarTablaDeInfracciones("ArchivosDeReportes/PruebaDeTablaDeInfracciones.txt",
                                 arrTablaDeInfracciones, numInfracciones);
    leerEmpresasRegistradas("ArchivosDeDatos/EmpresasRegistradas_Lab09.csv",
                            arrEmpresasRegistradas, numEmpresas);
    verificarEmpresasRegistradas("ArchivosDeReportes/PruebaDeEmpresasRegistradas.txt",
                                 arrEmpresasRegistradas, numEmpresas);
    leerPlacasRegistradas("ArchivosDeDatos/PlacasRegistradas_Lab09.csv",
                          arrEmpresasRegistradas, numEmpresas);
    leerInfraccionesCometidas("ArchivosDeDatos/InfraccionesCometidas_Lab09.csv",
                              arrTablaDeInfracciones, numInfracciones,
                              arrEmpresasRegistradas, numEmpresas);
    calcularTotales(arrEmpresasRegistradas, numEmpresas);
    ordenarEmpresasRegistradas(arrEmpresasRegistradas, numEmpresas);

    emitirReporte("ArchivosDeReportes/ReporteDeInfraccionesPorEmpresa.txt",
                  arrEmpresasRegistradas, numEmpresas);

    return 0;
}
