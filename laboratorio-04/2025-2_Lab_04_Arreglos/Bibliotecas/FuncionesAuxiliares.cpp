#include "FuncionesAuxiliares.h"
#define TAM_PAG 140
#define TAM_FECHA 10
#define TAM_ESP 5
#define TAM_COD 12
#define TAM_RAT 12
/*------------------------------------------------------------------*/
// Funciones secundarias --------------------------------------------
/*------------------------------------------------------------------*/

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

int leerDuracion(ifstream& arch) {
    int mm, ss;
    char c;
    arch >> mm >> c >> ss;
    return mm * 60 + ss;
}

void imprimirDuracion(ofstream& arch, int duracion) {
    int hh, mm, ss;
    hh = duracion / 3600;
    mm = duracion / 60 % 60;
    ss = duracion % 60;

    arch << right << setfill('0');
    if (hh > 0) {
        if (hh>99) {
            arch << hh << ':';
        } else {
            arch << " " << setw(2) << hh << ":";
        }
    }
    arch << setw(2) << mm << ":" << setw(2) << ss
        << setfill(' ');
}

int leerFecha(ifstream& arch) {
    int dd, mm, aa;
    char c;
    arch >> dd >> c >> mm >> c >> aa;
    return aa * 10000 + mm * 100 + dd;
}

void imprimirFecha(ofstream& arch, int fecha) {
    int dd, mm, aa;
    aa = fecha / 10000;
    mm = fecha / 100 % 100;
    dd = fecha % 100;
    arch << right << setfill('0')
        << setw(2) << dd << '/' << setw(2) << mm << '/' << setw(4) << aa
        << setfill(' ');
}

void imprimirLinea(ofstream& arch, char car) {
    arch << setfill(car) << setw(TAM_PAG) << "" << endl
        << setfill(' ');
}

void suprimir(ifstream& arch, char car) {
    arch >> ws;
    while (arch.get() != car);
}

void imprimirContador(ofstream& arch, int contador) {
    arch << right << setfill(' ')
        << setw(3) << contador << ")   ";
}

/*------------------------------------------------------------------*/
// Funciones de inserción y ordenación de datos --------------------
/*------------------------------------------------------------------*/

void leerTarifa(double& tarifa) {
    cout << "INGRESE TARIFA:" << endl;
    cin >> tarifa;
}


void leerCanales(const char* nombArch,
                 int* arrFechaCanal, int* arrCodCanal, char* arrLetraCodCanal,
                 double* arrRatingCanal, int& numCanal) {
    ifstream arch;
    abrirInput(arch, nombArch);
    // 19/06/2022    X5514      xQcOW      2.5      632180
    while (true) {
        arrFechaCanal[numCanal] = leerFecha(arch);
        if (arch.eof()) break;
        arch >> ws >> arrLetraCodCanal[numCanal] >> arrCodCanal[numCanal];
        suprimir(arch, ' ');
        arch >> arrRatingCanal[numCanal];
        suprimir(arch, '\n');
        numCanal++;
    }
}

void leerEtiquetas(const char* nombArch,
                   int* arrCodEtiq, int* arrDuraEtiq, int& numEtiqueta) {
    ifstream arch;
    abrirInput(arch, nombArch);
    // 888106   fps   02:07
    while (true) {
        arch >> arrCodEtiq[numEtiqueta];
        if (arch.eof()) break;
        suprimir(arch, ' ');
        arrDuraEtiq[numEtiqueta] = leerDuracion(arch);
        numEtiqueta++;
    }
}

void verificarArrays(const char* nombArch,
                     int* arrFechaCanal, int* arrCodCanal, char* arrLetraCodCanal,
                     double* arrRatingCanal, int numCanal,
                     int* arrCodEtiq, int* arrDuraEtiq, int numEtiqueta) {
    ofstream arch;
    abrirOutput(arch, nombArch);

    arch << left << setw(TAM_ESP + TAM_FECHA) << "FECHA:"
        << setw(TAM_COD) << "CANAL:" << "RATING" << endl;
    for (int i = 0; i < numCanal; i++) {
        imprimirFecha(arch, arrFechaCanal[i]);
        arch << left << setw(TAM_ESP) << ""
            << arrLetraCodCanal[i] << setw(TAM_COD - 1) << arrCodCanal[i]
            << right << setw(TAM_RAT) << arrRatingCanal[i];
        arch << endl;
    }

    imprimirLinea(arch, '=');

    arch << left << setw(TAM_COD) << "ETIQUETA" << "DURACION" << endl;
    for (int i = 0; i < numEtiqueta; i++) {
        arch << left << setw(TAM_COD) << arrCodEtiq[i];
        imprimirDuracion(arch, arrDuraEtiq[i]);
        arch << endl;
    }
}

void leerReproduccionesYCompletarArraysAuxiliares(const char* nombArch,
                                                  char* arrLetraCodCanal, int* arrCodCanal, double* arrRatingCanal,
                                                  int numCanal,
                                                  int* arrCodEtiq, int* arrDuraEtiq, int numEtiqueta, double tarifa,
                                                  int* arrTotalReprodCanal, int* arrCantReprodCanal,
                                                  int* arrPorcentRating, double* arrIngresosCanal,
                                                  int* arrTotalReprodEtiq, int* arrCantReprodEtiq) {
    ifstream arch;
    abrirInput(arch, nombArch);
    int codCanal, codEtiq, cant;
    char letraCanal;
    int posCanal, posEtiqueta;
    // 22/12/2024      T1252      629118      408
    while (true) {
        arch >> ws;
        if (arch.eof()) break;
        suprimir(arch, ' ');
        arch >> ws >> letraCanal >> codCanal >> codEtiq >> cant;

        posEtiqueta = buscarEtiqueta(codEtiq, arrCodEtiq, numEtiqueta);
        if (posEtiqueta != -1) {
            completarArraysDeEtiquetas(arrTotalReprodEtiq[posEtiqueta], arrCantReprodEtiq[posEtiqueta],
                                       arrDuraEtiq[posEtiqueta], cant);
            posCanal = buscarCanal(letraCanal, codCanal, arrLetraCodCanal, arrCodCanal, numCanal);
            if (posCanal != -1) {
                completarArraysDeCanales(arrTotalReprodCanal[posCanal], arrCantReprodCanal[posCanal],
                                         arrPorcentRating[posCanal], arrIngresosCanal[posCanal],
                                          arrRatingCanal[posCanal],
                                         arrDuraEtiq[posEtiqueta],
                                         cant, tarifa);
            }
        }
    }
}

int buscarEtiqueta(int codEtiq, int* arrCodEtiq, int numEtiqueta) {
    for (int i = 0; i < numEtiqueta; i++)
        if (codEtiq == arrCodEtiq[i]) return i;
    return -1;
}

void completarArraysDeEtiquetas(int& totalReprodEtiq, int& cantReprod,
                                int duracion, int cant) {
    totalReprodEtiq += duracion * cant;
    cantReprod += cant;
}

int buscarCanal(char letraCanal, int codCanal, char* arrLetraCodCanal, int* arrCodCanal, int numCanal) {
    for (int i = 0; i < numCanal; i++)
        if (letraCanal == arrLetraCodCanal[i] and codCanal == arrCodCanal[i]) return i;
    return -1;
}

void completarArraysDeCanales(int& totalReprodCanal, int& cantReprodCanal, int& porcentRating, double& ingresosCanal,
                              double ratingCanal, int duracion, int cant, double tarifa) {
    totalReprodCanal += (duracion * cant);
    cantReprodCanal += cant;

    if (4.0 < ratingCanal and ratingCanal < 5.0)
        porcentRating = 30;
    else if (3.0 < ratingCanal and ratingCanal <= 4.0)
        porcentRating = 20;
    else if (2.0 < ratingCanal and ratingCanal <= 3.0)
        porcentRating = 0;
    else
        porcentRating = -25;
    ingresosCanal = (totalReprodCanal * tarifa * (100.0 + porcentRating) / 100.0) / 60.0;
}


void emitirReporte(const char* nombArch,
                   int* arrFechaCanal, int* arrCodCanal, char* arrLetraCodCanal,
                   double* arrRatingCanal,
                   int* arrTotalReprodCanal, int* arrCantReprodCanal,
                   int* arrPorcentRating, double* arrIngresosCanal, int numCanal,
                   int* arrCodEtiq, int* arrDuraEtiq, int* arrTotalReprodEtiq, int* arrCantReprodEtiq,
                   int numEtiqueta, double tarifa) {
    ofstream arch;
    abrirOutput(arch, nombArch);

    imprimirEncabezado(arch, tarifa);
    imprimirSubtitulos(arch, 'C');
    for (int i = 0; i < numCanal; i++) {
        imprimirContador(arch, i + 1);
        arch << left << arrLetraCodCanal[i] << setw(TAM_COD) << arrCodCanal[i];
        imprimirFecha(arch, arrFechaCanal[i]);
        arch << setw(TAM_ESP) << ""
            << right << setw(TAM_RAT) << arrRatingCanal[i]
            << setw(TAM_RAT+TAM_ESP) << arrCantReprodCanal[i]
            << setw(TAM_ESP*2) << "";
        imprimirDuracion(arch, arrTotalReprodCanal[i]);
        arch << right << setw(TAM_ESP) << ""
            << setw(TAM_RAT+TAM_ESP) << arrPorcentRating[i] << '%'
            << setw(TAM_ESP*4) << arrIngresosCanal[i];
        arch << endl;
    }

    imprimirSubtitulos(arch, 'E');
    for (int i = 0; i < numEtiqueta; i++) {
        imprimirContador(arch, i + 1);
        arch << left << setw(TAM_COD) << arrCodEtiq[i];
        imprimirDuracion(arch, arrDuraEtiq[i]);
        arch << right << setw(20) << arrCantReprodEtiq[i]
            << setw(TAM_ESP * 2) << "";
        imprimirDuracion(arch, arrTotalReprodEtiq[i]);
        arch << endl;
    }
}

void imprimirEncabezado(ofstream& arch, double tarifa) {
    arch << setw(56) << "" << "PLATAFORMA TP_Twitch" << endl
        << setw(32) << "" << "TARIFA POR DURACION DE LAS ETIQUETAS " << tarifa << " POR CADA MINUTO Y FRACCION" << endl;
}

void imprimirSubtitulos(ofstream& arch, char parametro) {
    imprimirLinea(arch, '=');
    arch << left;
    if (parametro == 'C') {
        arch << "CANALES ADSCRITOS A LA PLATAFORMA" << endl;
        imprimirLinea(arch, '-');
        arch << setw(39) << "" << "RATING DE" << setw(TAM_ESP+3) << ""
            << "NUMERO TOTAL" << setw(TAM_ESP+2) << ""
            << "TIEMPO TOTAL DE" << setw(TAM_ESP) << ""
            << "PORCENTAJE POR" << setw(TAM_ESP) << ""
            << "INGRESOS POR REPRODUCCION";
        arch << endl;
        arch << " No.  "
            << setw(TAM_COD) << "CODIGO"
            << "FECHA DE CREACION" << setw(TAM_ESP) << ""
            << "CALIDAD" << setw(TAM_ESP) << ""
            << "DE REPRODUCCIONES" << setw(TAM_ESP) << ""
            << "DE REPRODUCCIONES" << setw(TAM_ESP) << ""
            << "RATING DE CALIDAD" << setw(TAM_ESP) << ""
            << "DE ETIQUETAS";
        arch << endl;
    }
    else {
        arch << endl << "ETIQUETAS DE LA PLATAFORMA" << endl;
        imprimirLinea(arch, '-');
        arch << setw(32) << "" <<"CANTIDAD TOTAL" << setw(TAM_ESP) << ""
            << "TIEMPO TOTAL DE" << endl;
        arch << " No.  "
            << setw(TAM_COD) << "ETIQUETA"
            << "DURACION" << setw(TAM_ESP) << ""
            << "DE REPRODUCCIONES" << setw(TAM_ESP) << ""
            << "REPRODUCIDO";
        arch << endl;
    }
}
