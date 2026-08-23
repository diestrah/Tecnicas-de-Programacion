#include "FuncionesAuxiliares.h"
#define TAM_PAG 130
#define TAM_NOM 20
#define TAM_ETIQ 22

// Funciones Secundarias
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
    arch << setfill(car) << setw(TAM_PAG) << "" << endl
        << setfill(' ');
}

int leerFecha(ifstream& arch) {
    int dd, mm, aa;
    char c;
    arch >> dd >> c >> mm >> c >> aa;
    return dd + mm * 100 + aa * 10000;
}

void imprimirFecha(ofstream& arch, int fecha) {
    int dd, mm, aa;
    dd = fecha % 100;
    mm = fecha / 100 % 100;
    aa = fecha / 10000;
    arch << right << setfill('0')
        << setw(2) << dd << '/' << setw(2) << mm << '/' << aa
        << setfill(' ');
}

int leerDuracion(ifstream& arch) {
    int mm, ss;
    char c;
    arch >> mm >> c >> ss;
    return mm * 60 + ss;
}

void imprimirDuracion(ofstream& arch, int duracion, bool hora) {
    int hh, mm, ss;
    hh = duracion / 3600;
    mm = (duracion % 3600) / 60;
    ss = duracion % 60;

    arch << right << setfill('0');
    if (hora) {
        arch << setw(2) << hh << ':';
    }
    arch << right << setw(2) << mm << ':' << setw(2) << ss
        << setfill(' ');
}

void imprimirNombre(ifstream& archIn, ofstream& archOut, int numBlancos, bool mayus) {
    int numCar = 0;
    char c;
    archIn >> ws;

    while (true) {
        archIn.get(c);
        if (c == ' ') break;
        if ('a' <= c and c <= 'z' and mayus) c += 'A' - 'a';
        archOut.put(c);
        numCar++;
    }

    numBlancos -= numCar;
    archOut << setw(numBlancos) << "";
}

void imprimirContador(ofstream& archRepo, int contadorEtiq) {
    archRepo << right << setfill('0') << "  " << setw(2) << contadorEtiq << ")  "
        << setfill(' ');
}

// Funciones principales:
void leerTarifa(double& tarifa) {
    cout << "Ingrese una tarifa: ";
    cin >> tarifa;
}

void leerDatosYEmitirReporte(const char* nombArchCana,
                             const char* nombArchEtiq,
                             const char* nombArchRepro,
                             const char* nombArchRepo,
                             double tarifa) {
    ifstream archCana, archEtiq, archRepro;
    ofstream archRepo;
    abrirInput(archCana, nombArchCana);
    abrirInput(archEtiq, nombArchEtiq);
    abrirInput(archRepro, nombArchRepro);
    abrirOutput(archRepo, nombArchRepo);

    imprimirEncabezado(archRepo, tarifa);
    imprimirCanales(archCana, archRepro, archEtiq, archRepo, tarifa);
}

void imprimirEncabezado(ofstream& archRepo, double tarifa) {
    archRepo << setw(56) << "" << "PLATAFORMA TP_Twitch" << endl;
    archRepo << setw(34) << "" << "TARIFA POR DURACION DE LAS ETIQUETAS: " << tarifa
        << " POR CADA MINUTO Y FRACCION" << endl;
    imprimirLinea(archRepo, '=');
}

void imprimirCanales(ifstream& archCana, ifstream& archRepro, ifstream& archEtiq,
                     ofstream& archRepo, double tarifa) {
    int fecha, codigo, contadorCanal = 1;
    char letra;
    double rating;

    // 19/06/2022    X5514      xQcOW      2.5      632180
    while (true) {
        fecha = leerFecha(archCana);
        if (archCana.eof()) break;

        imprimirSubtitulosCanales(archRepo, contadorCanal);
        archCana >> ws >> letra >> codigo;
        archRepo << setw(6) << "";
        imprimirNombre(archCana, archRepo, TAM_NOM, true);
        archCana >> rating;

        while (archCana.get() != '\n');

        imprimirDatosCanales(archRepo, letra, codigo, fecha, rating);
        imprimirReproducciones(archRepro, archEtiq, archRepo, tarifa, letra, codigo, rating);
        contadorCanal++;
    }
}

void imprimirSubtitulosCanales(ofstream& arch, int contadorCanal) {
    arch << "CANAL No. " << contadorCanal << endl;
    arch << left << setw(6) << "" << setw(TAM_NOM) << "NOMBRE" << setw(12) << "CODIGO"
        << setw(14) << "CREADO EL" << "RATING DE CALIDAD" << endl;
}

void imprimirDatosCanales(ofstream& archRepo, char letra, int codigo, int fecha, double rating) {
    archRepo << left << letra << setw(11) << codigo;
    imprimirFecha(archRepo, fecha);
    archRepo << setw(6) << "" << setw(8) << rating << endl;
    imprimirLinea(archRepo, '-');
}

void imprimirReproducciones(ifstream& archRepro, ifstream& archEtiq, ofstream& archRepo,
                            double tarifa, char letra, int codigo, double rating) {
    int fecha, codEtiqueta, reproducciones, codCanal, contadorEtiq = 1, duracionTotal = 0;
    char letraCanal;

    imprimirSubtitulosReproducciones(archRepo);

    // 28/02/2025  E6696      888106      244
    archRepro.clear();
    archRepro.seekg(0, ios::beg);
    while (true) {
        fecha = leerFecha(archRepro);

        if (archRepro.eof()) break;
        archRepro >> ws >> letraCanal >> codCanal >> codEtiqueta >> reproducciones;

        if (letraCanal == letra and codCanal == codigo) {
            imprimirDatosReproducciones(archEtiq, archRepo, contadorEtiq, fecha, codEtiqueta, reproducciones,
                                        duracionTotal);
            contadorEtiq++;
        }
    }
    imprimirResumenReproducciones(archRepo, duracionTotal, rating, tarifa);
}

void imprimirSubtitulosReproducciones(ofstream& archRepo) {
    archRepo << "ETIQUETAS REPRODUCIDAS:" << endl;
    archRepo << left << setw(7) << "  No." << setw(16) << "FECHA" << setw(14) << "ETIQUETA"
        << setw(TAM_ETIQ - 1) << "REPRODUCCION" << setw(10) << "DURACION"
        << "CANTIDAD DE REPRODUCCIONES   " << "TIEMPO TOTAL REPRODUCIDO" << endl;
}

void imprimirDatosReproducciones(ifstream& archEtiq, ofstream& archRepo, int contadorEtiq,
                                 int fecha, int codEtiqueta, int reproducciones, int& duracionTotal) {
    int duracion, duracionEtiquetas;

    imprimirContador(archRepo, contadorEtiq);
    imprimirFecha(archRepo, fecha);
    archRepo << setw(12) << codEtiqueta << setw(8) << "";
    imprimirEtiquetas(archEtiq, archRepo, codEtiqueta, duracion);
    duracionEtiquetas = duracion * reproducciones;
    archRepo << right << setw(18) << reproducciones << setw(22) << "";
    imprimirDuracion(archRepo, duracionEtiquetas, true);
    archRepo << endl;
    duracionTotal += duracionEtiquetas;
}


void imprimirEtiquetas(ifstream& archEtiq, ofstream& archRepo, int codEtiqueta, int& duracion) {
    int codigo;

    archEtiq.clear();
    archEtiq.seekg(0, ios::beg);
    // 803100    dropsenabled   01:27
    while (true) {
        archEtiq >> codigo;
        if (archEtiq.eof()) break;
        archEtiq >> ws;

        if (codigo == codEtiqueta) {
            imprimirNombre(archEtiq, archRepo, TAM_ETIQ, false);
            duracion = leerDuracion(archEtiq);
            imprimirDuracion(archRepo, duracion, false);
            break;
        }

        while (archEtiq.get() != '\n');
    }
}

void imprimirResumenReproducciones(ofstream& archRepo, int duracionTotal, double rating, double tarifa) {
    int porcentaje;
    double ingresos;

    imprimirLinea(archRepo, '-');
    archRepo << left << setw(48) << "TIEMPO TOTAL DE REPRODUCCIONES DE ETIQUETAS:";
    imprimirDuracion(archRepo, duracionTotal, true);

    archRepo << endl << left << setw(48) << "PORCENTAJE POR RATING DE CALIDAD";
    imprimirRating(archRepo, rating, porcentaje);

    ingresos = rating * tarifa *  ((100 + porcentaje) / 100.0);
    archRepo << left << setw(48) << "INGRESOS POR REPRODUCCION DE ETIQUETAS:"
        << right << setw(8) << ingresos << endl;
    imprimirLinea(archRepo, '=');
}

void imprimirRating(ofstream& archRepo, double rating, int& porcentaje) {
    if (4.0 <= rating and rating < 5.0) {
        porcentaje = 30;
    }
    else if (3.0 <= rating) {
        porcentaje = 20;
    }
    else if (2.0 <= rating) {
        porcentaje = 0;
    }
    else if (1.0 <= rating) {
        porcentaje = -25;
    }

    if (porcentaje > 0) {
        archRepo << right << setw(5) << '+' << porcentaje;
    }
    else {
        archRepo << right << setw(7) << porcentaje;
    }
    archRepo << '%' << endl;
}
