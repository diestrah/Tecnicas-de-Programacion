/*------------------------------------------------------------------------------------------*/
/*  Autor       	:   Naim Diestra
/*  Fecha creación  :   10/12/2025
/*  Actualización   :   03/05/2026
/*------------------------------------------------------------------------------------------*/

#include "Bibliotecas/FuncionesAuxiliares.h"
#define MAX_INFRAC 200
#define MAX_EMPR 50

int main() {
    struct TablaDeInfracciones arrTablaDeInfracciones[MAX_INFRAC]{};
    struct EmpresasRegistradas arrEmpresasRegistradas[MAX_EMPR]{};
    int numInfrac = 0, numEmpr = 0;

    leerTablaDeInfracciones("ArchivosDeDatos/TablaDeInfracciones_Lab08.csv",
                            arrTablaDeInfracciones, numInfrac);
    leerEmpresasRegistradas("ArchivosDeDatos/EmpresasRegistradas_Lab08.csv",
                            arrEmpresasRegistradas, numEmpr);
    leerPlacasRegistradas("ArchivosDeDatos/PlacasRegistradas_Lab08.txt",
                          arrEmpresasRegistradas, numEmpr);
    leerInfraccionesCometidas("ArchivosDeDatos/InfraccionesCometidas_Lab08.csv",
                              arrEmpresasRegistradas, numEmpr, arrTablaDeInfracciones, numInfrac);

    ordenarEmpresasRegistradas(arrEmpresasRegistradas, numEmpr);
    ordenarTablaDeInfracciones(arrTablaDeInfracciones, numInfrac);

    emitirReporte("ArchivosDeReportes/Reporte.txt", arrEmpresasRegistradas, numEmpr,
                  arrTablaDeInfracciones, numInfrac);

    return 0;
}
