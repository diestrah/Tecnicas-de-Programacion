/*----------------------------------------------------------------------------------------*/
/*  Autor           :   Naim Diestra
/*  Fecha creación  :   26/01/2026 
/*----------------------------------------------------------------------------------------*/

#include "Bibliotecas/FuncionesAuxiliares.h"
#define MAX_CLIE 100
#define MAX_LIBR 300

int main() {
    struct Cliente arrClientes[MAX_CLIE];
    struct Libro arrLibros[MAX_LIBR];
    int numClientes = 0, numLibros = 0;

    leerClientes("ArchivosDeDatos/Clientes_laboratorio9.csv", arrClientes, numClientes);
    leerLibros("ArchivosDeDatos/Libros_laboratorio9.csv", arrLibros, numLibros);
    leerVentas("ArchivosDeDatos/Ventas_laboratorio9.csv", arrLibros, numLibros);
    determinarRankings(arrLibros, numLibros);
    ordenarLibrosPorRankingYTitulo(arrLibros, numLibros);
    emitirReporte("ArchivosDeReportes/ReporteDePagoPorAlumno.txt", arrClientes, numClientes,
        arrLibros, numLibros);

    return 0;
}
