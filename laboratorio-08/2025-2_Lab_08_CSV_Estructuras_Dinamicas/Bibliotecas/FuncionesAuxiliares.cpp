#include "FuncionesAuxiliares.h"
#include "Categoria.h"
#include "Reproduccion.h"

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

char* leerString(ifstream& arch, char delim) {
    char buffer[MAX_CAD], *cadena;
    arch.getline(buffer, MAX_CAD, delim);
    if (arch.eof()) return nullptr;
    cadena = new char[strlen(buffer) + 1];
    strcpy(cadena, buffer);
    return cadena;
}

int leerDuracion(ifstream& arch) {
    int hh, mm, ss;
    hh = leerInt(arch);
    mm = leerInt(arch);
    ss = leerInt(arch);
    return hh * 3600 + mm * 60 + ss;
}

// Funciones ayuda de impresión
void imprimirDuracion(ofstream& arch, int duracion) {
    int hh, mm, ss;
    hh = duracion / 3600;
    mm = duracion / 60 % 60;
    ss = duracion % 60;
    arch << right << setfill('0')
        << setw(2) << hh << ":" << setw(2) << mm << ":" << setw(2) << ss
        << setfill(' ');
}

void imprimirLinea(ofstream& arch, char car) {
    arch << setfill(car) << setw(TAM_PAG) << "" << endl
        << setfill(' ');
}

/*------------------------------------------------------------------*/
// Funciones principales --------------------------------------------
/*------------------------------------------------------------------*/
// Función 1: leer Categorias.csv y guardar los datos en strucs
void leerCategorias(const char* nombArch, struct Categoria* arrCategorias, int& numCate) {
    ifstream arch = abrirInput(nombArch);
    // En lugar de crear muchas variables, utilizamos un struct que ya posea esas variables
    struct Categoria c{};
    // TZ196V36,grand theft auto v,Open-world gameplay: GTA Online missions
    while (true) {
        c.codigo = leerString(arch, ',');
        if (arch.eof()) break;
        c.nombre = leerString(arch, ',');
        c.descripcion = leerString(arch, '\n');
        c.reproducciones = new struct Reproduccion[MAX_REPROD]{};
        arrCategorias[numCate] = c;
        numCate++;
    }
}

// Función 2: leer StreamsReproducidos.csv y guardar los datos en structs
void leerStreams(const char* nombArch, struct Categoria* arrCategorias, int numCate) {
    ifstream arch = abrirInput(nombArch);
    char* codigo;
    int pos;
    struct Reproduccion r{};
    // Anomaly,VG156H76,2.065,00:11:23
    while (true) {
        r.canal = leerString(arch, ',');
        if (arch.eof()) break;
        codigo = leerString(arch, ',');
        r.rating = leerDouble(arch);
        r.duracion = leerDuracion(arch);
        pos = buscarCategoria(arrCategorias, codigo, numCate);
        if (pos != -1) {
            insertarReproduccion(arrCategorias[pos], r);
        }
    }
}

int buscarCategoria(const struct Categoria* arrCategorias, char* codigo, int numCate) {
    for (int i = 0; i < numCate; i++)
        if (strcmp(codigo, arrCategorias[i].codigo) == 0) return i;
    return -1;
}

void insertarReproduccion(struct Categoria& c, const struct Reproduccion& r) {
    int numReprod = c.numReproducciones;
    c.reproducciones[numReprod] = r;
    c.numReproducciones++;
}

// Función 3: 0rdenar arrays ascendentemente por nombre de categoría
void ordenarArray(struct Categoria* arrCategorias, int numCate) {
    for (int i = 0; i < numCate - 1; i++)
        for (int j = i + 1; j < numCate; j++) {
            if (strcmp(arrCategorias[i].nombre, arrCategorias[j].nombre) > 0)
                cambiarStruct(arrCategorias[i], arrCategorias[j]);
        }
}

void cambiarStruct(struct Categoria& i, struct Categoria& j) {
    struct Categoria temp = i;
    i = j;
    j = temp;
}

// Función 4: leer ComentariosAlCanal.csv y almacenar data en los arreglos correspondientes
void leerComentarios(const char* nombArch, struct Categoria* arrCategorias, int numCate) {
    ifstream arch = abrirInput(nombArch);
    char *canal, *comentario;
    // MOONMOON,they call me unexpected
    while (true) {
        canal = leerString(arch, ',');
        if (arch.eof()) break;
        comentario = leerString(arch, '\n');
        recorrerCanalesEInsertarComentario(arrCategorias, canal, comentario, numCate);
    }
}

void recorrerCanalesEInsertarComentario(struct Categoria* arrCategorias, char* canal, char* comentario, int numCate) {
    int numReprod;
    for (int i = 0; i < numCate; i++) {
        numReprod = arrCategorias[i].numReproducciones;
        insertarComentarioEnCanal(arrCategorias[i], canal, comentario, numReprod);
    }
}

void insertarComentarioEnCanal(struct Categoria& c, char* canal, char* comentario, int numReprod) {
    int numComent;
    for (int i = 0; i < numReprod; i++) {
        if (strcmp(canal, c.reproducciones[i].canal) == 0) {
            numComent = c.reproducciones[i].numComentarios;
            c.reproducciones[i].comentarios[numComent] = comentario;
            c.reproducciones[i].numComentarios++;
        }
    }
}

// Funcion 5: Impresión de la data adaptada a cada parte del enunciado
void verificarCategorias(const char* nombArch, const struct Categoria* arrCategorias, int numCate) {
    ofstream arch = abrirOutput(nombArch);
    struct Categoria c{};
    // Encabezado
    arch << setw(30) << "" << "REPORTE POR CATEGORIAS" << endl;
    // Impresión de la zona roja
    for (int i = 0; i < numCate; i++) {
        c = arrCategorias[i];
        imprimirLinea(arch, '=');
        arch << left << setw(TAM_SUB_CAT) << "Codigo:" << c.codigo << endl
            << setw(TAM_SUB_CAT) << "Nombre" << c.nombre << endl
            << setw(TAM_SUB_CAT) << "Descripcion :" << c.descripcion << endl;
        imprimirLinea(arch, '-');
        // Condición para imprimir la zona azul
        if (c.numReproducciones > 0) {
            imprimirReproducciones(arch, c);
        }
    }
}

void imprimirReproducciones(ofstream& arch, const struct Categoria& c) {
    struct Reproduccion r{};
    arch << "REPRODUCCIONES:" << endl;
    for (int i = 0; i < c.numReproducciones; i++) {
        r = c.reproducciones[i];
        arch << left << "CANAL: " << setw(TAM_NOM_CAN) << r.canal
            << "RATING: " << right << setw(4) << r.rating
            << "    DURACION: ";
        imprimirDuracion(arch, r.duracion);
        arch << endl;
        // Condición para imprimir la zona verde
        if (c.reproducciones[i].numComentarios > 0) {
            imprimirComentarios(arch, c.reproducciones[i]);
        }
    }
}

void imprimirComentarios(ofstream& arch, const struct Reproduccion& r) {
    arch << "   COMENTARIOS:" << endl;
    for (int i = 0; i < r.numComentarios; i++) {
        arch << "   - " << r.comentarios[i] << endl;
    }
}
