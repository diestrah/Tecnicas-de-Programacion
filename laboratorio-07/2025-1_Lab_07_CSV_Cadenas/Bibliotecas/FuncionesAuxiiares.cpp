#include "FuncionesAuxiiares.h"

// FUNCIONES SECUNDARIAS
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

char leerChar(ifstream& arch) {
    char dato;
    arch.get(dato);
    arch.ignore();
    return dato;
}

int leerFecha(ifstream& arch) {
    int dd, mm, yyyy;
    dd = leerInt(arch);
    mm = leerInt(arch);
    yyyy = leerInt(arch);
    return yyyy * 10000 + mm * 100 + dd;
}

char* leerString(ifstream& arch, char delim) {
    char buffer[MAX_CAD]{}, *cadena;
    arch.getline(buffer, MAX_CAD, delim);
    if (arch.eof()) return nullptr;
    cadena = new char[strlen(buffer) + 1]{};
    strcpy(cadena, buffer);
    return cadena;
}

// Manipulación de cadenas
void cambiarAMayus(char* cadena) {
    for (int i = 0; cadena[i]; i++)
        if ('a' <= cadena[i] and cadena[i] <= 'z')
            cadena[i] += 'A' - 'a';
}

// Impresión
void imprimirLinea(ofstream& arch, char car) {
    arch << setfill(car) << setw(TAM_PAG) << "" << endl
        << setfill(' ');
}

void imprimirContador(ofstream& arch, int num) {
    arch << setfill('0') << setw(2) << num + 1 << ")  " << endl
        << setfill(' ');
}

void imprimirFecha(ofstream& arch, int fecha) {
    int dd, mm, yyyy;
    dd = fecha % 100;
    mm = fecha / 100 % 100;
    yyyy = fecha / 10000;
    arch << right << setfill('0')
        << setw(2) << dd << '/' << setw(2) << mm << '/' << setw(4) << yyyy
        << setfill(' ');
}

// Intercambiar
void swapInt(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void swapString(char*& a, char*& b) {
    char* temp = a;
    a = b;
    b = temp;
}

void swapDouble(double& a, double& b) {
    double temp = a;
    a = b;
    b = temp;
}

// FUNCIONES PRINCIPALES
// Función 1: inicializar placas
void inicializarPlacas(char** arrPlacas, int maxLongitud, int maxEmpresas) {
    for (int i = 0; i < maxEmpresas; i++) {
        arrPlacas[i] = new char[maxLongitud]{};
    }
}

// Función 2: leer EmpresasRegistradas.csv
void leerEmpresasRegistradas(const char* nombArch,
                             int* arrDni, char** arrNombre, char** arrDistrito,
                             int& numEmpresas) {
    ifstream arch = abrirInput(nombArch);
    // 88167677,prado vera juan,San Miguel
    while (true) {
        arrDni[numEmpresas] = leerInt(arch);
        if (arch.eof()) break;
        arrNombre[numEmpresas] = leerString(arch, ',');
        arrDistrito[numEmpresas] = leerString(arch, '\n');
        cambiarAMayus(arrNombre[numEmpresas]);
        cambiarAMayus(arrDistrito[numEmpresas]);
        numEmpresas++;
    }
}

// Función 3: leer PlacasRegistradas.txt

void leerPlacasRegistradas(const char* nombArch,
                           int* arrDni, char** arrPlacas, int numEmpresas) {
    ifstream arch = abrirInput(nombArch);
    int dni, pos;
    char placa[10];
    // 12443643      M421-807
    while (true) {
        arch >> dni;
        if (arch.eof()) break;
        arch >> placa;

        pos = buscarDni(dni, arrDni, numEmpresas);
        if (pos != -1) {
            if (arrPlacas[pos][0] != '\0') strcat(arrPlacas[pos], "/");
            strcat(arrPlacas[pos], placa);
        }
    }
}

int buscarDni(int dni, int* arrDni, int numEmpresas) {
    for (int i = 0; i < numEmpresas; i++)
        if (arrDni[i] == dni) return i;
    return -1;
}

// Función 4: verificación de arrays
void verificarEmpresasYPlacasRegistradas(const char* nombArch,
                                         int* arrDni, char** arrNombre, char** arrDistrito, char** arrPlacas,
                                         int numEmpresas) {
    ofstream arch = abrirOutput(nombArch);
    // Encabezado
    arch << left << setw(TAM_DNI) << "DNI" << setw(TAM_NOM) << "NOMBRE"
        << setw(TAM_DIS) << "DISTRITO" << setw(TAM_PLA) << "PLACAS" << endl;
    // Impresión de datos
    for (int i = 0; i < numEmpresas; i++) {
        arch << left << setw(TAM_DNI) << arrDni[i]
            << setw(TAM_NOM) << arrNombre[i]
            << setw(TAM_DIS) << arrDistrito[i]
            << setw(TAM_PLA) << arrPlacas[i] << endl;
    }
}

// Función 5: leer TablaDeInfracciones.csv
void leerTablaDeInfracciones(const char* nombArch,
                             char** arrCodInfrac, double* arrMulta, char** arrDesInfrac,
                             int& numInfracciones) {
    ifstream arch = abrirInput(nombArch);
    // G2056,417.99,Abandonar el vehiculo en la via p�blica.
    while (true) {
        arrCodInfrac[numInfracciones] = leerString(arch, ',');
        if (arch.eof()) break;
        arrMulta[numInfracciones] = leerDouble(arch);
        arrDesInfrac[numInfracciones] = leerString(arch, '\n');
        numInfracciones++;
    }
}

// Función 6: verificar TablaDeInfracciones
void verificarTablaDeInfracciones(const char* nombArch,
                                  char** arrCodInfrac, double* arrMulta, char** arrDesInfrac,
                                  int& numInfracciones) {
    ofstream arch = abrirOutput(nombArch);
    arch << left << setw(TAM_COD) << "CODIGO:" << right << setw(TAM_DOUB) << "MULTA"
        << "   DESCRIPCIÓN INFRACCIÓN" << endl;
    for (int i = 0; i < numInfracciones; i++) {
        arch << left << setw(TAM_COD) << arrCodInfrac[i]
            << right << setw(TAM_DOUB) << arrMulta[i] << "   "
            << arrDesInfrac[i] << endl;
    }
}

// Función 7: leer InfraccionesCometidas.csv
void leerInfraccionesCometidas(const char* nombArch,
                               char** arrPlacas, int* arrFechaAnt, int* arrFechaNueva,
                               double* arrTotalLeves, double* arrTotalGraves, double* arrTotalMuyGraves,
                               int* arrCantFaltas, int numEmpresas,
                               char** arrCodInfrac, double* arrMulta, int numInfracciones) {
    ifstream arch = abrirInput(nombArch);
    int fechaInfrac, fechaPago;
    char *placa, *infraccion, pago;
    int posInfrac, posEmpr;
    // 1/12/2020,G760-721,G2022,N   (caso 1)
    // 23/7/2023,P474-593,G2060,P,22/8/2023     (caso 2)
    while (true) {
        fechaInfrac = leerFecha(arch);
        if (arch.eof()) break;
        placa = leerString(arch, ',');
        infraccion = leerString(arch, ',');
        pago = leerChar(arch);
        if (pago == 'P') fechaPago = leerFecha(arch);
        else fechaPago = 0;

        posInfrac = buscarInfraccion(infraccion, arrCodInfrac, numInfracciones);
        posEmpr = buscarEmpresa(placa, arrPlacas, numEmpresas);

        if (posInfrac != -1 and posEmpr != -1) {
            actualizarDatos(infraccion, arrMulta[posInfrac],
                            fechaInfrac, fechaPago, arrFechaAnt[posEmpr],
                            arrFechaNueva[posEmpr], arrTotalLeves[posEmpr], arrTotalGraves[posEmpr],
                            arrTotalMuyGraves[posEmpr], arrCantFaltas[posEmpr]);
        }
    }
}

int buscarInfraccion(char* infraccion, char** arrCodInfrac, int numInfracciones) {
    for (int i = 0; i < numInfracciones; i++) {
        if (strcmp(infraccion, arrCodInfrac[i]) == 0) return i;
    }
    return -1;
}

int buscarEmpresa(char* placa, char** arrPlacas, int numEmpresas) {
    for (int i = 0; i < numEmpresas; i++) {
        if (verificaSiEstaLaPlaca(arrPlacas[i], placa)) return i;
    }
    return -1;
}

bool verificaSiEstaLaPlaca(const char* listaDePlacas, char* placa) {
    if (strstr(listaDePlacas, placa)) return true;
    return false;
}

void actualizarDatos(char* infraccion, double multa,
                     int fechaInfrac, int fechaPago, int& fechaInfracAnt,
                     int& fechaPagoNueva, double& totalLeves, double& totalGraves,
                     double& totalMuyGraves, int& cantFaltas) {
    char gravedad = infraccion[0];
    if (cantFaltas == 0) {
        fechaInfracAnt = fechaInfrac;
        fechaPagoNueva = fechaPago;
    }
    else {
        if (fechaInfrac < fechaInfracAnt) fechaInfracAnt = fechaInfrac;
        if (fechaPagoNueva < fechaPago) fechaPagoNueva = fechaPago;
    }

    switch (gravedad) {
    case 'L':
        totalLeves += multa;
        break;
    case 'G':
        totalGraves += multa;
        break;
    case 'M':
        totalMuyGraves += multa;
        break;
    default:
        break;
    }

    cantFaltas++;
}


// Función 8: ordenar arreglos
void ordenarArreglos(int* arrDni, char** arrNombre, char** arrDistrito,
                     char** arrPlacas, int* arrFechaAnt, int* arrFechaNueva,
                     double* arrTotalLeves, double* arrTotalGraves,
                     double* arrTotalMuyGraves, int* arrCantFaltas, int numEmpresas) {
    for (int i = 0; i < numEmpresas - 1; i++) {
        for (int j = i + 1; j < numEmpresas; j++) {
            if (arrFechaAnt[i] > arrFechaAnt[j] or
                arrFechaAnt[i] == arrFechaAnt[j] and strcmp(arrNombre[i], arrNombre[j]) > 0) {
                swapInt(arrDni[i], arrDni[j]);
                swapString(arrNombre[i], arrNombre[j]);
                swapString(arrDistrito[i], arrDistrito[j]);
                swapString(arrPlacas[i], arrPlacas[j]);
                swapInt(arrFechaAnt[i], arrFechaAnt[j]);
                swapInt(arrFechaNueva[i], arrFechaNueva[j]);
                swapDouble(arrTotalLeves[i], arrTotalLeves[j]);
                swapDouble(arrTotalGraves[i], arrTotalGraves[j]);
                swapDouble(arrTotalMuyGraves[i], arrTotalMuyGraves[j]);
                swapInt(arrCantFaltas[i], arrCantFaltas[j]);
            }
        }
    }
}

// Función 9: emitir reporte
void emitirReporte(const char* nombArch, int* arrDni, char** arrNombre, char** arrDistrito,
                   char** arrPlacas, int* arrFechaAnt, int* arrFechaNueva, double* arrTotalLeves,
                   double* arrTotalGraves, double* arrTotalMuyGraves, int* arrCantFaltas, int numEmpresas) {
    ofstream arch = abrirOutput(nombArch);

    arch << left << setw(TAM_DNI) << "DNI" << setw(TAM_NOM) << "NOMBRE"
        << setw(TAM_DIS) << "DISTRITO" << setw(TAM_PLA) << "PLACAS" << endl;

    for (int i = 0; i < numEmpresas; i++) {
        arch << left << setw(TAM_DNI) << arrDni[i]
            << setw(TAM_NOM) << arrNombre[i]
            << setw(TAM_DIS) << arrDistrito[i]
            << setw(TAM_PLA) << arrPlacas[i];
        arch << right << "   ";
        imprimirFecha(arch, arrFechaAnt[i]);
        arch << "   ";
        imprimirFecha(arch, arrFechaNueva[i]);
        arch << setw(TAM_DOUB) << arrTotalLeves[i]
            << setw(TAM_DOUB) << arrTotalGraves[i]
            << setw(TAM_DOUB) << arrTotalMuyGraves[i]
            << setw(TAM_DOUB) << arrCantFaltas[i];
        arch << endl;
    }
}
