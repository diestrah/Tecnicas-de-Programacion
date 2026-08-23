/*--------------------------------------------------------------------------------------------------*/
/*  Autor           :   Naim Diestra
/*  Fecha creación  :   11/12/2025
/*  Actualización   :   02/05/2026
/*  Descripción     :   Se almacenan los datos de los archivos Categorias.txt y Reproducciones.txt
/*                      en arrays creados convenientemente a estos y se emite su respectivo reporte
/*                      de verificación. Luego, se crea un archivo por categoría donde se emitirá
/*                      su correspondiente reporte completo con reproducciones y resumen.
/*--------------------------------------------------------------------------------------------------*/

#include "Bibliotecas/FuncionesAuxiliares.h"
#define MAX_STREAM 450
#define MAX_CATE 120

int main() {
    int arrFecha[MAX_STREAM], arrDuracion[MAX_STREAM],
        numStream = 0, numCate = 0;
    double arrRating[MAX_STREAM], arrDropOff[MAX_STREAM];
    char *arrNomCanal[MAX_STREAM], *arrCodCateCanal[MAX_STREAM],
         *arrCodCate[MAX_CATE], *arrNomCate[MAX_CATE];

    leerCategorias("ArchivosDeDatos/Categorias.txt",
                   arrCodCate, arrNomCate, numCate);

    verificarCategorias("ArchivosDeReportes/ReportePruebaCategorias.txt",
                        arrCodCate, arrNomCate, numCate);

    leerReproducciones("ArchivosDeDatos/Reproducciones.txt",
                       arrFecha, arrNomCanal, arrCodCateCanal, arrRating,
                       arrDropOff, arrDuracion, numStream);

    verificarReproducciones("ArchivosDeReportes/ReportePruebaDeStreamsReproducidos.txt",
                            arrFecha, arrNomCanal, arrCodCateCanal, arrRating,
                            arrDropOff, arrDuracion, numStream);

    emitirReportes(arrCodCate, arrNomCate, numCate,
                   arrFecha, arrNomCanal, arrCodCateCanal, arrRating,
                   arrDropOff, arrDuracion, numStream);

    return 0;
}
