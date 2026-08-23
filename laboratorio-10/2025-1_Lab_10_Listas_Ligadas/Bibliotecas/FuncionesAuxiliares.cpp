#include "FuncionesAuxiliares.h"

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

char* leerString(ifstream& arch, char delim) {
    char buffer[MAX_CAD], *cadena;
    arch.getline(buffer, MAX_CAD, delim);
    if (arch.eof()) return nullptr;
    cadena = new char[strlen(buffer) + 1];
    strcpy(cadena, buffer);
    return cadena;
}

int leerFecha(ifstream& arch) {
    int dd, mm, aa;
    dd = leerInt(arch);
    mm = leerInt(arch);
    aa = leerInt(arch);
    return aa * 10000 + mm * 100 + dd;
}

void imprimirLinea(ofstream& arch, char car) {
    arch << setfill(car) << setw(TAM_PAG) << "" << endl
        << setfill(' ');
}

void imprimirFecha(ofstream& arch, int fecha) {
    int dd = fecha % 100;
    int mm = fecha / 100 % 100;
    int aa = fecha / 10000;
    arch << right << setfill('0')
        << setw(2) << dd << '/' << setw(2) << mm << '/' << aa
        << setfill(' ');
}

void imprimirContador(ofstream& arch, int contador) {
    arch << right << setfill('0') << setw(2) << contador << ")  "
        << setfill(' ');
}

/*
 *  Módulos Principales
*/
void leerCuentasBancarias(const char* nombArch, struct Nodo*& lista) {
    ifstream arch;
    abrirInput(arch, nombArch);
    lista = nullptr;
    // 58477632,Larriega Velasquez Moises Roberto,23326.62
    struct Cuenta c{};
    c.sobregiro = false;
    while (true) {
        c.codigo = leerInt(arch);
        if (arch.eof()) break;
        c.nombre = leerString(arch, ',');
        c.saldo = leerDouble(arch);
        insertarCuenta(lista, c);
    }
}

void insertarCuenta(Nodo*& lista, const struct Cuenta& c) {
    struct Nodo *anterior = nullptr, *actual = lista;
    struct Nodo* nuevo = new struct Nodo;
    nuevo->cuenta = c;
    while (actual) {
        if (actual->cuenta.codigo > c.codigo) break;
        anterior = actual;
        actual = actual->siguiente;
    }
    nuevo->siguiente = actual;
    if (anterior != nullptr) anterior->siguiente = nuevo;
    else lista = nuevo;
}

void leerMovimientosDeCuentas(const char* nombArch, struct Nodo* lista) {
    ifstream arch;
    abrirInput(arch, nombArch);
    int fecha, codCuenta;
    double monto;
    struct Nodo* cuenta;
    // 2/11/2024,67392071,14445.59,71839426,15211.07,70642877,-18247.08,14398081,10907.03,64627562,-17161.58
    while (true) {
        fecha = leerFecha(arch);
        if (arch.eof()) return;
        while (true) {
            codCuenta = leerInt(arch);
            arch >> monto;
            cuenta = buscarCuenta(lista, codCuenta);
            completarDatosCuenta(cuenta, fecha, monto);
            if (arch.get() == '\n') break;
        }
    }
}

struct Nodo* buscarCuenta(Nodo* lista, int codCuenta) {
    struct Nodo* actual = lista;
    while (actual) {
        if (actual->cuenta.codigo == codCuenta)
            return actual;
        actual = actual->siguiente;
    }
    return nullptr;
}

void completarDatosCuenta(struct Nodo* cuenta, int fecha, double monto) {
    if (cuenta == nullptr) return;
    double saldoAnterior = cuenta->cuenta.saldo;
    cuenta->cuenta.saldo += monto;
    if (cuenta->cuenta.saldo < 0 and saldoAnterior >= 0) {
        cuenta->cuenta.sobregiro = true;
        cuenta->cuenta.fechaSobregiro = fecha;
    }
}


void emitirReporteCuentas(const char* nombArch, struct Nodo* lista) {
    ofstream arch;
    abrirOutput(arch, nombArch);
    struct Nodo* actual = lista;
    imprimirEncabezado(arch);
    for (int i = 1; actual; i++) {
        imprimirContador(arch, i);
        imprimirCuenta(arch, actual->cuenta);
        actual = actual->siguiente;
    }
    imprimirLinea(arch, '=');
}

void imprimirEncabezado(ofstream& arch) {
    arch << setw(40) << "" << "BANCO DE LOS CLIENTES TP" << endl;
    arch << setw(28) << "" << "LISTADO DE LAS CUENTAS DE AHORROS DE NUESTROS CLIENTES" << endl;
    imprimirLinea(arch, '=');
    arch << left << "No.  "
        << setw(12) << "CUENTA"
        << setw(42) << "CLIENTE"
        << setw(10) << "SALDO"
        << setw(15) << "SOBREGIRADA"
        << "FECHA DEL ULTIMO SOBREGIRO" << endl;
}

void imprimirCuenta(ofstream& arch, const struct Cuenta& c) {
    arch << left
        << setw(12) << c.codigo
        << setw(40) << c.nombre;
    arch << right << setw(10) << c.saldo
        << setw(8) << "" << left;
    if (c.sobregiro) {
        arch << setw(15) << "SI";
        imprimirFecha(arch, c.fechaSobregiro);
    }
    else {
        arch << setw(15) << "NO";
        arch << "--/--/----";
    }
    arch << endl;
}

void eliminarCuentasConSaldoPositivo(struct Nodo*& lista) {
    struct Nodo* actual = lista;
    struct Nodo *anterior = nullptr, *posterior;
    while (actual) {
        posterior = actual->siguiente;
        if (actual->cuenta.saldo > 0) {
            if (anterior == nullptr) lista = posterior;
            else anterior->siguiente = posterior;
            delete actual;
            actual = posterior;
            continue;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
}
