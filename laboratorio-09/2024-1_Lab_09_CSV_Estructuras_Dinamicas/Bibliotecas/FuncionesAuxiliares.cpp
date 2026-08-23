#include "FuncionesAuxiliares.h"
#define TAM_PAG 150
#define MAX_CAD 200
#define MAX_VENT 10
#define TAM_COD 12
#define TAM_NOM_TIT 60
#define TAM_NOM_AUT 25
#define TAM_DOUB 12
#define TAM_NOM_CLIE 40

/*
 *  Módulos secundarios
 */

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
    arch << setfill(car) << setw(TAM_PAG) << "" << endl << setfill(' ');
}

void imprimirFecha(ofstream& arch, const struct Fecha f) {
    arch << right << setfill('0')
        << setw(2) << f.dd << '/' << setw(2) << f.mm << '/' << f.aa
        << setfill(' ');
}

void imprimirContador(ofstream& arch, const int contador, const int formato) {
    arch << right << setfill('0') << setw(formato) << contador + 1
        << setfill(' ');
}

void swapLibros(struct Libro& a, struct Libro& b) {
    struct Libro temp = a;
    a = b;
    b = temp;
}

/*
 *  Módulos principales
 */

void leerClientes(const char* nombArch, struct Cliente* arrClientes, int& numClientes) {
    ifstream arch;
    abrirInput(arch, nombArch);
    struct Cliente c{};

    // 54393647,Reyes Tang Edward
    while (true) {
        c.dni = leerInt(arch);
        if (arch.eof()) break;
        c.nombre = leerString(arch, '\n');
        arrClientes[numClientes] = c;
        numClientes++;
    }
}

void leerLibros(const char* nombArch, struct Libro* arrLibros, int& numLibros) {
    ifstream arch;
    abrirInput(arch, nombArch);
    struct Libro l{};

    // SFZ1256,La Iliada,Homero,123.04
    while (true) {
        l = {};
        l.codigo = leerString(arch, ',');
        if (arch.eof()) break;
        l.titulo = leerString(arch, ',');
        l.autor = leerString(arch, ',');
        l.precio = leerDouble(arch);
        l.ventas = new struct Venta[MAX_VENT];
        arrLibros[numLibros] = l;
        numLibros++;
    }
}

void leerVentas(const char* nombArch, struct Libro* arrLibros, const int numLibros) {
    ifstream arch;
    abrirInput(arch, nombArch);
    struct Venta v{};
    char* codLibro;
    int pos, numVentas;

    // CRY6839,34460612,15/10/2023,93
    while (true) {
        codLibro = leerString(arch, ',');
        if (arch.eof()) break;
        v.dni = leerInt(arch);
        v.fecha = leerFecha(arch);
        v.calificacion = leerInt(arch);

        pos = buscarLibro(codLibro, arrLibros, numLibros);
        if (pos != -1) {
            numVentas = arrLibros[pos].librosVendidos;
            arrLibros[pos].ventas[numVentas] = v;
            arrLibros[pos].librosVendidos++;
        }
    }
}

int buscarLibro(const char* codLibro, const struct Libro* arrLibros, const int numLibros) {
    for (int i = 0; i < numLibros; i++)
        if (strcmp(codLibro, arrLibros[i].codigo) == 0) return i;
    return -1;
}

void determinarRankings(struct Libro* arrLibros, const int numLibros) {
    double promPuntaje;
    for (int i = 0; i < numLibros; i++) {
        arrLibros[i].sumaDeCalificaciones = 0;
        for (int j = 0; j < arrLibros[i].librosVendidos; j++) {
            arrLibros[i].sumaDeCalificaciones += arrLibros[i].ventas[j].calificacion;
        }

        if (arrLibros[i].librosVendidos>0) {
        promPuntaje = (double)arrLibros[i].sumaDeCalificaciones / arrLibros[i].librosVendidos;

        }

        if (promPuntaje < 25) {
            arrLibros[i].ranking = 1;
        }
        else if (25 <= promPuntaje and promPuntaje < 50) {
            arrLibros[i].ranking = 2;
        }
        else if (50 <= promPuntaje and promPuntaje < 75) {
            arrLibros[i].ranking = 3;
        }
        else if (75 <= promPuntaje) {
            arrLibros[i].ranking = 5;
        }
        else {
            arrLibros[i].ranking = 0;
        }
    }
}

void ordenarLibrosPorRankingYTitulo(struct Libro* arrLibros, const int numLibros) {
    for (int i = 0; i < numLibros - 1; i++) {
        for (int j = i; j < numLibros; j++) {
            if (arrLibros[i].ranking < arrLibros[j].ranking or
                arrLibros[i].ranking == arrLibros[j].ranking and strcmp(arrLibros[i].titulo, arrLibros[j].titulo) < 0) {
                swap(arrLibros[i], arrLibros[j]);
            }
        }
    }
}

void emitirReporte(const char* nombArch, const struct Cliente* arrClientes, const int numClientes,
                   const struct Libro* arrLibros, const int numLibros) {
    ofstream arch;
    abrirOutput(arch, nombArch);

    imprimirEncabezado(arch);
    imprimirLibrosYVentas(arch, arrClientes, numClientes, arrLibros, numLibros);
}

void imprimirEncabezado(ofstream& arch) {
    arch << setw(64) << "" << "LIBRERIA PUCP-TP" << endl;
    arch << setw(55) << "" << "RESULTADO DE LAS VENTAS REALIZADAS" << endl;
}

void imprimirLibrosYVentas(ofstream& arch, const struct Cliente* arrClientes, const int numClientes,
                           const struct Libro* arrLibros, const int numLibros) {
    for (int i = 0; i < numLibros; i++) {
        imprimirSubtitulosLibros(arch, i);
        arch << left << setw(5) << ""
            << setw(TAM_COD) << arrLibros[i].codigo
            << setw(TAM_NOM_TIT) << arrLibros[i].titulo
            << setw(TAM_NOM_AUT) << arrLibros[i].autor
            << right << setw(TAM_DOUB) << arrLibros[i].precio
            << setw(TAM_DOUB) << arrLibros[i].librosVendidos
            << setw(TAM_DOUB) << arrLibros[i].ranking << endl;
        if (arrLibros[i].librosVendidos > 0) {
            imprimirVentas(arch, arrClientes, numClientes, arrLibros[i].ventas, arrLibros[i].librosVendidos);
        }
    }
}

void imprimirSubtitulosLibros(ofstream& arch, const int i) {
    imprimirLinea(arch, '=');
    arch << "LIBRO NO. ";
    imprimirContador(arch, i, 3);
    arch << endl;
    arch << left << setw(5) << ""
        << setw(TAM_COD) << "CODIGO"
        << setw(TAM_NOM_TIT) << "TITULO"
        << setw(TAM_NOM_AUT) << "AUTOR"
        << right << setw(TAM_DOUB) << "PRECIO"
        << "  LIBROS VENDIDOS"
        << "  RANKINGS" << endl;
}

void imprimirVentas(ofstream& arch, const struct Cliente* arrClientes, const int numClientes,
                    const struct Venta* arrVentas, const int numVentas) {
    int pos;

    imprimirLinea(arch, '-');
    arch << left << setw(5) << "" << "VENTAS REALIZADAS:" << endl;
    arch << setw(5) << "" << "No.  "
        << setw(TAM_COD) << "DNI"
        << setw(TAM_NOM_CLIE) << "NOMBRE" << "CALIFICACION" << endl;

    for (int i = 0; i < numVentas; i++) {
        pos = buscarCliente(arrVentas[i].dni, arrClientes, numClientes);
        if (pos != -1) {
            arch << setw(5) << "";
            imprimirContador(arch, i, 2);
            arch << left << "   " << setw(TAM_COD) << arrVentas[i].dni
                << setw(TAM_NOM_CLIE) << arrClientes[pos].nombre
                << setw(TAM_DOUB) << arrVentas[i].calificacion << endl;
        }
    }
}

int buscarCliente(const int dni, const struct Cliente* arrClientes, const int numClientes) {
    for (int i = 0; i < numClientes; i++) {
        if (arrClientes[i].dni == dni) return i;
    }
    return -1;
}
