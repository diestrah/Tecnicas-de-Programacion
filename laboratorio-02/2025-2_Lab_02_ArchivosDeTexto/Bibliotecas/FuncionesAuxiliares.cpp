#include "FuncionesAuxiliares.h"
#define TAM_PAG 150
#define TAM_RESUMEN_CAN 38
#define TAM_RESUMEN_FIN 38

// Abrir archivos
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

// Funciones secundarias
int leerFecha(ifstream& arch) {
    int dd, mm, aa;
    char c;
    arch >> dd >> c >> mm >> c >> aa;
    return aa * 10000 + mm * 100 + dd;
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
    int hh, mm, ss;
    char c;
    arch >> hh >> c >> mm >> c >> ss;
    return hh * 3600 + mm * 60 + ss;
}

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

void imprimirNombre(ifstream& archDat, ofstream& archRep) {
    int numBlancos, numCar = 0;
    char c;
    archDat >> ws;
    archRep << setw(6) << "";
    while (true) {
        archDat.get(c);
        if (c == ' ') break;
        if ('a' <= c and c <= 'z') c += 'A' - 'a';
        archRep.put(c);
        numCar++;
    }
    numBlancos = 30 - numCar;
    archRep << setfill(' ') << setw(numBlancos) << "";
}

// Funciones principales

void solicitarFechas(int& fechaIni, int& fechaFin, double& tarifaReprod, double& tarifaDura) {
    int dd, mm, aa;
    cout << "INGRESE FECHA INICIAL: " << endl;
    cin >> dd >> mm >> aa;
    fechaIni = aa * 10000 + mm * 100 + dd;
    cout << "INGRESE FECHA FINAL: " << endl;
    cin >> dd >> mm >> aa;
    fechaFin = aa * 10000 + mm * 100 + dd;
    cout << "INGRESE TARIFA DE REPRODUCCIONES: " << endl;
    cin >> tarifaReprod;
    cout << "INGRESE TARIFA POR DURACION" << endl;
    cin >> tarifaDura;
}

void leerEImprimirReporte(const char* nombArchDat, const char* nombArchRep,
                          int fechaIni, int fechaFin, double tarifaReprod, double tarifaDura) {
    ifstream archDat;
    ofstream archRep;
    abrirInput(archDat, nombArchDat);
    abrirOutput(archRep, nombArchRep);

    int duraFinal = 0, cantFinal = 0;
    double ingresoDuraFinal = 0.0, ingresoRepFinal = 0.0;

    imprimirEncabezado(archRep, fechaIni, fechaFin, tarifaReprod, tarifaDura);
    imprimirDatos(archDat, archRep, cantFinal, duraFinal, ingresoDuraFinal, ingresoRepFinal,
                  fechaIni, fechaFin, tarifaReprod, tarifaDura);
    imprimirResumenFinal(archRep, cantFinal, duraFinal, ingresoDuraFinal, ingresoRepFinal);
}

void imprimirEncabezado(ofstream& archRep, int fechaIni, int fechaFin, double tarifaReprod, double tarifaDura) {
    archRep << setw(71) << "" << "PLATAFORMA TP_Twitch" << endl
        << setw(64) << "" << "REGISTRO DE LOS CANALES AFILIADOS" << endl
        << setw(53) << "" << "FECHAS DE CREACION ENTRE EL ";
    imprimirFecha(archRep, fechaIni);
    archRep << " Y EL ";
    imprimirFecha(archRep, fechaFin);
    archRep << endl
        << setw(38) << "" << "TARIFA POR NÚMERO DE REPRODUCCIONES: " << tarifaReprod <<
        " POR CADA 1,000 REPRODUCCIONES Y FRACCION" << endl
        << setw(48) << "" << "TARIFA POR DURACION DEL STREAM: " << tarifaDura << " POR CADA MINUTO Y FRACCION" << endl;
}

void imprimirDatos(ifstream& archDat, ofstream& archRep,
                   int& cantFinal, int& duraFinal, double& ingresoDuraFinal, double& ingresoPubliFinal,
                   int fechaIni, int fechaFin, double tarifaReprod, double tarifaDura) {
    int fecha, contador = 1, duraTotal = 0;
    double index, ingresoRepTotal, ingresoDuraTotal;

    while (true) {
        fecha = leerFecha(archDat);
        if (archDat.eof()) break;
        if (fechaIni <= fecha and fecha <= fechaFin) {
            imprimirSubtitulos(archDat, archRep, fecha, contador, index);
            imprimirReproduccionesYResumen(archDat, archRep, duraTotal, cantFinal,
                                           ingresoRepTotal, ingresoDuraTotal, tarifaReprod, tarifaDura, index);

            duraFinal += duraTotal;
            ingresoDuraFinal += ingresoDuraTotal;
            ingresoPubliFinal += ingresoRepTotal;

            contador++;
        }
        else
            while (archDat.get() != '\n');
    }
}

void imprimirSubtitulos(ifstream& archDat, ofstream& archRep, int fecha, int contador, double& index) {
    char letraCod;
    int codigo, seguidores, vistas, espectadores;
    // F3765    Fextralife       1734810    93036735    222720

    imprimirLinea(archRep, '=');
    archRep << left << "CANAL No " << contador << endl
        << setw(6) << "" << setw(30) << "NOMBRE" << setw(12) << "CODIGO"
        << setw(20) << "CREADO EL" << setw(30) << "SEGUIDORES NUEVOS POR MES"
        << setw(30) << "VISITAS NUEVAS POR MES" << "MAXIMO DE ESPECTADORES" << endl;

    archDat >> letraCod >> codigo;
    imprimirNombre(archDat, archRep);
    archDat >> seguidores >> vistas >> espectadores;

    archRep << left << letraCod << setw(11) << codigo;
    imprimirFecha(archRep, fecha);
    archRep << right << setw(25) << seguidores << setw(30) << vistas << setw(30) << espectadores << endl;
    imprimirLinea(archRep, '-');

    index = ((double)seguidores + (double)vistas / 100) / (double)espectadores;
}

void imprimirReproduccionesYResumen(ifstream& archDat, ofstream& archRep, int& duraTotal, int& cantFinal,
                                    double& ingresoRepTotal,
                                    double& ingresoDuraTotal, double tarifaReprod, double tarifaDura, double index) {
    int fecha, duracion, reproducciones, repTotal = 0;
    double ingresoDura, ingresoRep;
    ingresoDuraTotal = 0.0;
    ingresoRepTotal = 0.0;
    duraTotal = 0;

    archRep << left << setw(5) << "" << "ULTIMAS REPRODUCCIONES" << endl
        << setw(11) << "" << setw(30) << "FECHA DE PUBLICACION" << setw(30) << "TIEMPO DE DURACION"
        << setw(30) << "INGRESOS POR DURACION" << "NUMERO DE REPRODUCCIONES" << endl;

    while (true) {
        fecha = leerFecha(archDat);
        duracion = leerDuracion(archDat);
        archDat >> reproducciones;

        ingresoDura = (double)duracion / 60 * tarifaDura;
        ingresoRep = (double)reproducciones / 1000 * tarifaReprod;

        archRep << setw(11) << "";
        imprimirFecha(archRep, fecha);
        archRep << setw(25) << "";
        imprimirDuracion(archRep, duracion);
        archRep << right << setw(30) << ingresoDura << setw(30) << ingresoRep << endl;

        duraTotal += duracion;
        ingresoDuraTotal += ingresoDura;
        ingresoRepTotal += ingresoRep;
        repTotal += reproducciones;

        cantFinal++;

        if (archDat.get() == '\n') break;
    }

    imprimirResumenCanal(archRep, duraTotal, ingresoDuraTotal, repTotal, ingresoRepTotal, index);
}

void imprimirResumenCanal(ofstream& archRep, int duraTotal, double ingresoDuraTotal, int repTotal,
                          double ingresoRepTotal, double index) {
    imprimirLinea(archRep, '-');
    archRep << setw(5) << "" << "RESUMEN DEL CANAL:" << endl
        << setw(5) << "" << "DURACION TOTAL DE LAS REPRODUCCIONES: ";
    imprimirDuracion(archRep, duraTotal);
    archRep << endl
        << left << setw(5) << "" << setw(TAM_RESUMEN_CAN) << "INGRESOS POR DURACION" << "$" << right << setw(7) <<
        ingresoDuraTotal << endl
        << left << setw(5) << "" << setw(TAM_RESUMEN_CAN) << "TOTAL DE REPRODUCCIONES" << right << setw(8) << repTotal
        << endl
        << left << setw(5) << "" << setw(TAM_RESUMEN_CAN) << "INGRESOS POR PUBLICIDAD" << "$" << right << setw(7) <<
        ingresoRepTotal << endl
        << left << setw(5) << "" << setw(TAM_RESUMEN_CAN) << "ENGAGEMENT INDEX" << right << setw(8) << index << endl <<
        endl;
}

void imprimirResumenFinal(ofstream& archRep, int cantFinal, int duraFinal, double ingresoDuraFinal,
                          double ingresoRepFinal) {
    imprimirLinea(archRep, '=');
    archRep << "RESUMEN FINAL: " << endl
        << left << setw(TAM_RESUMEN_FIN) << "CANTIDAD TOTAL DE STREAMS COLOCADOS POR CANALES: " << right << setw(9) <<
        cantFinal << endl
        << left << setw(TAM_RESUMEN_FIN) << "DURACION TOTAL DE LOS STREAMS PUBLICADOS: ";
    imprimirDuracion(archRep, duraFinal);
    archRep << endl
        << left << setw(TAM_RESUMEN_FIN) << "INGRESOS TOTALES POR DURACION:" << right << '$' << setw(8) <<
        ingresoDuraFinal << endl
        << left << setw(TAM_RESUMEN_FIN) << "INGRESOS TOTALES POR PUBLICIDAD:" << right << '$' << setw(8) <<
        ingresoRepFinal << endl;
}
