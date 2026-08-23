/*------------------------------------------------------------------------------------------*/
/*  Autor       	:   Naim Diestra
/*  Fecha creación  :   10/12/2025
/*  Actualización   :   03/05/2026
/*  Descripción     :   En un array de struct Categoria se almacenan los datos de los archivos
/*                      Categorias.csv (1) y StreamsReproducidos.csv (2), luego se ordena
/*                      alfabéticamente por el nombre de Categoria (3) y al final se almacenan
/*                      los datos de ComentariosAlCanal.csv (4). Por cada procedimiento
/*                      (el cual se encuentra enumerado con paréntesis) se emite un reporte.
/*------------------------------------------------------------------------------------------*/

#include "Bibliotecas/FuncionesAuxiliares.h"
#define MAX_CATE 150

int main() {
    int numCate = 0;
    struct Categoria arrCategorias[MAX_CATE];

    leerCategorias("ArchivosDeDatos/Categorias.csv", arrCategorias, numCate);
    verificarCategorias("ArchivosDeReportes/ReporteDePruebaCategorias.txt", arrCategorias, numCate);

    leerStreams("ArchivosDeDatos/StreamsReproducidos.csv", arrCategorias, numCate);
    verificarCategorias("ArchivosDeReportes/ReporteDePruebaConReproducciones.txt", arrCategorias, numCate);

    ordenarArray(arrCategorias, numCate);
    verificarCategorias("ArchivosDeReportes/ReporteDePruebaOrdenado.txt", arrCategorias, numCate);

    leerComentarios("ArchivosDeDatos/ComentariosAlCanal.csv", arrCategorias, numCate);
    verificarCategorias("ArchivosDeReportes/ReporteDePruebaConComentarios.txt", arrCategorias, numCate);

    return 0;
}
