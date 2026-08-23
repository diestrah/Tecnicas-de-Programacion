#include "FuncionesAuxiliares.h"
#define MAX_CAD 200
#define TAM_PAG 140
#define TAM_COD 12
#define TAM_NOM_CLIE 40
#define TAM_NOM_DIST 25
#define TAM_NOM_PLAT 46
#define TAM_DOUB 10
#define TAM_CAT 12
/*
 *  Módulos Secundarios
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

char* leerString(ifstream& arch, char car) {
    char buffer[MAX_CAD], *cadena;
    arch.getline(buffer, MAX_CAD, car);
    if (arch.eof()) return nullptr;
    cadena = new char[strlen(buffer) + 1];
    strcpy(cadena, buffer);
    return cadena;
}

void imprimirLinea(ofstream& arch, char car) {
    arch << setfill(car) << setw(TAM_PAG) << "" << endl << setfill(' ');
}

void swapClientes(struct Cliente &a, struct Cliente &b) {
    struct Cliente temp = a;
    a = b;
    b = temp;
}

void swapPlatos(struct Plato &a, struct Plato &b) {
    struct Plato temp = a;
    a = b;
    b = temp;
}

void imprimirContador(ofstream &arch, int num) {
    arch << right << setfill('0') << setw(3) << num + 1 << setfill(' ');
}

/*
 *  Módulos Principales
 */

void leerPlatosOfrecidos(const char* nombArch, struct Plato* arrPlatos, int& numPlatos) {
    ifstream arch;
    abrirInput(arch, nombArch);
    struct Plato p{};
    // AP-73428,TEQUE�OS,19.50,APERITIVO
    while (true) {
        p.codigo = leerString(arch, ',');
        if (arch.eof()) break;
        p.descripcion = leerString(arch, ',');
        p.precio = leerDouble(arch);
        p.categoria = leerString(arch, '\n');
        arrPlatos[numPlatos] = p;
        numPlatos++;
    }
}

void leerClientes(const char* nombArch, struct Cliente* arrClientes, int& numClientes) {
    ifstream arch;
    abrirInput(arch, nombArch);
    struct Cliente c{};
    // 90367684,CORONEL CHUMPITAZ HELI,LS8594
    while (true) {
        c.dni = leerInt(arch);
        if (arch.eof()) break;
        c.nombre = leerString(arch, ',');
        c.distrito.codigo = leerString(arch, '\n');
        arrClientes[numClientes] = c;
        numClientes++;
    }
}

void leerDistritos(const char* nombArch, struct Distrito* arrDistritos, int& numDistritos) {
    ifstream arch;
    abrirInput(arch, nombArch);
    struct Distrito d{};
    // LN3085,Ancon,NORTE
    while (true) {
        d.codigo = leerString(arch, ',');
        if (arch.eof()) break;
        d.nombre = leerString(arch, ',');
        d.ubicacion = leerString(arch, '\n');
        arrDistritos[numDistritos] = d;
        numDistritos++;
    }
}

void verificarPlatosOfrecidos(const char* nombArch, const struct Plato* arrPlatos, const int numPlatos) {
    ofstream arch;
    abrirOutput(arch, nombArch);
    struct Plato p{};
    arch << left << setw(TAM_COD) << "CODIGO" << setw(TAM_NOM_PLAT) << "DESCRIPCION"
        << right << setw(TAM_DOUB) << "PRECIO" << "   CATEGORIA" << endl;
    for (int i = 0; i < numPlatos; i++) {
        p = arrPlatos[i];
        arch << left << setw(TAM_COD) << p.codigo
            << setw(TAM_NOM_PLAT) << p.descripcion
            << right << setw(TAM_DOUB) << p.precio << "   "
            << left << p.categoria << endl;
    }
}

void verificarClientes(const char* nombArch, const struct Cliente* arrClientes, const int numClientes) {
    ofstream arch;
    abrirOutput(arch, nombArch);
    struct Cliente c{};
    arch << left << setw(TAM_COD) << "DNI" << setw(TAM_NOM_CLIE) << "NOMBRE" << "DISTRITO" << endl;
    for (int i = 0; i < numClientes; i++) {
        c = arrClientes[i];
        arch << left << setw(TAM_COD) << c.dni << setw(TAM_NOM_CLIE) << c.nombre
            << c.distrito.codigo << endl;
    }
}

void verificarDistritos(const char* nombArch, const struct Distrito* arrDistritos, const int numDistritos) {
    ofstream arch;
    abrirOutput(arch, nombArch);
    struct Distrito d{};
    arch << left << setw(TAM_COD) << "CODIGO" << setw(TAM_NOM_DIST) << "NOMBRE DISTRITO" << "UBICACION" << endl;
    for (int i = 0; i < numDistritos; i++) {
        d = arrDistritos[i];
        arch << left << setw(TAM_COD) << d.codigo << setw(TAM_NOM_DIST) << d.nombre
            << d.ubicacion << endl;
    }
}


void leerPedidosYCompletarArrays(const char* nombArch, struct Plato* arrPlatos, const int numPlatos,
                                 struct Cliente* arrClientes, const int numClientes,
                                 const struct Distrito* arrDistritos, const int numDistritos) {
    ifstream arch;
    abrirInput(arch, nombArch);
    int codPedido, dni, cant, pos;
    char* codPlato;
    // 117660      68114999        AP-73428       3
    while (true) {
        arch >> codPedido;
        if (arch.eof()) break;
        arch >> dni >> ws;
        codPlato = leerString(arch, ' ');
        arch >> cant;

        pos = buscarCliente(dni, arrClientes, numClientes);
        if (pos != -1) {
        if (arrClientes[pos].cantidadDePedidos == 0) {
            actualizarDistrito(arrClientes[pos], arrDistritos, numDistritos);
        }
        completarDatosClientes(codPedido, codPlato, cant, arrClientes[pos], arrPlatos, numPlatos);
        }
    }
}

int buscarCliente(const int dni, const struct Cliente* arrClientes, const int numClientes) {
    for (int i = 0; i < numClientes; i++)
        if (dni == arrClientes[i].dni) return i;
    return -1;
}

void actualizarDistrito(struct Cliente& c, const struct Distrito* arrDistritos, int numDistritos) {
    int pos;
    pos = buscarDistrito(c.distrito.codigo, arrDistritos, numDistritos);
    if (pos != -1) {
        c.distrito.nombre = arrDistritos[pos].nombre;
        c.distrito.ubicacion = arrDistritos[pos].ubicacion;
    }
}

int buscarDistrito(char* codDistrito, const struct Distrito* arrDistritos, const int numDistritos) {
    for (int i = 0; i < numDistritos; i++)
        if (strcmp(codDistrito, arrDistritos[i].codigo) == 0) return i;
    return -1;
}

void completarDatosClientes(const int codPedido, const char* codPlato, const int cant,
                            struct Cliente& c, struct Plato* arrPlatos, const int numPlatos) {
    int pos, numPedido;
    pos = buscarPlato(codPlato, arrPlatos, numPlatos);

    if (pos != -1) {
        numPedido = c.cantidadDePedidos;
        c.pedidos[numPedido].codigoPedido = codPedido;
        c.pedidos[numPedido].codigoPlato =  arrPlatos[pos].codigo;
        c.pedidos[numPedido].descripcion = arrPlatos[pos].descripcion;
        c.pedidos[numPedido].categoria = arrPlatos[pos].categoria;
        c.pedidos[numPedido].cantidad = cant;
        c.pedidos[numPedido].precio = arrPlatos[pos].precio;
        c.pedidos[numPedido].subtotal = cant * arrPlatos[pos].precio;
        c.montoTotal += c.pedidos[numPedido].subtotal;
        arrPlatos[pos].cantidad += cant;
        c.cantidadDePedidos++;
    }
}

int buscarPlato(const char* codPlato, const struct Plato* arrPlatos, const int numPlatos) {
    for (int i = 0; i < numPlatos; i++)
        if (strcmp(codPlato, arrPlatos[i].codigo)==0) return i;
    return -1;
}

void ordenarClientes(struct Cliente *arrClientes, const int numClientes) {
    for (int i=0; i<numClientes-1; i++) {
        for (int j=i; j<numClientes; j++) {
            if (strcmp(arrClientes[i].nombre, arrClientes[j].nombre)>0)
                swapClientes(arrClientes[i], arrClientes[j]);
        }
    }
}

void ordenarPlatos(struct Plato *arrPlatos, const int numPlatos) {
    for (int i=0; i<numPlatos-1; i++) {
        for (int j=i; j<numPlatos; j++) {
            if (arrPlatos[i].codigo>arrPlatos[j].codigo or
                arrPlatos[i].codigo==arrPlatos[j].codigo and
                strcmp(arrPlatos[i].codigo, arrPlatos[j].codigo)<0) {
                swapPlatos(arrPlatos[i], arrPlatos[j]);
            }
        }
    }
}

void emitirReporte(const char* nombArch, const struct Cliente* arrClientes, const int numClientes) {
    ofstream arch;
    abrirOutput(arch, nombArch);

    imprimirEncabezado(arch);
    imprimirClientes(arch, arrClientes, numClientes);
}

void imprimirEncabezado(ofstream& arch) {
    arch << setw(50) << "" << "EMPRESA DE REPARTOS A DOMICILIO TP S. A." << endl;
    arch << setw(54) << "" << "RELACION DE PEDIDOS POR CLIENTE" << endl;
    imprimirLinea(arch, '=');
}

void imprimirClientes(ofstream& arch, const struct Cliente* arrClientes, const int numClientes) {
    for (int i=0; i<numClientes; i++) {
        if (arrClientes[i].cantidadDePedidos>0) {
            imprimirSubtitulosClientes(arch, i);
            arch << left << setw(TAM_COD) << arrClientes[i].dni
                << setw(TAM_NOM_CLIE) << arrClientes[i].nombre
                << arrClientes[i].distrito.codigo << "  "
                << setw(TAM_NOM_DIST) << arrClientes[i].distrito.nombre
                << setw(TAM_DOUB) << arrClientes[i].montoTotal << endl;
            imprimirLinea(arch, '-');
            imprimirPedidos(arch, arrClientes[i].pedidos, arrClientes[i].cantidadDePedidos);
        }
    }
}

void imprimirSubtitulosClientes(ofstream& arch, const int i) {
    arch << "CLIENTE No. ";
    imprimirContador(arch, i);
    arch << endl;
    arch << left << setw(TAM_COD) << "DNI"
        << setw(TAM_NOM_CLIE) << "NOMBRE"
        << setw(TAM_NOM_DIST) << "DISTRITO"
        << "     PAGO TOTAL" << endl;
}

void imprimirPedidos(ofstream& arch, const struct PlatoPedido *arrPedidos, const int numPedidos) {
    imprimirSubtitulosPedidos(arch);
    for (int i=0; i<numPedidos; i++) {
        arch << setw(18) << "";
        imprimirContador(arch, i);
        arch << left << "   " << setw(TAM_COD) << arrPedidos[i].codigoPedido
            << setw(TAM_COD) << arrPedidos[i].codigoPlato
            << setw(TAM_NOM_PLAT) << arrPedidos[i].descripcion
            << setw(TAM_CAT) << arrPedidos[i].categoria
            << right << setw(TAM_DOUB) << arrPedidos[i].precio
            << setw(TAM_DOUB) << arrPedidos[i].cantidad
            << setw(TAM_DOUB) << arrPedidos[i].subtotal << endl;
    }
    imprimirLinea(arch, '=');
}

void imprimirSubtitulosPedidos(ofstream& arch) {
    arch << "PEDIDOS REALIZADOS: " << endl;
    arch << setw(18) << "";
    arch << left << "No.   " << setw(TAM_COD) << "PEDIDO"
        << setw(TAM_COD) << "CODIGO"
        << setw(TAM_NOM_PLAT) << "DESCRIPCION"
        << setw(TAM_CAT) << "CATEGORIA"
        << right << setw(TAM_DOUB) << "PRECIO"
        << setw(TAM_DOUB) << "CANTIDAD"
        << setw(TAM_DOUB) << "SUBTOTAL"
        << endl;
}
