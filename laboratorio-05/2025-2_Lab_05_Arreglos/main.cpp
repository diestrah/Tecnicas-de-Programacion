/*------------------------------------------------------------------------------------*/
/*  Elaborado por   :   Naim Diestra
/*  Fecha creación  :   11/12/2025
/*  Actualizacion   :   02/05/2026
/*  Descripcion     :   Se almacenan en arrays los datos de Streams.txt y se completan los
/*                      arrays auxiliares con Canales.txt y se emite un reporte final.
/*                      Se refuerza el ordenamiento de datos y la inserción ordenada.
/*------------------------------------------------------------------------------------*/

#include "Bibliotecas/FuncionesAuxiliares.h"
#define MAX_STREAM 150

int main() {
    // Parte a: variables y función utilizada para leer los datos de Streams.txt
    int arrCodStream[MAX_STREAM], arrDuracion[MAX_STREAM],
        arrIdioma[MAX_STREAM], arrCodCate[MAX_STREAM], numStream = 0;
    char arrLetraCate[MAX_STREAM];
    leerStreamsOrdenado("ArchivosDeDatos/Streams.txt",
                        arrCodStream, arrDuracion, arrIdioma,
                        arrLetraCate, arrCodCate, numStream);

    // Parte b: impresión de data del código
    verificarArraysDeStreams("ArchivosDeReportes/ReporteArraysDeStreams.txt",
                             arrCodStream, arrDuracion, arrIdioma,
                             arrLetraCate, arrCodCate, numStream);

    // Parte c: variables y función utilizada para leer los datos de Canales.txt
    int arrCantReprod[MAX_STREAM]{}, arrTotalReprod[MAX_STREAM]{},
        arrRepAntigua[MAX_STREAM], arrRepReciente[MAX_STREAM];
    double arrPromRating[MAX_STREAM]{}, arrPromDropOff[MAX_STREAM]{};
    leerCanales("ArchivosDeDatos/Canales.txt",
                arrCodStream, numStream, arrCantReprod,
                arrTotalReprod, arrRepAntigua, arrRepReciente,
                arrPromRating, arrPromDropOff);

    // Parte d: impresión del reporte
    emitirReporte("ArchivosDeReportes/ReproduccionesStreams.txt",
                  arrCodStream, arrDuracion, arrIdioma, arrLetraCate, arrCodCate,
                  arrCantReprod, arrTotalReprod, arrRepAntigua, arrRepReciente,
                  arrPromRating, arrPromDropOff, numStream, true);

    // Parte e: ordenación ascendente por categoría y descendente por tasa drop off
    ordernarPorRatingYDropOff(arrCodStream, arrDuracion, arrIdioma, arrLetraCate, arrCodCate,
                              arrCantReprod, arrTotalReprod, arrRepAntigua, arrRepReciente,
                              arrPromRating, arrPromDropOff, numStream);

    // Parte f: Impresión del reporte final
    emitirReporte("ArchivosDeReportes/ReproduccionesStreamsOrdenadoPorPromedios.txt",
                  arrCodStream, arrDuracion, arrIdioma, arrLetraCate, arrCodCate,
                  arrCantReprod, arrTotalReprod, arrRepAntigua, arrRepReciente,
                  arrPromRating, arrPromDropOff, numStream, false);

    return 0;
}
