/*
 *
 *  Hay un error de impresión con el primer canal, de ahí, todo chills
 *
 */
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
