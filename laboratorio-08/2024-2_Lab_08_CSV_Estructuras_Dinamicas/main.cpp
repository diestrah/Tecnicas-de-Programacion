#include "Bibliotecas/FuncionesAuxiliares.h"
#define MAX_CLIE 120
#define MAX_PLAT 120
#define MAX_DIST 50

int main() {
    struct Plato arrPlatos[MAX_PLAT]{};
    struct Cliente arrClientes[MAX_CLIE]{};
    struct Distrito arrDistritos[MAX_DIST]{};
    int numPlatos = 0, numClientes = 0, numDistritos = 0;

    leerPlatosOfrecidos("ArchivosDeDatos/lab8_PlatosOfrecidos.csv", arrPlatos, numPlatos);
    leerClientes("ArchivosDeDatos/lab8_Clientes.csv", arrClientes, numClientes);
    leerDistritos("ArchivosDeDatos/lab8_Distritos.csv", arrDistritos, numDistritos);
    verificarPlatosOfrecidos("ArchivosDeReportes/ReporteDePlatos.txt", arrPlatos, numPlatos);
    verificarClientes("ArchivosDeReportes/ReporteDeClientes.txt", arrClientes, numClientes);
    verificarDistritos("ArchivosDeReportes/ReporteDeDistritos.txt", arrDistritos, numDistritos);
    leerPedidosYCompletarArrays("ArchivosDeDatos/lab8_PedidosRealizados.txt", arrPlatos, numPlatos,
                                arrClientes, numClientes, arrDistritos, numDistritos);
    ordenarClientes(arrClientes, numClientes);
    ordenarPlatos(arrPlatos, numPlatos);
    emitirReporte("ArchivosDeReportes/PedidosAtendidos.txt", arrClientes, numClientes);
    return 0;
}
