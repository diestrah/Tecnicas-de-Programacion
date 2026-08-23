/*------------------------------------------------------------------------------------*/
/*  Nombre      :   Naim Diestra
/*  Fecha       :   12/12/2025
/*  Descripcion :   Se almacenan en arrays los datos de Streams.txt y se completan los
/*                  arrays auxiliares con Canales.txt y se emite un reporte final.
/*                  Se refuerza el ordenamiento de datos y la inserción ordenada.
/*------------------------------------------------------------------------------------*/

#include "Bibliotecas/FuncionesAuxiliares.h"
#define MAX_CANAL 120
#define MAX_ETIQ 120

int main() {
    int arrFechaCanal[MAX_CANAL], arrCodCanal[MAX_CANAL];
    char arrLetraCodCanal[MAX_CANAL];
    double arrRatingCanal[MAX_CANAL];
    int arrCodEtiq[MAX_ETIQ], arrDuraEtiq[MAX_ETIQ];
    int numCanal=0, numEtiqueta=0;
    double tarifa;

    int arrTotalReprodCanal[MAX_CANAL]{}, arrCantReprodCanal[MAX_CANAL]{},
        arrPorcentRating[MAX_CANAL]{};
    int arrTotalReprodEtiq[MAX_ETIQ]{}, arrCantReprodEtiq[MAX_ETIQ]{};
    double arrIngresosCanal[MAX_CANAL]{};

    leerTarifa(tarifa);

    leerCanales("ArchivosDeDatos/Canales.txt",
        arrFechaCanal, arrCodCanal, arrLetraCodCanal, arrRatingCanal, numCanal);

    leerEtiquetas("ArchivosDeDatos/Etiquetas.txt",
        arrCodEtiq, arrDuraEtiq, numEtiqueta);

    verificarArrays("ArchivosDeReportes/ReportePruebaArrays",
        arrFechaCanal, arrCodCanal, arrLetraCodCanal, arrRatingCanal, numCanal,
        arrCodEtiq, arrDuraEtiq, numEtiqueta);

    leerReproduccionesYCompletarArraysAuxiliares("ArchivosDeDatos/ReproduccionesDeEtiquetas.txt",
        arrLetraCodCanal, arrCodCanal, arrRatingCanal, numCanal,
        arrCodEtiq, arrDuraEtiq, numEtiqueta, tarifa,
        arrTotalReprodCanal, arrCantReprodCanal, arrPorcentRating, arrIngresosCanal,
        arrTotalReprodEtiq, arrCantReprodEtiq);

    emitirReporte("ArchivosDeReportes/ReporteDeCanales_Y_Etiquetas.txt",
        arrFechaCanal, arrCodCanal, arrLetraCodCanal, arrRatingCanal,
        arrTotalReprodCanal, arrCantReprodCanal, arrPorcentRating, arrIngresosCanal,
        numCanal,
        arrCodEtiq, arrDuraEtiq, arrTotalReprodEtiq, arrCantReprodEtiq, numEtiqueta,
        tarifa);

    return 0;
}