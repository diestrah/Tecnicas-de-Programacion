/*
 *  Nombre  :   Naim Diestra
 *  Fecha   :   04/07/2026
 *
 *  Descripción:
 *  Este programa procesa la información usando una lista ligada ordenada ascendentemente por código de
 *  categoría. Primero lee las categorías desde "Categorias.csv" y genera un reporte de prueba.
 *  Luego lee las reproducciones desde "StreamsReproducidos.csv", actualiza la duración total,
 *  la duración máxima, el canal con mayor duración y los drop-off de cada categoría.
 *  Después calcula el promedio de drop-off,
 *  emite el reporte completo, elimina las categorías con promedio de drop-off menor a 3.5
 *  y finalmente genera un reporte con la lista resultante (utiliza la misma función de impresión).
 */
#include "Bibliotecas/FuncionesAuxiliares.h"

int main() {
    Nodo * lista;
    leerCategorias("ArchivosDeDatos/Categorias.csv", lista);
    emitirReporte("ArchivosDeReporte/ReporteDePruebaDeCategorias.txt", lista);
    leerStreams("ArchivosDeDatos/StreamsReproducidos.csv", lista);
    calcularDropOff(lista);
    emitirReporte("ArchivosDeReporte/ReporteDeCategoriasCompleto.txt", lista);
    eliminarMenoresDropOff(lista);
    emitirReporte("ArchivosDeReporte/ReporteDeCategoriasEliminados.txt", lista);
    return 0;
}