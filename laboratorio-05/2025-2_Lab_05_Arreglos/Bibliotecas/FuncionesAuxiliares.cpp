#include "FuncionesAuxiliares.h"

/*------------------------------------------------------------------*/
// Funciones secundarias --------------------------------------------
/*------------------------------------------------------------------*/

// De impresión
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

// De lectura de datos
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

// De impresión
void imprimirDuracion(ofstream& arch, int duracion) {
    int hh, mm, ss;
    hh = duracion / 3600;
    mm = duracion / 60 % 60;
    ss = duracion % 60;
    arch << right << setfill('0')
        << setw(2) << hh << ":" << setw(2) << mm << ":" << setw(2) << ss
        << setfill(' ');
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

// De suprimir
void suprimir(ifstream& arch, char car) {
    arch >> ws;
    while (arch.get() != car);
}

// De intercambio
void cambiarInt(int& i, int& j) {
    int temp = i;
    i = j;
    j = temp;
}

void cambiarDouble(double& i, double& j) {
    double temp = i;
    i = j;
    j = temp;
}

void cambiarChar(char& i, char& j) {
    char temp = i;
    i = j;
    j = temp;
}

/*------------------------------------------------------------------*/
// Funciones Principales ---------------------------------------------
/*------------------------------------------------------------------*/

// Parte a:
void leerStreamsOrdenado(const char* nombArch,
                         int* arrCodStream, int* arrDuracion, int* arrIdioma,
                         char* arrLetraCate, int* arrCodCate, int& numStream) {
    ifstream arch = abrirInput(nombArch);
    int codStream, duracion, idioma, codCate;
    char letraCate;
    // 576104    2:11:48    3071    O1070
    while (true) {
        arch >> codStream;
        if (arch.eof()) break;
        duracion = leerDuracion(arch);
        arch >> idioma >> ws >> letraCate >> codCate;
        insertarOrdenado(codStream, duracion, idioma, letraCate, codCate,
                         arrCodStream, arrDuracion, arrIdioma, arrLetraCate, arrCodCate,
                         numStream);
    }
}

void insertarOrdenado(int codStream, int duracion, int idioma, char letraCate, int codCate,
                      int* arrCodStream, int* arrDuracion, int* arrIdioma,
                      char* arrLetraCate, int* arrCodCate,
                      int& numStream) {
    int i = numStream;
    while (true) {
        i--;
        if (i < 0 || codStream > arrCodStream[i]) break;
        arrCodStream[i + 1] = arrCodStream[i];
        arrDuracion[i + 1] = arrDuracion[i];
        arrIdioma[i + 1] = arrIdioma[i];
        arrLetraCate[i + 1] = arrLetraCate[i];
        arrCodCate[i + 1] = arrCodCate[i];
    }
    arrCodStream[i + 1] = codStream;
    arrDuracion[i + 1] = duracion;
    arrIdioma[i + 1] = idioma;
    arrLetraCate[i + 1] = letraCate;
    arrCodCate[i + 1] = codCate;
    numStream++;
}

// Parte b:
void verificarArraysDeStreams(const char* nombArch,
                              int* arrCodStream, int* arrDuracion, int* arrIdioma,
                              char* arrLetraCate, int* arrCodCate,
                              int numStream) {
    ofstream arch = abrirOutput(nombArch);
    // Encabezado
    arch << "    REPORTE DE ARRAYS DE STREAMS.TXT" << endl;
    arch << left << setw(TAM_COD) << "STREAM" << setw(13) << "DURACION"
        << setw(TAM_COD - 1) << "IDIOMA" << setw(TAM_COD) << "CATEGORIA" << endl;
    // Impresión de los datos
    for (int i = 0; i < numStream; i++) {
        arch << left << setw(TAM_COD) << arrCodStream[i];
        imprimirDuracion(arch, arrDuracion[i]);
        arch << left << setw(TAM_ESP) << ""
            << setw(TAM_COD) << arrIdioma[i]
            << arrLetraCate[i] << setw(TAM_COD - 1) << arrCodCate[i];
        arch << endl;
    }
}

// Parte c:
void leerCanales(const char* nombArch, int* arrCodStream, int numStream,
                 int* arrCantReprod, int* arrTotalReprod, int* arrRepAntigua,
                 int* arrRepReciente, double* arrPromRating, double* arrPromDropOff) {
    ifstream arch = abrirInput(nombArch);
    // 1/10/2022    A1911    AdmiralBulldog    738184    1/9/2025    15:13:35    3.38    0.628    929142
    while (true) {
        arch >> ws; // los primeros datos no importan
        if (arch.eof()) break;
        suprimir(arch, ' '); // suprime la fecha de creación
        suprimir(arch, ' '); // suprime el codigo del canal
        suprimir(arch, ' '); // suprime el nombre del canal
        leerInfoStreams(arch, arrCodStream, numStream, arrCantReprod, arrTotalReprod,
                        arrRepAntigua, arrRepReciente, arrPromRating, arrPromDropOff);
    }
}

void leerInfoStreams(ifstream& arch, int* arrCodStream, int numStream,
                     int* arrCantReprod, int* arrTotalReprod, int* arrRepAntigua,
                     int* arrRepReciente, double* arrPromRating, double* arrPromDropOff) {
    int codigo, pos;
    while (true) {
        arch >> codigo;
        pos = buscarStream(codigo, arrCodStream, numStream);
        if (pos != -1) {
            insertarDatos(arch, arrCantReprod[pos], arrTotalReprod[pos],
                          arrRepAntigua[pos], arrRepReciente[pos],
                          arrPromRating[pos], arrPromDropOff[pos]);
        }
        if (arch.peek() == '\n') break;
    }
}

int buscarStream(int codigo, int* arrCodStream, int numStream) {
    int limInf = 0, limSup = numStream - 1, puntoMedio;
    while (true) {
        if (limSup < limInf) return -1;
        puntoMedio = (limInf + limSup) / 2;
        if (arrCodStream[puntoMedio] == codigo) return puntoMedio;
        if (arrCodStream[puntoMedio] > codigo) limSup = puntoMedio - 1;
        else limInf = puntoMedio + 1;
    }
}

void insertarDatos(ifstream& arch, int& cantReprod, int& totalReprod, int& repAntigua,
                   int& repReciente, double& promRating, double& promDropOff) {
    int fecha, duracion;
    double rating, dropOff;
    // 1/9/2025    15:13:35    3.38    0.628
    fecha = leerFecha(arch);
    duracion = leerDuracion(arch);
    arch >> rating >> dropOff;

    if (cantReprod == 0) {
        repAntigua = fecha;
        repReciente = fecha;
    }
    else {
        if (fecha < repAntigua) repAntigua = fecha;
        if (repReciente < fecha) repReciente = fecha;
    }

    totalReprod += duracion;

    // Actualizar promedios en línea (sin dividir luego otra vez)
    promRating = (promRating * cantReprod + rating) / (cantReprod + 1);
    promDropOff = (promDropOff * cantReprod + dropOff) / (cantReprod + 1);
    cantReprod++;
}

// Parte d:
void ordernarPorRatingYDropOff(int* arrCodStream, int* arrDuracion,
                               int* arrIdioma, char* arrLetraCate, int* arrCodCate,
                               int* arrCantReprod, int* arrTotalReprod, int* arrRepAntigua,
                               int* arrRepReciente, double* arrPromRating, double* arrPromDropOff,
                               int numStream) {
    for (int i = 0; i < numStream - 1; i++) {
        for (int j = i + 1; j < numStream; j++) {
            if (arrPromRating[i] < arrPromRating[j] ||
                (arrPromRating[i] == arrPromRating[j] && arrPromDropOff[i] > arrPromDropOff[j])) {
                cambiarInt(arrCodStream[i], arrCodStream[j]);
                cambiarInt(arrDuracion[i], arrDuracion[j]);
                cambiarInt(arrIdioma[i], arrIdioma[j]);
                cambiarChar(arrLetraCate[i], arrLetraCate[j]);
                cambiarInt(arrCodCate[i], arrCodCate[j]);
                cambiarInt(arrCantReprod[i], arrCantReprod[j]);
                cambiarInt(arrTotalReprod[i], arrTotalReprod[j]);
                cambiarInt(arrRepAntigua[i], arrRepAntigua[j]);
                cambiarInt(arrRepReciente[i], arrRepReciente[j]);
                cambiarDouble(arrPromRating[i], arrPromRating[j]);
                cambiarDouble(arrPromDropOff[i], arrPromDropOff[j]);
            }
        }
    }
}

// Parte e:
void emitirReporte(const char* nombArch, int* arrCodStream, int* arrDuracion,
                   int* arrIdioma, char* arrLetraCate, int* arrCodCate,
                   int* arrCantReprod, int* arrTotalReprod, int* arrRepAntigua,
                   int* arrRepReciente, double* arrPromRating, double* arrPromDropOff,
                   int numStream, bool resumen) {
    ofstream arch = abrirOutput(nombArch);
    int maxDura = 0, maxStream = 0, minDura = 1000000000, minStream = 0;
    imprimirEncabezado(arch, resumen);
    for (int i = 0; i < numStream; i++) {
        if (resumen) // Si es true, imprime el resumen y cumple las restricciones
            filtrarDuraciones(arrCodStream[i], arrDuracion[i],
                              maxStream, maxDura, minStream, minDura);

        arch << left << setw(TAM_COD) << arrCodStream[i]
            << setw(TAM_COD) << arrIdioma[i]
            << arrLetraCate[i] << setw(TAM_COD - 1) << arrCodCate[i];
        imprimirDuracion(arch, arrDuracion[i]);
        arch << setw(TAM_ESP) << ""; // esto crea espacios en blanco para luego imprimir la fecha
        imprimirFecha(arch, arrRepAntigua[i]);
        arch << setw(TAM_ESP) << "";
        imprimirFecha(arch, arrRepReciente[i]);

        arch << right << setw(TAM_PROM) << arrPromRating[i]
            << setw(TAM_ESP) << "" << setw(TAM_PROM) << arrPromDropOff[i]
            << setw(TAM_ESP) << "" << setw(TAM_ESP) << arrCantReprod[i]
            << setw(TAM_ESP) << "";

        imprimirDuracion(arch, arrTotalReprod[i]); // ahora sí: suma de duraciones
        arch << endl;
    }

    if (resumen) imprimirResumen(arch, maxStream, maxDura, minStream, minDura);
}

void imprimirEncabezado(ofstream& arch, bool resumen) {
    imprimirLinea(arch, '=');
    arch << "PLATAFORMA DE STREAMING TP" << endl;
    if (resumen)
        arch << "DETALLE COMPLETO DE REPRODUCCION DE STREAMS" << endl;
    else
        arch << "DETALLE COMPLETO DE REPRODUCCION DE STREAMS ORDENADO POR CATEGORIA Y TASA DROP-OFF" << endl;

    imprimirLinea(arch, '=');
    arch << left << setw(TAM_COD) << "STREAM" << setw(TAM_COD) << "IDIOMA"
        << setw(TAM_COD) << "CATEGORIA" << setw(TAM_DUR) << "DURACION"
        << setw(TAM_FEC + 2) << "REP.ANTIGUA" << setw(TAM_FEC) << "REP.RECIENTE"
        << setw(TAM_RAT) << "PROM.RAT.CAL" << setw(TAM_DROP) << "PROM.TASA.DROP-OFF  "
        << setw(TAM_COD - 1) << "#REPR." << "TOT. REPR." << endl;
    // Si te parece tedioso tener una variable tipo TAM_COD o TAM_DUR por cada variable que tengas,
    // te recomiendo simplemente colocar números. La finalidad es aprobar xdd
    imprimirLinea(arch, '-');
}

void filtrarDuraciones(int codigo, int duracion,
                       int& maxStream, int& maxDura,
                       int& minStream, int& minDura) {
    if (duracion < minDura) {
        minDura = duracion;
        minStream = codigo;
    }
    if (duracion > maxDura) {
        maxDura = duracion;
        maxStream = codigo;
    }
}

void imprimirResumen(ofstream& arch, int maxStream, int maxDura, int minStream, int minDura) {
    imprimirLinea(arch, '-');
    arch << "RESUMEN:" << endl;

    arch << left << setw(TAM_RES) << "STREAM CON MAYOR DURACION:" << maxStream << " - ";
    imprimirDuracion(arch, maxDura);
    arch << " hrs" << endl;

    arch << left << setw(TAM_RES) << "STREAM CON MENOR DURACION:" << minStream << " - ";
    imprimirDuracion(arch, minDura);
    arch << " hrs" << endl;
    imprimirLinea(arch, '=');
}
