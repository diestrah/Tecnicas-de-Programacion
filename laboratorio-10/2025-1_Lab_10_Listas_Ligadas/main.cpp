/*---------------------------------------------------------------------------------------*/
/*  Fecha de creación   :   17/06/2026
/*  Autor               :   Naim Diestra
/*  Descripción del problema:
/*  Se leen los archivos "CuentasBancarias.csv" y "MovimientosDeCuentas.csv" y se llena
/*  la data en el Nodo* Lista. Se emite un reporte inicial de todas las cuentas y
/*  después se eliminan todas las cuentas cuyo saldo sea mayor a 0. Finalmente se emite
/*  un reporte final donde se muestran las cuentas a eliminar.
/*  La finalidad del laboratorio era reforzar el concepto de lista ligada y structs
/*  (una previa de Algoritmia)
/*---------------------------------------------------------------------------------------*/

#include "Bibliotecas/FuncionesAuxiliares.h"

int main() {
    Nodo* lista;

    leerCuentasBancarias("ArchivosDeDatos/CuentasBancarias.csv", lista);
    leerMovimientosDeCuentas("ArchivosDeDatos/MovimientosDeCuentas.csv", lista);
    emitirReporteCuentas("ArchivosDeReporte/ReporteDeSaldosDeLasCuentas.txt", lista);
    eliminarCuentasConSaldoPositivo(lista);
    emitirReporteCuentas("ArchivosDeReporte/ReporteDeCuentasQueSeCierran.txt", lista);

    return 0;
}
