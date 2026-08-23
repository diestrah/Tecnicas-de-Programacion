#include "FuncionesAuxiliares.h"

/*------------------------------------------------------------------*/
// Funciones secundarias --------------------------------------------
/*------------------------------------------------------------------*/

// Apertura de archivos
ifstream abrirInput(const char* nombArch) {
    ifstream arch(nombArch, ios::in);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo " << nombArch << endl;
        exit(1);
    }
    return arch;
}

ofstream abrirOutput(const char* nombArch) {
    ofstream arch(nombArch, ios::out);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo " << nombArch << endl;
        exit(1);
    }
    arch.precision(2);
    arch << fixed;
    return arch;
}

// Lectura de datos
int leerDuracion(ifstream& arch) {
    int hh, mm, ss;
    char c;
    arch >> hh >> c >> mm >> c >> ss;
    return hh * 3600 + mm * 60 + ss;
}

int leerFecha(ifstream& arch) {
    int dd, mm, aa;
    char c;
    arch >> dd >> c >> mm >> c >> aa;
    return aa * 10000 + mm * 100 + dd;
}

char* leerCadena(ifstream& arch) {
    char buffer[MAX_CAD]{}, *cadena;
    arch >> buffer;
    if (arch.eof()) return nullptr;
    cadena = new char[strlen(buffer) + 1]{};
    strcpy(cadena, buffer);
    return cadena;
}

// Impresión de datos
void imprimirDuracion(ofstream& arch, int duracion) {
    int hh, mm, ss;
    hh = duracion / 3600;
    mm = duracion / 60 % 60;
    ss = duracion % 60;
    arch << right << setfill('0')
        << setw(2) << hh << ":" << setw(2) << mm << ":" << setw(2) << ss
        << setfill(' ');
}

void imprimirLinea(ofstream& arch, char car) {
    arch << setfill(car) << setw(TAM_PAG) << "" << endl
        << setfill(' ');
}

void imprimirFecha(ofstream& arch, int fecha) {
    int dd, mm, aa;
    aa = fecha / 10000;
    mm = fecha / 100 % 100;
    dd = fecha % 100;
    arch << right << setfill('0')
        << setw(2) << dd << '/' << setw(2) << mm << '/' << aa
        << setfill(' ');
}

/*------------------------------------------------------------------*/
// Funciones principales --------------------------------------------
/*------------------------------------------------------------------*/

// Parte 2: generar archvo
void generaArchivoEnlace(const char* categoria, char*& nombArch, char*& enlace) {
    char cadena[MAX_CAD], link[MAX_CAD];

    strcpy(cadena, "ArchivosDeReportes/");
    strcat(cadena, categoria);

    strcpy(link, "https://Laboratorio06_2025_2/");
    strcat(link, cadena);

    enlace = new char[strlen(link) + 1];
    strcpy(enlace, link);

    strcat(cadena, ".txt");
    nombArch = new char[strlen(cadena) + 1];
    strcpy(nombArch, cadena);
}


// Parte 3: leer Categorias.txt
void leerCategorias(const char* nombArch, char** arrCodCate, char** arrNomCate, int& numCate) {
    ifstream arch = abrirInput(nombArch);
    // DN124W94    league_of_legends
    while (true) {
        arrCodCate[numCate] = leerCadena(arch);
        if (arch.eof()) break;
        arrNomCate[numCate] = leerCadena(arch);
        numCate++;
    }
}

// Parte 4: verificar Categorias.txt
void verificarCategorias(const char* nombArch, char** arrCodCate, char** arrNomCate, int numCate) {
    ofstream arch = abrirOutput(nombArch);
    // Encabezado
    arch << left << "REPORTE CATEGORIAS" << endl
        << setw(TAM_COD) << "CODIGO" << setw(TAM_NOM) << "NOMBRE CATEGORIA" << endl;
    // Impresión de datos
    for (int i = 0; i < numCate; i++) {
        arch << left << setw(TAM_COD) << arrCodCate[i]
            << setw(TAM_NOM) << arrNomCate[i] << endl;
    }
}

// Parte 5: leer StreamsReproducidos.txt
void leerReproducciones(const char* nombArch, int* arrFecha,
                        char** arrNomCanal, char** arrCodCateCanal, double* arrRating,
                        double* arrDropOff, int* arrDuracion, int& numStream) {
    ifstream arch = abrirInput(nombArch);
    // 1/11/2025  LCK  SJ181Q95    4.666    0.448    1:48:17
    while (true) {
        arrFecha[numStream] = leerFecha(arch);
        if (arch.eof()) break;
        arrNomCanal[numStream] = leerCadena(arch);
        arrCodCateCanal[numStream] = leerCadena(arch);
        arch >> arrRating[numStream] >> arrDropOff[numStream];
        arrDuracion[numStream] = leerDuracion(arch);
        numStream++;
    }
}

// Parte 6: verificar StreamsReproducidos.txt
void verificarReproducciones(const char* nombArch, int* arrFecha,
                             char** arrNomCanal, char** arrCodCateCanal, double* arrRating,
                             double* arrDropOff, int* arrDuracion, int numStream) {
    ofstream arch = abrirOutput(nombArch);
    // Encabezado
    arch << "REPORTE REPRODUCCIONES" << endl
        << left << setw(16) << "FECHA" << setw(TAM_NOM) << "NOMBRE" << setw(TAM_COD) << "CODIGO"
        << right << setw(TAM_FLO) << "RATING" << setw(TAM_FLO) << "DROP OFF" << "      DURACION" << endl;
    // Impresión de datos
    for (int i = 0; i < numStream; i++) {
        imprimirFecha(arch, arrFecha[i]);
        arch << left << setw(6) << "" << setw(TAM_NOM) << arrNomCanal[i]
            << setw(TAM_COD) << arrCodCateCanal[i]
            << right << setw(TAM_FLO) << arrRating[i]
            << setw(TAM_FLO) << arrDropOff[i] << setw(6) << "";
        imprimirDuracion(arch, arrDuracion[i]);
        arch << endl;
    }
}

// Parte 7: emitir todos los reportes
void emitirReportes(char** arrCodCate, char** arrNomCate, int numCate,
                    int* arrFecha, char** arrNomCanal, char** arrCodCateCanal, double* arrRating,
                    double* arrDropOff, int* arrDuracion, int numStream) {
    char *nombArch, *enlace;
    // Se imprime un reporte por cada categoría que existe.
    for (int i = 0; i < numCate; i++) {
        generaArchivoEnlace(arrNomCate[i], nombArch, enlace);
        ofstream arch = abrirOutput(nombArch);
        imprimirEncabezado(arch, arrCodCate[i], arrNomCate[i], enlace);
        imprimirReproducciones(arch, arrCodCate[i], arrFecha, arrNomCanal, arrCodCateCanal,
                               arrRating, arrDropOff, arrDuracion, numStream);
    }
}

void imprimirEncabezado(ofstream& arch, char* codigo, char* nombre, char* enlace) {
    arch << "Codigo: " << codigo << endl
        << "Nombre: " << nombre << endl
        << "Enlace: " << enlace << endl;
}

void imprimirReproducciones(ofstream& arch, char* codigo, int* arrFecha,
                            char** arrNomCanal, char** arrCodCateCanal, double* arrRating,
                            double* arrDropOff, int* arrDuracion, int numStream) {
    double promRating = 0.0, promDropOff = 0.0;
    int duracionTotal = 0, cant = 0;

    imprimirSubtituloReproducciones(arch);
    // Impresión de datos
    for (int i = 0; i < numStream; i++) {
        if (strcmp(codigo, arrCodCateCanal[i]) == 0) {
            imprimirFecha(arch, arrFecha[i]);
            arch << left << setw(6) << "" << setw(TAM_NOM) << arrNomCanal[i]
                << right << setw(TAM_FLO) << arrRating[i]
                << setw(TAM_FLO) << arrDropOff[i] << setw(6) << "";
                // este último setw(6) imprime espacios en blanco para luego imprimir la duración (por formato)
            imprimirDuracion(arch, arrDuracion[i]);
            arch << endl;

            duracionTotal += arrDuracion[i];
            promDropOff += arrDropOff[i];
            promRating += arrRating[i];
            cant++;
        }
    }

    imprimirResumen(arch, promRating, promDropOff, duracionTotal, cant);
}

void imprimirSubtituloReproducciones(ofstream& arch) {
    arch << "REPRODUCCIONES:" << endl;
    imprimirLinea(arch, '=');
    arch << left << setw(16) << "FECHA" << setw(TAM_NOM) << "CANAL"
        << right << setw(TAM_FLO) << "RATING"
        << setw(TAM_FLO) << "DROP OFF" << "      DURACION" << endl;
}

void imprimirResumen(ofstream& arch, double promRating, double promDropOff, int duracionTotal, int cant) {
    if (cant != 0) {
        promRating /= cant;
        promDropOff /= cant;
        imprimirLinea(arch, '=');
        arch << "PROMEDIO DE RATING  :" << right << setw(TAM_FLO) << promRating << endl
            << "PROMEDIO DE DROP-OFF:" << right << setw(TAM_FLO) << promDropOff << endl
            << "DURACION TOTAL:" << setw(10) << "";
        imprimirDuracion(arch, duracionTotal);
    }
    else {
        arch << "SIN REPRODUCCIONES" << endl; // por si acaso
    }
}
