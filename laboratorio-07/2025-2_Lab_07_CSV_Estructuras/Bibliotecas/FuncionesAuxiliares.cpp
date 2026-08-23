#include "FuncionesAuxiliares.h"
#include "Categoria.h"
#define TAM_PAG 60

/*------------------------------------------------------------------*/
// Funciones Secundarias --------------------------------------------
/*------------------------------------------------------------------*/
// Apertuura de archivos
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
int leerInt(ifstream& arch) {
    int dato;
    arch >> dato;
    arch.get();
    return dato;
}

double leerDouble(ifstream& arch) {
    double dato;
    arch >> dato;
    arch.get();
    return dato;
}

int leerDuracion(ifstream& arch) {
    int hh, mm, ss;
    hh = leerInt(arch);
    mm = leerInt(arch);
    ss = leerInt(arch);
    return hh * 3600 + mm * 60 + ss;
}

// Impresión
void imprimirDuracion(ofstream& arch, int duracion) {
    int hh, mm, ss;
    hh = duracion / 3600;
    mm = duracion / 60 % 60;
    ss = duracion % 60;
    arch << right << setfill('0')
        << setw(2) << hh << ':' << setw(2) << mm << ':' << setw(2) << ss
        << setfill(' ');
}

void imprimirLinea(ofstream& arch, char car) {
    arch << setfill(car) << setw(TAM_PAG) << "" << endl
        << setfill(' ');
}

/*------------------------------------------------------------------*/
// Funciones de Inserción y Lectura ---------------------------------
/*------------------------------------------------------------------*/
// Función 1: leer Categorias.csv
void leerCategorias(const char* nombArch, struct Categoria* arrCategorias, int& numCategorias) {
    ifstream arch = abrirInput(nombArch);
    struct Categoria c{}; // Aquí almacenamos toda la data y no creamos más variables
    // TM145B57,eternal return
    while (true) {
        arch.getline(c.codigo, TAM_COD, ',');
        if (arch.eof()) break;
        arch.getline(c.nombre, TAM_NOM_CAT, '\n');
        arrCategorias[numCategorias] = c;
        numCategorias++;
    }
}

// Función 2: leer Reproducciones.csv
void leerReproducciones(const char* nombArch, struct Categoria* arrCategorias, int numCategorias) {
    ifstream arch = abrirInput(nombArch);
    char codigo[TAM_COD];
    int pos;
    struct Reproduccion r{}; // Aquí almacenamos toda la data. Así no creamos más variables
    // Gaules,EW188U26,3.485,01:49:26
    while (true) {
        arch.getline(r.canal, TAM_NOM_CAN, ',');
        if (arch.eof()) break;
        arch.getline(codigo, TAM_COD, ',');
        r.rating = leerDouble(arch);
        r.duracion = leerDuracion(arch);

        pos = buscarCategoria(arrCategorias, codigo, numCategorias);
        if (pos != -1) {
            insertarReproduccion(arrCategorias[pos], r);
        }
    }
}

int buscarCategoria(struct Categoria* arrCategorias, char* codigo, int numCategorias) {
    for (int i = 0; i < numCategorias; i++)
        if (strcmp(codigo, arrCategorias[i].codigo) == 0) return i;
    return -1;
}

void insertarReproduccion(struct Categoria& c, struct Reproduccion r) {
    int numReprod = c.numReproducciones;
    c.reproducciones[numReprod] = r;
    c.numReproducciones++;
}

// Función 3: calcular promedios
void calcularPromediosYDuraciones(struct Categoria* arrCategorias, int numCategorias) {
    for (int i = 0; i < numCategorias; i++) {
        acumularRatingYDuracion(arrCategorias[i]);
        arrCategorias[i].promedioRating /= arrCategorias[i].numReproducciones;
    }
}

void acumularRatingYDuracion(struct Categoria& c) {
    struct Reproduccion r{};
    for (int i = 0; i < c.numReproducciones; i++) {
        r = c.reproducciones[i];
        c.duracionTotal += r.duracion;
        c.promedioRating += r.rating;
    }
}


// Función 4: reporte
void verificarCategorias(const char* nombArch, const struct Categoria* arrCategorias, int numCategorias) {
    // esta función se adapta a los 3 casos mencionados en el enunciado
    ofstream arch = abrirOutput(nombArch);
    struct Categoria c;
    // Encabezado
    arch << setw(20) << "" << "REPORTE POR CATEGORIAS" << endl;
    // Impresión de data
    for (int i = 0; i < numCategorias; i++) {
        c = arrCategorias[i];
        arch << "Codigo: " << c.codigo << endl
            << "Nombre: " << c.nombre << endl;
        if (c.numReproducciones > 0) {
            imprimirReproducciones(arch, c);
        }
        if (c.promedioRating > 0) {
            imprimirRatingYDuracion(arch, c);
        }
        imprimirLinea(arch, '=');
    }
}

void imprimirReproducciones(ofstream& arch, const struct Categoria& c) {
    struct Reproduccion r{};
    imprimirLinea(arch, '-');
    // Encabezado
    arch << left << "REPRODUCCIONES" << endl
        << setw(TAM_NOM_CAN) << "CANAL" << setw(20) << "RATING" << "DURACION" << endl;
    // Impresión de data
    for (int i = 0; i < c.numReproducciones; i++) {
        r = c.reproducciones[i];
        arch << left << setw(TAM_NOM_CAN) << r.canal
            << right << setw(6) << r.rating << setw(14) << "";
        imprimirDuracion(arch, r.duracion);
        arch << endl;
    }
}

void imprimirRatingYDuracion(ofstream& arch, const struct Categoria& c) {
    imprimirLinea(arch, '-');
    arch << right << "RATING PROMEDIO: " << setw(8) << c.promedioRating << endl
        << "DURACION TOTAL:     ";
    imprimirDuracion(arch, c.duracionTotal);
    arch << endl;
}
