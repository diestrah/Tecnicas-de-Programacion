#ifndef INC_2024_2_LAB_08_CSV_ESTRUCTURAS_DINAMICAS_PLATOPEDIDO_H
#define INC_2024_2_LAB_08_CSV_ESTRUCTURAS_DINAMICAS_PLATOPEDIDO_H

struct PlatoPedido{
    int codigoPedido;
    char* codigoPlato;
    char* descripcion;
    char* categoria; // esto lo agregué
    int cantidad;
    double precio;
    double subtotal;
};

#endif //INC_2024_2_LAB_08_CSV_ESTRUCTURAS_DINAMICAS_PLATOPEDIDO_H
