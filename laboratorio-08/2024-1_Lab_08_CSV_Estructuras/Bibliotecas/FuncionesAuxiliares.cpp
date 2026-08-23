#include "FuncionesAuxiliares.h"
#define TAM_PAG 150
#define MAX_CAD 200
#define TAM_COD 12
#define TAM_NOM 40
#define TAM_DOUB 14
/*
 *  Módulos secundarios
 */
void abrirInput(ifstream& arch, const char* nombArch) {
    arch.open(nombArch, ios::in);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo " << nombArch << endl;
        exit(1);
    }
}

void abrirOutput(ofstream& arch, const char* nombArch) {
    arch.open(nombArch, ios::out);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo " << nombArch << endl;
        exit(1);
    }
    arch.precision(2);
    arch << fixed;
}

void imprimirLinea(ofstream& arch, char car) {
    arch << setfill(car) << setw(TAM_PAG) << "" << endl << setfill(' ');
}

int leerInt(ifstream& arch) {
    int dato;
    arch >> dato;
    arch.get();
    return dato;
}

void cambiarAEspacios(char *nomFacultad) {
    for (int i=0; nomFacultad[i]; i++) {
        if (nomFacultad[i]=='-')
            nomFacultad[i] = ' ';
    }
}


/*
 *  Módulos principales
 */
void leerCalificaciones(const char* nombArch, struct Alumno* arrAlumnos, int& numAlumnos) {
    ifstream arch;
    abrirInput(arch, nombArch);
    char curso[TAM_COD];
    double creditos;
    // DER614   5.75   20238549   16   20205830   17

    while (true) {
        arch >> curso;
        if (arch.eof()) break;
        arch >> creditos;
        leerDatosAlumnos(arch, creditos, arrAlumnos, numAlumnos);
    }
}

void leerDatosAlumnos(ifstream& arch, const double creditos, struct Alumno* arrAlumnos, int& numAlumnos) {
    int codAlumno, nota, pos;

    // 20238549   16   20205830   17
    while (true) {
        arch >> codAlumno >> nota;
        pos = buscarAlumno(codAlumno, arrAlumnos, numAlumnos);
        if (pos == -1) {
            arrAlumnos[numAlumnos].codigo = codAlumno;
            actualizarDatos(creditos, nota, arrAlumnos[numAlumnos]);
            numAlumnos++;
        }
        else {
            actualizarDatos(creditos, nota, arrAlumnos[pos]);
        }
        if (arch.get() == '\n') break;
    }
}

int buscarAlumno(const int codAlumno, const struct Alumno* arrAlumnos, const int numAlumnos) {
    for (int i = 0; i < numAlumnos; i++)
        if (codAlumno == arrAlumnos[i].codigo) return i;
    return -1;
}

void actualizarDatos(const double creditos, const int nota, struct Alumno& a) {
    a.sumaPonderada += creditos * nota;
    a.numCreditos += creditos;
    a.promPonderado = a.sumaPonderada/a.numCreditos;
    a.numCursos++;
}

void leerAlumnos(const char* nombArch, struct Alumno* arrAlumnos, const int numAlumnos) {
    ifstream arch;
    abrirInput(arch, nombArch);
    int codAlumno, pos;

    // 20227341,DIAZ ANTEZANO MAGALI SILVANA,EEGGCC
    while (true) {
        codAlumno = leerInt(arch);
        if (arch.eof()) break;
        pos = buscarAlumno(codAlumno, arrAlumnos, numAlumnos);
        if (pos != -1) {
            arch.getline(arrAlumnos[pos].nombre, TAM_NOM, ',');
            arch.getline(arrAlumnos[pos].facultad.codigo, TAM_COD, '\n');
        }
        else while (arch.get() != '\n');
    }
}

void leerFacultades(const char* nombArch, struct Alumno *arrAlumnos, const int numAlumnos) {
    ifstream arch;
    abrirInput(arch, nombArch);
    char codFacultad[TAM_COD], nomFacultad[TAM_NOM];
    // FACULTAD_DE_ARTE   FARTE
    while (true) {
        arch >> nomFacultad;
        cambiarAEspacios(nomFacultad);
        if (arch.eof()) break;
        arch >> codFacultad;
        for (int i=0; i<numAlumnos; i++) {
            if (strcmp(arrAlumnos[i].facultad.codigo, codFacultad) == 0)
                strcpy(arrAlumnos[i].facultad.nombre, nomFacultad);
        }
    }
}

void emitirReporte(const char* nombArch, const struct Alumno *arrAlumnos, const int numAlumnos) {
    ofstream arch;
    abrirOutput(arch, nombArch);
    imprimirEncabezado(arch);
    imprimirSubtitulos(arch);
    imprimirRegistrosDeAlumnos(arch, arrAlumnos, numAlumnos);
}

void imprimirEncabezado(ofstream& arch) {
    arch << setw(46) << "" << "INSTITUCION EDUCATIVA TP" << endl;
    arch << setw(35) << "" << "PROMEDIO PONDERADO DE LOS ALUMNOS MATRICULADOS" << endl;
    arch << setw(51) << "" << "CICLO: 2024-1" << endl;
    arch << setw(48) << "" << "TODAS LAS FACULTADES" << endl;
    imprimirLinea(arch, '=');
}

void imprimirSubtitulos(ofstream& arch) {
    arch << setw(6) << "" << "ALUMNO" << setw(32) << "" << "No. de Cursos   " << "Suma Ponderada  "
        << "No. de Creditos  " << "Prom Ponderado" << setw(4) << "" << "Facultad" <<endl;
    imprimirLinea(arch, '-');
}

void imprimirRegistrosDeAlumnos(ofstream& arch, const struct Alumno *arrAlumnos, const int numAlumnos) {

    struct Alumno alumnoMasCreditos{};

    for (int i=0; i<numAlumnos; i++) {
        arch << left << arrAlumnos[i].codigo << " - "
            << setw(TAM_NOM) << arrAlumnos[i].nombre
            << right << setw(2) << arrAlumnos[i].numCursos << setw(6) << ""
            << setw(TAM_DOUB) << arrAlumnos[i].sumaPonderada
            << setw(TAM_DOUB) << arrAlumnos[i].numCreditos
            << setw(TAM_DOUB) << arrAlumnos[i].promPonderado << setw(10) << ""
            << arrAlumnos[i].facultad.nombre;
        arch << endl;
        if (alumnoMasCreditos.numCreditos<arrAlumnos[i].numCreditos) {
            alumnoMasCreditos.numCreditos = arrAlumnos[i].numCreditos;
            strcpy(alumnoMasCreditos.nombre, arrAlumnos[i].nombre);
            alumnoMasCreditos.codigo = arrAlumnos[i].codigo;
            strcpy(alumnoMasCreditos.facultad.nombre, arrAlumnos[i].facultad.nombre);
        }
    }
    imprimirLinea(arch, '=');
    arch << "Alumno con mayor numero de creditos matriculados:" << endl;
    arch << setw(30) << "" << alumnoMasCreditos.nombre << '[' << alumnoMasCreditos.codigo << ']'
        << " con " << alumnoMasCreditos.numCreditos << " creditos de la "
        << alumnoMasCreditos.facultad.nombre << endl;
}
