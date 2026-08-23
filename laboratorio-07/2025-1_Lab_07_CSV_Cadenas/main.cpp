/*----------------------------------------------------------------------------------------*/
/*  Autor           :   Naim Diestra
/*  Fecha creación  :   26/01/2026 
/*  Descripción :   pendiente xd
/*  Falta corregir la forma en que se buscan las placas y los subtitulos
/*----------------------------------------------------------------------------------------*/

#include "Bibliotecas/FuncionesAuxiiares.h"
#define MAX_EMPR 50
#define MAX_INFRAC 150
#define TAM_PLA 60

int main() {
    int arrDni[MAX_EMPR], arrFechaAnt[MAX_EMPR], arrFechaNueva[MAX_EMPR], arrCantFaltas[MAX_EMPR]{};
    double arrTotalLeves[MAX_EMPR]{}, arrTotalGraves[MAX_EMPR]{}, arrTotalMuyGraves[MAX_EMPR]{}, arrMulta[MAX_INFRAC];
    char *arrNombre[MAX_EMPR], *arrDistrito[MAX_EMPR],
         *arrPlacas[MAX_EMPR], *arrCodInfrac[MAX_INFRAC], *arrDesInfrac[MAX_INFRAC];
    int numEmpresas = 0, numInfracciones = 0;

    inicializarPlacas(arrPlacas, TAM_PLA, MAX_EMPR);

    leerEmpresasRegistradas("ArchivosDeDatos/EmpresasRegistradas_Lab07.csv",
                            arrDni, arrNombre, arrDistrito, numEmpresas);

    leerPlacasRegistradas("ArchivosDeDatos/PlacasRegistradas_Lab07.txt",
                          arrDni, arrPlacas, numEmpresas);

    verificarEmpresasYPlacasRegistradas("ArchivosDeReporte/ReporteDePrueba01.txt",
                                        arrDni, arrNombre, arrDistrito, arrPlacas, numEmpresas);

    leerTablaDeInfracciones("ArchivosDeDatos/TablaDeInfracciones_Lab07.csv",
                            arrCodInfrac, arrMulta, arrDesInfrac, numInfracciones);

    verificarTablaDeInfracciones("ArchivosDeReporte/ReporteDePrueba02.txt",
                                 arrCodInfrac, arrMulta, arrDesInfrac, numInfracciones);

    leerInfraccionesCometidas("ArchivosDeDatos/InfraccionesCometidas_Lab07.csv",
                              arrPlacas, arrFechaAnt, arrFechaNueva, arrTotalLeves, arrTotalGraves,
                              arrTotalMuyGraves, arrCantFaltas, numEmpresas,
                              arrCodInfrac, arrMulta, numInfracciones);

    ordenarArreglos(arrDni, arrNombre, arrDistrito, arrPlacas, arrFechaAnt, arrFechaNueva,
                    arrTotalLeves, arrTotalGraves, arrTotalMuyGraves, arrCantFaltas, numEmpresas);

    emitirReporte("ArchivosDeReporte/ReporteDeInfracciones.txt", arrDni, arrNombre, arrDistrito,
                  arrPlacas, arrFechaAnt, arrFechaNueva, arrTotalLeves, arrTotalGraves,
                  arrTotalMuyGraves, arrCantFaltas, numEmpresas);

    return 0;
}
