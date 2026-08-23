/*----------------------------------------------------------------------------------------*/
/*  Elaborado por   :   Naim Diestra
/*  Fecha creación  :   26/01/2026
/*  Descripción     :   Se leen los datos de twitchdataTP.txt y se emite un reporte
/*                      que emitirá los datos de los canales cuya fecha de creación
/*                      se encuentre en el rango de fechas solicitado al usuario.
/*                      Además, cada canal contará con un resumen por sus reproducciones
/*                      y se emite un resumen de todos los canales.
/*----------------------------------------------------------------------------------------*/

#include "Bibliotecas/FuncionesAuxiliares.h"

int main() {
    int fechaIni, fechaFin;
    double tarifaReprod, tarifaDura;

    solicitarFechas(fechaIni, fechaFin, tarifaReprod, tarifaDura);

    leerEImprimirReporte("ArchivosDeDatos/twitchdataTP.txt", "ArchivosDeReportes/Reporte.txt",
                         fechaIni, fechaFin, tarifaReprod, tarifaDura);

    return 0;
}
