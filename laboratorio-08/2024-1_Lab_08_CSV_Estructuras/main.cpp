#include "Bibliotecas/FuncionesAuxiliares.h"
#define MAX_ALUM 100

int main() {
    struct Alumno arrAlumnos[MAX_ALUM]{};
    int numAlumnos = 0;

    leerCalificaciones("ArchivosDeDatos/Calificaciones_laboratorio8.txt",
                       arrAlumnos, numAlumnos);
    leerAlumnos("ArchivosDeDatos/Alumnos_laboratorio8.csv", arrAlumnos, numAlumnos);
    leerFacultades("ArchivosDeDatos/Facultades_laboratorio8.txt", arrAlumnos, numAlumnos);
    emitirReporte("ArchivosDeReportes/ReporteDePagoPorAlumno.txt", arrAlumnos, numAlumnos);
    return 0;
}
