#include "FuncionesAuxiliares.h"

/*------------------------------------------------------------------*/
// Funciones Secundarias --------------------------------------------
/*------------------------------------------------------------------*/

// Funciones de apertura de archivos
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

// Funciones de lectura de datos
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
    arch.get();
    return dato;
}

char* leerString(ifstream& arch, char delim) {
    char buffer[MAX_CAD], *cadena;
    arch.getline(buffer, MAX_CAD, delim);
    if (arch.eof()) return nullptr;
    cadena = new char[strlen(buffer) + 1];
    strcpy(cadena, buffer);
    return cadena;
}

struct Fecha leerFecha(ifstream& arch) {
    struct Fecha f;
    f.dd = leerInt(arch);
    f.mm = leerInt(arch);
    f.aa = leerInt(arch);
    f.fecha = f.dd + f.mm * 100 + f.aa * 10000;
    return f;
}

// Funciones de manipulación de strings
void cambiarAMayus(char* cadena) {
    for (int i = 0; cadena[i]; i++) {
        if ('a' <= cadena[i] and cadena[i] <= 'z')
            cadena[i] += 'A' - 'a';
    }
}

// Funciones ayuda de impresión
void imprimirLinea(ofstream& arch, char car) {
    arch << setfill(car) << setw(TAM_PAG) << "" << endl << setfill(' ');
}

void imprimirFecha(ofstream& arch, struct Fecha f) {
    arch << right << setfill('0') << setw(2) << f.dd << '/' << setw(2) << f.mm << '/' << f.aa << "    ";
    arch << setfill(' ');
}

void imprimirContador(ofstream& arch, int i) {
    arch << right << setw(3) << i << ")  ";
}

/*------------------------------------------------------------------*/
// Funciones Principales --------------------------------------------
/*------------------------------------------------------------------*/

// Módulo 1: leer TablaDeInfracciones.csv
void leerTablaDeInfracciones(const char* nombArch,
                             struct TablaDeInfracciones* arrTablaDeInfracciones, int& numInfrac) {
    ifstream arch = abrirInput(nombArch);
    struct TablaDeInfracciones t{};
    // L3001,214.55,Dejar mal estacionado el vehiculo en lugares permitidos.
    while (true) {
        t.codigo = leerString(arch, ',');
        if (arch.eof()) break;
        t.multa = leerDouble(arch);
        t.descripcion = leerString(arch, '\n');
        cambiarAMayus(t.descripcion);
        arrTablaDeInfracciones[numInfrac] = t;
        numInfrac++;
    }
}

// Módulo 2: leer EmpresasRegistradas.csv
void leerEmpresasRegistradas(const char* nombArch,
                             struct EmpresasRegistradas* arrEmpresasRegistradas, int& numEmpr) {
    ifstream arch = abrirInput(nombArch);
    struct EmpresasRegistradas e{};
    //47844324,vilca lee nestor hugo,Comas
    while (true) {
        e.dni = leerInt(arch);
        if (arch.eof()) break;
        e.nombre = leerString(arch, ',');
        e.distrito = leerString(arch, '\n');
        e.placas = new char*[10]{};
        cambiarAMayus(e.nombre);
        cambiarAMayus(e.distrito);
        arrEmpresasRegistradas[numEmpr] = e;
        numEmpr++;
    }
}

// Módulo 3: leer PlacasRegistradas.txt
void leerPlacasRegistradas(const char* nombArch,
                           struct EmpresasRegistradas* arrEmpresasRegistradas, int numEmpr) {
    ifstream arch = abrirInput(nombArch);
    int dni, pos, numPlaca;
    char* placa;
    // 75945248   P939-759
    while (true) {
        dni = leerInt(arch); // aunque el archivo no es csv, igual solo consume un espacio
        if (arch.eof()) break;
        arch >> ws;
        placa = leerString(arch, '\n');

        pos = buscarDni(dni, arrEmpresasRegistradas, numEmpr);
        if (pos != -1) {
            numPlaca = arrEmpresasRegistradas[pos].numPlacas;
            arrEmpresasRegistradas[pos].placas[numPlaca] = placa;
            arrEmpresasRegistradas[pos].numPlacas++;
        }
    }
}

int buscarDni(int dni, const struct EmpresasRegistradas* arrEmpresasRegistradas, int numEmpr) {
    for (int i = 0; i < numEmpr; i++)
        if (arrEmpresasRegistradas[i].dni == dni) return i;
    return -1;
}

// Módulo 4: leer InfraccionesCometidas.csv
void leerInfraccionesCometidas(const char* nombArch,
                               struct EmpresasRegistradas* arrEmpresasRegistradas, int numEmpr,
                               struct TablaDeInfracciones* arrTablaDeInfracciones, int numInfrac) {
    ifstream arch = abrirInput(nombArch);
    struct EmpresasRegistradas e{};
    char *infraccion, *placa, pagado;
    double multa;
    int posEmpr;
    // 7/7/2021,M207-572,M1024,P,31/7/2021   (caso 1)
    // 27/8/2022,G542-724,G2027,N   (caso 2)
    while (true) {
        e.fechaDeInfraccion = leerFecha(arch);
        if (arch.eof()) break;
        placa = leerString(arch, ',');
        infraccion = leerString(arch, ',');
        pagado = leerChar(arch);
        if (pagado == 'P') e.fechaDePago = leerFecha(arch);

        multa = buscarInfraccion(infraccion, arrTablaDeInfracciones, numInfrac);
        posEmpr = buscarEmpresaPorPlaca(placa, arrEmpresasRegistradas, numEmpr);
        if (posEmpr != -1) {
            insertarDatos(e, multa, pagado, arrEmpresasRegistradas[posEmpr]);
        }
    }
}

double buscarInfraccion(char* infraccion, TablaDeInfracciones* arrTablaDeInfracciones, int numInfrac) {
    for (int i = 0; i < numInfrac; i++) {
        if (strcmp(infraccion, arrTablaDeInfracciones[i].codigo) == 0)
            return arrTablaDeInfracciones[i].multa;
    }
    return 0;
}

int buscarEmpresaPorPlaca(char* placa, struct EmpresasRegistradas* arrEmpresasRegistradas, int numEmpr) {
    int numPlacas;
    for (int i = 0; i < numEmpr; i++) {
        numPlacas = arrEmpresasRegistradas[i].numPlacas;
        for (int j = 0; j < numPlacas; j++) {
            if (strcmp(arrEmpresasRegistradas[i].placas[j], placa) == 0) return i;
        }
    }
    return -1;
}

void insertarDatos(struct EmpresasRegistradas e, double multa, char pagado,
                   struct EmpresasRegistradas& EmpresaRegistrada) {
    if (EmpresaRegistrada.cantidadDeFaltas == 0) // si es el primer dato, insertar fecha
        EmpresaRegistrada.fechaDeInfraccion = e.fechaDeInfraccion;
    else // si hay más datos, guardar la última fecha
        if (EmpresaRegistrada.fechaDeInfraccion.fecha > e.fechaDeInfraccion.fecha)
            EmpresaRegistrada.fechaDeInfraccion = e.fechaDeInfraccion;

    if (pagado == 'P') {
        EmpresaRegistrada.totalPagado += multa;
        if (EmpresaRegistrada.fechaDePago.fecha < e.fechaDePago.fecha)
            EmpresaRegistrada.fechaDePago = e.fechaDePago;
    }
    else {
        EmpresaRegistrada.totalAdeudado += multa;
    }

    EmpresaRegistrada.totalDeMultas += multa;
    EmpresaRegistrada.cantidadDeFaltas++;
}

// Módulo 5: ordenar structs de arrEmpresasRegistradas
void ordenarEmpresasRegistradas(struct EmpresasRegistradas* arrEmpresasRegistradas, int numEmpr) {
    for (int i = 0; i < numEmpr - 1; i++) {
        for (int j = i; j < numEmpr; j++) {
            if (strcmp(arrEmpresasRegistradas[i].distrito, arrEmpresasRegistradas[j].distrito) > 0 or
                strcmp(arrEmpresasRegistradas[i].distrito, arrEmpresasRegistradas[j].distrito) == 0 and
                arrEmpresasRegistradas[i].fechaDeInfraccion.fecha <= arrEmpresasRegistradas[j].fechaDeInfraccion.fecha)
                cambiarStructEmpresas(arrEmpresasRegistradas[i], arrEmpresasRegistradas[j]);
        }
    }
}

void cambiarStructEmpresas(struct EmpresasRegistradas& a, struct EmpresasRegistradas& b) {
    struct EmpresasRegistradas temp;
    temp = a;
    a = b;
    b = temp;
};

// Módulo 6: ordenar structs de arrTablaDeInfracciones
void ordenarTablaDeInfracciones(struct TablaDeInfracciones* arrTablaDeInfracciones, const int numInfrac) {
    for (int i = 0; i < numInfrac - 1; i++) {
        for (int j = i; j < numInfrac; j++) {
            if (strcmp(arrTablaDeInfracciones[i].codigo, arrTablaDeInfracciones[j].codigo) < 0)
                cambiarStructInfracciones(arrTablaDeInfracciones[i], arrTablaDeInfracciones[j]);
        }
    }
}

void cambiarStructInfracciones(struct TablaDeInfracciones& a, struct TablaDeInfracciones& b) {
    struct TablaDeInfracciones temp;
    temp = a;
    a = b;
    b = temp;
}

// Módulo 7: emitir reporte
void emitirReporte(const char* nombArch, struct EmpresasRegistradas* arrEmpresasRegistradas, int numEmpr,
                   struct TablaDeInfracciones* arrTablaDeInfracciones, int numInfrac) {
    ofstream arch = abrirOutput(nombArch);
    imprimirInfraccionesDeEmpresas(arch, arrEmpresasRegistradas, numEmpr);
    imprimirTablaDeInfracciones(arch, arrTablaDeInfracciones, numInfrac);
}

void imprimirInfraccionesDeEmpresas(ofstream& arch, struct EmpresasRegistradas* arrEmpresasRegistradas,
                                    int numEmpr) {
    double totalPagado = 0, totalAdeudado = 0;
    int totalInfracciones = 0;
    // Encabezado
    imprimirEncabezadoYSubtitulos(arch);
    // Impresión de datos
    for (int i = 0; i < numEmpr; i++) {
        imprimirContador(arch, i);
        arch << left << setw(TAM_DNI) << arrEmpresasRegistradas[i].dni
            << setw(TAM_NOM) << arrEmpresasRegistradas[i].nombre
            << setw(TAM_DIS) << arrEmpresasRegistradas[i].distrito;
        imprimirPlacas(arch, arrEmpresasRegistradas[i]);
        imprimirFecha(arch, arrEmpresasRegistradas[i].fechaDeInfraccion);
        imprimirFecha(arch, arrEmpresasRegistradas[i].fechaDePago);
        arch << right << setw(TAM_DOUB) << arrEmpresasRegistradas[i].totalPagado
            << "   " << setw(TAM_DOUB) << arrEmpresasRegistradas[i].totalAdeudado
            << setw(TAM_DOUB) << arrEmpresasRegistradas[i].cantidadDeFaltas;
        arch << endl;
        // Cálculos (puede ser un módulo)
        totalPagado += arrEmpresasRegistradas[i].totalPagado;
        totalAdeudado += arrEmpresasRegistradas[i].totalAdeudado;
        totalInfracciones += arrEmpresasRegistradas[i].cantidadDeFaltas;
    }
    // Resumen
    imprimirLinea(arch, '=');
    arch << right << setw(148) << "" << "TOTALES:" << setw(TAM_DOUB + 7) << totalPagado << setw(TAM_DOUB + 3)
        << totalAdeudado << setw(TAM_DOUB) << totalInfracciones << endl;
}

void imprimirPlacas(ofstream& arch, const struct EmpresasRegistradas& e) {
    char cadenaDePlacas[200]{};
    strcpy(cadenaDePlacas, e.placas[0]);
    for (int i = 1; i < e.numPlacas; i++) {
        strcat(cadenaDePlacas, "/");
        strcat(cadenaDePlacas, e.placas[i]);
    }
    arch << left << setw(TAM_PLAC) << cadenaDePlacas;
}

void imprimirEncabezadoYSubtitulos(ofstream& arch) {
    arch << setw(60) << "" << "MINISTERIO DE TRANSPORTES" << endl
        << setw(54) << "" << "LISTADO DE INFRACCIONES POR EMPRESA" << endl;
    imprimirLinea(arch, '=');

    arch << left << setw(43) << "" << "EMPRESA" << setw(85) << "" << "FECHA INF.   "
        << "FECHA PAGO" << setw(33) << "" << "CANTIDAD" << endl;

    arch << "  No." << setw(TAM_DNI) << " DNI" << setw(TAM_NOM) << " NOMBRE"
        << setw(TAM_DIS) << "DISTRITO" << setw(TAM_PLAC) << "PLACAS" << "MAS ANTIGUA  "
        << "MAS RECIENTE  " << "TOTAL PAGADO  " << "TOTAL ADEUDADO  " << "DE FALTAS" << endl;

    imprimirLinea(arch, '=');
}

void imprimirTablaDeInfracciones(ofstream& arch, struct TablaDeInfracciones* arrTablaDeInfracciones,
                                 int numInfrac) {
    // Encabezado
    imprimirLinea(arch, '=');
    arch << setw(54) << "" << "TABLA DE INFRACCIONES" << endl;
    imprimirLinea(arch, '=');

    arch << left << setw(12) << "" << setw(TAM_DOUB) << "CODIGO" << setw(TAM_DOUB) << "  MULTA"
        << setw(4) << "" << "DESCRIPCION" << endl;
    imprimirLinea(arch, '=');

    // Impresión de la data de arrTablaDeInfracciones
    for (int i = 0; i < numInfrac; i++) {
        arch << setw(12) << "" << left << setw(TAM_INFR) << arrTablaDeInfracciones[i].codigo
            << right << setw(TAM_DOUB) << arrTablaDeInfracciones[i].multa << setw(4) << ""
            << left << arrTablaDeInfracciones[i].descripcion << endl;
    }
    imprimirLinea(arch, '=');
}
