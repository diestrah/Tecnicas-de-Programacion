#include "FuncionesAuxiliares.h"
#define TAM_PAG 140
#define MAX_CAD 200
#define TAM_COD 12
#define TAM_DOUB 8
#define TAM_NOM_EMP 40
#define TAM_NOM_DIS 25

/*
 *  Módulos Secundarios
 */

void abrirInput(ifstream& arch, const char* nombArch) {
    arch.open(nombArch, ios::in);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo " << endl;
        exit(1);
    }
}

void abrirOutput(ofstream& arch, const char* nombArch) {
    arch.open(nombArch, ios::out);
    if (not arch.is_open()) {
        cout << "ERROR: No se pudo abrir el archivo " << endl;
        exit(1);
    }
    arch.precision(2);
    arch << fixed;
}

int leerInt(ifstream& arch) {
    int dato;
    arch >> dato;
    arch.ignore();
    return dato;
}

double leerDouble(ifstream& arch) {
    double dato;
    arch >> dato;
    arch.ignore();
    return dato;
}

char leerChar(ifstream& arch) {
    char dato;
    arch >> dato;
    arch.ignore();
    return dato;
}

char* leerString(ifstream& arch, const char delim) {
    char buffer[MAX_CAD], *cadena;
    arch.getline(buffer, MAX_CAD, delim);
    if (arch.eof()) return nullptr;
    cadena = new char[strlen(buffer) + 1];
    strcpy(cadena, buffer);
    return cadena;
}

struct Fecha leerFecha(ifstream& arch) {
    struct Fecha f{};
    f.dd = leerInt(arch);
    f.mm = leerInt(arch);
    f.aa = leerInt(arch);
    f.fecha = f.aa * 10000 + f.mm * 100 + f.dd;
    return f;
}

void imprimirLinea(ofstream& arch, const char car) {
    arch << setfill(car) << setw(TAM_PAG) << "" << endl
        << setfill(' ');
}

void imprimirFecha(ofstream& arch, const struct Fecha f) {
    arch << right << setfill('0')
        << setw(2) << f.dd << '/' << setw(2) << f.mm << '/' << f.aa
        << setfill(' ');
}

void imprimirContador(ofstream& arch, const int contador) {
    arch << setfill('0') << setw(2) << contador << ")  "
        << setfill(' ');
}

void swapEmpresas(struct EmpresasRegistradas& a, struct EmpresasRegistradas& b) {
    struct EmpresasRegistradas temp = a;
    a = b;
    b = temp;
}

void swapInfraccion(struct InfraccionCometida& a, struct InfraccionCometida& b) {
    struct InfraccionCometida temp = a;
    a = b;
    b = temp;
}

/*
 *  Módulos Principales
 */


void leerTablaDeInfracciones(const char* nombArch, struct TablaDeInfracciones* arrTablaDeInfracciones,
                             int& numInfracciones) {
    ifstream arch;
    abrirInput(arch, nombArch);
    struct TablaDeInfracciones t{};
    // M1046,658.70,Obstruir la ciclovia
    while (true) {
        t.codigo = leerString(arch, ',');
        if (arch.eof()) break;
        t.multa = leerDouble(arch);
        t.descripcion = leerString(arch, '\n');
        arrTablaDeInfracciones[numInfracciones] = t;
        numInfracciones++;
    }
}


void verificarTablaDeInfracciones(const char* nombArch, const struct TablaDeInfracciones* arrTablaDeInfracciones,
                                  const int numInfracciones) {
    ofstream arch;
    abrirOutput(arch, nombArch);
    struct TablaDeInfracciones t{};
    for (int i = 0; i < numInfracciones; i++) {
        t = arrTablaDeInfracciones[i];
        arch << left << setw(TAM_COD) << t.codigo
            << right << setw(TAM_DOUB) << t.multa << setw(6) << ""
            << left << t.descripcion << endl;
    }
}

void leerEmpresasRegistradas(const char* nombArch, struct EmpresasRegistradas* arrEmpresasRegistradas,
                             int& numEmpresas) {
    ifstream arch;
    abrirInput(arch, nombArch);
    struct EmpresasRegistradas e{};
    // 88167677,prado vera juan,San Miguel
    while (true) {
        e.dni = leerInt(arch);
        if (arch.eof()) break;
        e.nombre = leerString(arch, ',');
        e.distrito = leerString(arch, '\n');
        e.infraccion = new struct InfraccionCometida[40];
        arrEmpresasRegistradas[numEmpresas] = e;
        numEmpresas++;
    }
}

void verificarEmpresasRegistradas(const char* nombArch, const struct EmpresasRegistradas* arrEmpresasRegistradas,
                                  const int numEmpresas) {
    ofstream arch;
    abrirOutput(arch, nombArch);
    struct EmpresasRegistradas e{};
    for (int i = 0; i < numEmpresas; i++) {
        e = arrEmpresasRegistradas[i];
        arch << left << setw(TAM_COD) << e.dni
            << setw(TAM_NOM_EMP) << e.nombre
            << setw(TAM_NOM_DIS) << e.distrito << endl;
    }
}

void leerPlacasRegistradas(const char* nombArch, struct EmpresasRegistradas* arrEmpresasRegistradas,
                           const int numEmpresas) {
    ifstream arch;
    abrirInput(arch, nombArch);
    int dni, pos, numPlacas;
    char* placa;
    // 90467829,G189-507
    while (true) {
        dni = leerInt(arch);
        if (arch.eof()) break;
        placa = leerString(arch, '\n');
        pos = buscarEmpresaPorDni(dni, arrEmpresasRegistradas, numEmpresas);
        if (pos != -1) {
            numPlacas = arrEmpresasRegistradas[pos].numPlacas;
            arrEmpresasRegistradas[pos].placas[numPlacas] = placa;
            arrEmpresasRegistradas[pos].numPlacas++;
        }
    }
}

int buscarEmpresaPorDni(const int dni, const struct EmpresasRegistradas* arrEmpresasRegistradas,
                        const int numEmpresas) {
    for (int i = 0; i < numEmpresas; i++) {
        if (dni == arrEmpresasRegistradas[i].dni) return i;
    }
    return -1;
}

void leerInfraccionesCometidas(const char* nombArch,
                               const struct TablaDeInfracciones* arrTablaDeInfracciones, const int numInfracciones,
                               struct EmpresasRegistradas* arrEmpresasRegistradas, const int numEmpresas) {
    ifstream arch;
    abrirInput(arch, nombArch);
    struct InfraccionCometida i{};
    char pagado;
    int pos;
    // 1/12/2020,G760-721,G2022,N
    // 23/7/2023,P474-593,G2060,P,22/8/2023
    while (true) {
        i = {};
        i.fechaDeInfraccion = leerFecha(arch);
        if (arch.eof()) break;
        i.placa = leerString(arch, ',');
        i.codigoDeLaInfraccion = leerString(arch, ',');
        pagado = leerChar(arch);
        if (pagado == 'P') {
            i.fechaDePago = leerFecha(arch);
            i.multaPagada = true;
        }
        else {
            i.multaPagada = false;
        }
        pos = buscarEmpresaPorPlaca(i.placa, arrEmpresasRegistradas, numEmpresas);
        if (pos != -1) {
            insertarDatos(arrEmpresasRegistradas[pos], i, arrTablaDeInfracciones, numInfracciones);
        }
    }
}

int buscarEmpresaPorPlaca(const char* placa, const struct EmpresasRegistradas* arrEmpresasRegistradas,
                          const int numEmpresas) {
    for (int i = 0; i < numEmpresas; i++) {
        for (int j = 0; j < arrEmpresasRegistradas[i].numPlacas; j++) {
            if (strcmp(arrEmpresasRegistradas[i].placas[j], placa) == 0) return i;
        }
    }
    return -1;
}

void insertarDatos(struct EmpresasRegistradas& e, struct InfraccionCometida i,
                   const struct TablaDeInfracciones* arrTablaDeInfracciones, const int numInfracciones) {
    int pos, numInfraccion = e.cantidadDeInfracciones;
    pos = buscarInfraccion(i.codigoDeLaInfraccion, arrTablaDeInfracciones, numInfracciones);
    if (pos != -1) {
        i.multa = arrTablaDeInfracciones[pos].multa;
        i.descripcion = arrTablaDeInfracciones[pos].descripcion;
        e.infraccion[numInfraccion] = i;
        e.cantidadDeInfracciones++;
    }
}

int buscarInfraccion(const char* codigoInfraccion, const struct TablaDeInfracciones* arrTablaDeInfracciones,
                     const int numInfracciones) {
    for (int i = 0; i < numInfracciones; i++) {
        if (strcmp(codigoInfraccion, arrTablaDeInfracciones[i].codigo) == 0) return i;
    }
    return -1;
}

void calcularTotales(struct EmpresasRegistradas* arrEmpresasRegistradas, const int numEmpresas) {
    for (int i = 0; i < numEmpresas; i++) {
        for (int j = 0; j < arrEmpresasRegistradas[i].cantidadDeInfracciones; j++) {
            if (arrEmpresasRegistradas[i].infraccion[j].multaPagada)
                arrEmpresasRegistradas[i].totalPagado += arrEmpresasRegistradas[i].infraccion[j].multa;
            else
                arrEmpresasRegistradas[i].totalAdeudado += arrEmpresasRegistradas[i].infraccion[j].multa;
        }
    }
}

void ordenarEmpresasRegistradas(struct EmpresasRegistradas* arrEmpresasRegistradas, const int numEmpresas) {
    for (int i = 0; i < numEmpresas - 1; i++) {
        for (int j = 0; j < arrEmpresasRegistradas[i].cantidadDeInfracciones - 1; j++) {
            for (int k = 0; k < arrEmpresasRegistradas[i].infraccion[j].multa; k++) {
                if (arrEmpresasRegistradas[i].infraccion[j].multaPagada == false and
                    arrEmpresasRegistradas[i].infraccion[k].multaPagada == true) {
                    swapInfraccion(arrEmpresasRegistradas[i].infraccion[j],
                                   arrEmpresasRegistradas[i].infraccion[k]);
                }
            }
        }
        for (int j = i; j < numEmpresas; j++) {
            if (strcmp(arrEmpresasRegistradas[i].distrito, arrEmpresasRegistradas[j].distrito) > 0)
                swapEmpresas(arrEmpresasRegistradas[j], arrEmpresasRegistradas[i]);
        }
    }
}

void emitirReporte(const char* nombArch, const struct EmpresasRegistradas* arrEmpresasRegistradas,
                   const int numEmpresas) {
    ofstream arch;
    abrirOutput(arch, nombArch);
    imprimirEncabezado(arch);

    for (int i = 0; i < numEmpresas; i++) {
        imprimirSubtitulosEmpresa(arch, arrEmpresasRegistradas[i], i);
        imprimirSubtitulosPlacas(arch);
        imprimirPlacas(arch, arrEmpresasRegistradas[i].infraccion, arrEmpresasRegistradas[i].cantidadDeInfracciones);
    }
}

void imprimirEncabezado(ofstream& arch) {
    arch << "MINISTERIO DE TRANSPORTES" << endl;
    arch << "LISTADO DE INFRACCIONES POR EMPRESA" << endl;
    imprimirLinea(arch, '=');
}

void imprimirSubtitulosEmpresa(ofstream& arch, const struct EmpresasRegistradas e,
                               const int i) {
    char* placas = concatenarPlacas(e.infraccion, e.numPlacas);
    imprimirContador(arch, i);
    arch << left << "DNI: " << setw(TAM_COD) << e.dni
        << "NOMBRE: " << setw(TAM_NOM_EMP) << e.nombre
        << "DISTRITO: " << setw(TAM_NOM_DIS) << e.distrito
        << "PLACAS: " << placas << endl;
    imprimirLinea(arch, '=');
}

char* concatenarPlacas(struct InfraccionCometida* arrInfracciones, const int numPlacas) {
    char cadAux[MAX_CAD], *cadena;
    strcpy(cadAux, arrInfracciones[0].placa);
    for (int i = 0; i < numPlacas; i++) {
        strcat(cadAux, "/");
        strcat(cadAux, arrInfracciones[i].placa);
    }
    cadena = new char[strlen(cadAux)+1];
    strcpy(cadena, cadAux);
    return cadena;
}

void imprimirSubtitulosPlacas(ofstream& arch) {
    arch << "  MULTAS PAGADAS:" << endl;
    arch << "     FECHA" << "PLACA" << "CODIGO DE INFRACCION" << "DESCRIPCION" << "MULTA" << "FECHA DE PAGO" << endl;
    imprimirLinea(arch, '-');
}

void imprimirPlacas(ofstream& arch, const struct InfraccionCometida* arrInfracciones, const int numInfracciones) {
    for (int i = 0; i < numInfracciones; i++) {
        imprimirContador(arch, i + 1);
        imprimirFecha(arch, arrInfracciones[i].fechaDeInfraccion);
        arch << left << setw(6) << ""
            << setw(TAM_COD) << arrInfracciones[i].codigoDeLaInfraccion
            << setw(TAM_NOM_DIS) << arrInfracciones[i].descripcion
            << right << setw(TAM_DOUB) << arrInfracciones[i].multa
            << setw(6) << "";
        if (arrInfracciones[i].multaPagada) imprimirFecha(arch, arrInfracciones[i].fechaDePago);
        arch << endl;
    }
    imprimirLinea(arch, '-');
}
