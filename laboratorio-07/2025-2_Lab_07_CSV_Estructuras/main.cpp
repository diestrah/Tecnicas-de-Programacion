/*----------------------------------------------------------------------------------------*/
/*  Autor           :   Naim Diestra
/*  Fecha creación  :   10/12/2025
/*  Actualización   :   03/05/2026
/*  Descripción     :   Almacena en un array de estructuras datos de archivos Categorias.csv
/*                      y Reproducciones.csv. Conforme se vayan llenando los datos se emiten
/*                      reportes parciales hasta llegar al reporte final.
/*----------------------------------------------------------------------------------------*/

#include "Bibliotecas/FuncionesAuxiliares.h"

int main() {
    int numCategorias = 0;
    struct Categoria arrCategorias[MAX_CATE]{};

    leerCategorias("ArchivosDeDatos/Categorias.csv", arrCategorias, numCategorias);

    verificarCategorias("ArchivosDeReportes/ReporteDePruebaCategorias.txt", arrCategorias, numCategorias);

    leerReproducciones("ArchivosDeDatos/Reproducciones.csv", arrCategorias, numCategorias);

    verificarCategorias("ArchivosDeReportes/ReporteDePruebaConReproducciones.txt", arrCategorias, numCategorias);

    calcularPromediosYDuraciones(arrCategorias, numCategorias);

    verificarCategorias("ArchivosDeReportes/ReportePorCategorias.txt", arrCategorias, numCategorias);

    return 0;
}
