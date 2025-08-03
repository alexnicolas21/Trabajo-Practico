#include <iostream>
#include <cstdio>
using namespace std;

// Estructura de una venta diaria
struct Venta {
    int valor;
    int mes;      // 0-11
    int cod_vend; // se cruza con vendedores.dat
    int region;   // 0-3
};

// ===== FUNCIONES =====
void cargarVentas();
void mostrarVentas();

void cargarVentas() {
    FILE* archivo = fopen("ventas_diarias.dat", "ab"); // Append binario
    if (!archivo) {
        cout << "Error al abrir ventas_diarias.dat para escritura.\n";
        return;
    }

    Venta venta;
    int opcion = 1;
    while (opcion == 1) {
        cout << "\n--- Nueva Venta ---\n";

        cout << "Ingrese monto de la venta: ";
        cin >> venta.valor;

        do {
            cout << "Ingrese número de mes (0 a 11): ";
            cin >> venta.mes;
        } while (venta.mes < 0 || venta.mes > 11);

        cout << "Ingrese código del vendedor (debe existir en vendedores.dat): ";
        cin >> venta.cod_vend;

        do {
            cout << "Ingrese región (0 a 3): ";
            cin >> venta.region;
        } while (venta.region < 0 || venta.region > 3);

        fwrite(&venta, sizeof(Venta), 1, archivo);
        cout << "Venta guardada.\n";

        cout << "\n¿Desea ingresar otra venta? (1: sí, 0: no): ";
        cin >> opcion;
    }

    fclose(archivo);
    cout << "\nArchivo ventas_diarias.dat actualizado.\n";
}

void mostrarVentas() {
    FILE* archivo = fopen("ventas_diarias.dat", "rb");
    if (!archivo) {
        cout << "Error al abrir ventas_diarias.dat para lectura.\n";
        return;
    }

    Venta venta;
    cout << "\n📊 Listado de Ventas:\n";
    while (fread(&venta, sizeof(Venta), 1, archivo)) {
        cout << "Venta: $" << venta.valor
             << " | Mes: " << venta.mes
             << " | Cod. Vendedor: " << venta.cod_vend
             << " | Región: " << venta.region << "\n";
    }

    fclose(archivo);
}
