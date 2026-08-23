#include "FuncionesAuxiliares.h"

/*
 *  Funciones secundarias
 */
ifstream abrirInput(const char* nombArch) {
    ifstream arch(nombArch, ios::in);
    if (not arch.is_open()) {
        cerr << "ERROR: No se abrio el archivo " << nombArch << endl;
        exit(EXIT_FAILURE);
    }
    return arch;
}

ofstream abrirOutput(const char* nombArch) {
    ofstream arch(nombArch, ios::out);
    if (not arch.is_open()) {
        cerr << "ERROR: No se abrio el archivo " << nombArch << endl;
        exit(EXIT_FAILURE);
    }
    arch.precision(2);
    arch << fixed;
    return arch;
}

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
    int hh = leerInt(arch);
    int mm = leerInt(arch);
    int ss = leerInt(arch);
    return hh * 3600 + mm * 60 + ss;
}

char* leerString(ifstream& arch, char delim) {
    char buffer[MAX_CAD], *cadena;
    arch.getline(buffer, MAX_CAD, delim);
    if (arch.eof()) return nullptr;
    cadena = new char[strlen(buffer) + 1];
    strcpy(cadena, buffer);
    return cadena;
}

void imprimirLinea(ofstream& arch, char car) {
    arch << setfill(car);
    arch << setw(TAM_PAG) << "" << endl;
    arch << setfill(' ');
}

void imprimirHora(ofstream& arch, int hora) {
    int ss = hora % 60;
    int mm = hora / 60 % 60;
    int hh = hora / 3600;
    arch << right << setfill('0');
    arch << setw(2) << hh << ':' << setw(2) << mm << ':' << setw(2) << ss;
    arch << setfill(' ') << endl;
}

/*
*  Funciones principales
*/

// Sección leer "Categorias.csv"
void leerCategorias(const char* nombArch, struct Nodo*& lista) {
    lista = nullptr;
    ifstream arch = abrirInput(nombArch);
    // UM163F47,just chatting,Casual conversations; reactions; and hangouts without a main game.
    struct Categoria c{};
    while (true) {
        c.codigo = leerString(arch, ',');
        if (arch.eof()) break;
        c.nombre = leerString(arch, ',');
        c.descripcion = leerString(arch, '\n');
        insertarCategoria(lista, c);
    }
}

void insertarCategoria(struct Nodo*& lista, const struct Categoria& c) {
    struct Nodo *anterior = nullptr, *actual = lista;
    struct Nodo* nuevo = new Nodo();
    nuevo->categoria = c;
    while (actual) {
        if (strcmp(c.codigo, actual->categoria.codigo) < 0) break;
        anterior = actual;
        actual = actual->siguiente;
    }
    nuevo->siguiente = actual;
    if (anterior != nullptr) anterior->siguiente = nuevo;
    else lista = nuevo;
}

// Sección Impresión de reporte
void emitirReporte(const char* nombArch, struct Nodo* lista) {
    ofstream arch = abrirOutput(nombArch);
    struct Nodo* actual = lista;
    arch << setw(20) << "" << "REPORTE POR CATEGORIAS: " << endl;
    while (actual) {
        imprimirLinea(arch, '=');
        imprimirCategoria(arch, actual->categoria);
        actual = actual->siguiente;
    }
}

void imprimirCategoria(ofstream& arch, const struct Categoria& c) {
    imprimirDescripcionCategoria(arch, c);
    if (c.cantidadDeReproducciones > 0)
        imprimirInformacionReproducciones(arch, c);
}

void imprimirDescripcionCategoria(ofstream& arch, const struct Categoria& c) {
    arch << left << setw(18) << "Codigo:" << c.codigo << endl;
    arch << setw(18) << "Nombre:" << c.nombre << endl;
    arch << setw(18) << "Descripcion:" << c.descripcion << endl;
    imprimirLinea(arch, '-');
}

void imprimirInformacionReproducciones(ofstream& arch, const struct Categoria& c) {
    arch << "INFORMACION DE LAS REPRODUCCIONES:" << endl;
    arch << "DURACION MAXIMA:" << endl;
    arch << "NOMBRE DEL CANAL: " << c.canalConDuracionMaxima << endl;
    arch << "DURACION: ";
    imprimirHora(arch, c.duracionMaxima);
    imprimirLinea(arch, '-');
    imprimirArrayDropOff(arch, c.arrDropOff, c.cantidadDeReproducciones);
    arch << "PROMEDIO DE DROP-OFF:" << right << setw(13) << c.promedioDropOff << endl;
    arch << "TIEMPO DE DURACION TOTAL: ";
    imprimirHora(arch, c.duracionTotal);
}

void imprimirArrayDropOff(ofstream& arch, const double* arrDropOff, int cant) {
    arch << "LISTA DE DROP-OFF: ";
    for (int i = 0; i < cant; i++) {
        arch << " " << arrDropOff[i] << " ";
    }
    arch << endl;
}

// Sección leer "StreamsReproducidos.csv"
void leerStreams(const char* nombArch, struct Nodo* lista) {
    ifstream arch = abrirInput(nombArch);
    // ZT132U54,Sardoche,4.41,1:41:48
    while (true) {
        char* codigo = leerString(arch, ',');
        if (arch.eof()) break;
        struct Nodo* nodoCat = buscarCategoria(lista, codigo);
        if (nodoCat != nullptr)
            completarDatosCategoria(arch, nodoCat->categoria);
        else
            while (arch.get() != '\n');
    }
}

struct Nodo* buscarCategoria(struct Nodo* lista, char* codigo) {
    struct Nodo* actual = lista;
    while (actual) {
        if (strcmp(codigo, actual->categoria.codigo) == 0) return actual;
        actual = actual->siguiente;
    }
    return nullptr;
}

void completarDatosCategoria(ifstream& arch, struct Categoria& c) {
    // Sardoche,4.41,1:41:48
    char* nombre = leerString(arch, ',');
    double dropOff = leerDouble(arch);
    int duracion = leerDuracion(arch);
    if (duracion > c.duracionMaxima) {
        c.canalConDuracionMaxima = nombre;
        c.duracionMaxima = duracion;
    }
    c.arrDropOff[c.cantidadDeReproducciones] = dropOff;
    c.duracionTotal += duracion;
    c.cantidadDeReproducciones++;
}

// Sección calcular promedio dropOff
void calcularDropOff(struct Nodo* lista) {
    struct Nodo* actual = lista;
    while (actual) {
        calcularPromedio(actual->categoria);
        actual = actual->siguiente;
    }
}

void calcularPromedio(struct Categoria& c) {
    // validamos que tenga reproducciones (evitamos división por cero)
    if (c.cantidadDeReproducciones == 0) return;
    double sumaDropOff = 0;
    for (int i = 0; i < c.cantidadDeReproducciones; i++)
        sumaDropOff += c.arrDropOff[i];
    c.promedioDropOff = sumaDropOff / c.cantidadDeReproducciones;
}

// Sección eliminar categorias con dropOff < 3.5
void eliminarMenoresDropOff(struct Nodo*& lista) {
    struct Nodo* actual = lista;
    struct Nodo* anterior = nullptr;

    while (actual) {
        if (actual->categoria.promedioDropOff < 3.5) {
            struct Nodo* eliminar = actual;
            actual = actual->siguiente;

            if (anterior == nullptr)lista = actual;
            else anterior->siguiente = actual;

            delete eliminar;
        } else {
            anterior = actual;
            actual = actual->siguiente;
        }
    }
}
