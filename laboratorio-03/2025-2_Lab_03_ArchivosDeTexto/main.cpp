/*----------------------------------------------------------------------------------------*/
/*  Elaborado por       :  Naim Diestra
/*  Fecha creación      :  17/01/2026 
/*  Fecha actualización :  18/01/2026
/*  Nota: Hay un error de impresión del primer canal, de ahí, todo ok
/*----------------------------------------------------------------------------------------*/

#include "Bibliotecas/FuncionesAuxiliares.h"

int main() {
    double tarifa;
    leerTarifa(tarifa);

    leerDatosYEmitirReporte("ArchivosDeDatos/Canales.txt",
                            "ArchivosDeDatos/Etiquetas.txt",
                            "ArchivosDeDatos/ReproduccionesDeEtiquetas.txt",
                            "ArchivosDeReportes/Reporte.txt", tarifa);

    return 0;
}
