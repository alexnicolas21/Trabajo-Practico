#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

// Estructura de una venta diaria
struct Venta {
    int valor;
    int mes;      // 0-11
    int cod_vend; // se cruza con vendedores.dat
    int region;   // 0-3
};

struct Vendedor {
    char nombre_vend[100];
    char nombre_surc[100];
    int cod_vend;
};

// Prototipos
void cargarVentas();
void mostrarVentas();
bool existeCodVendArchivo(int codigo);

bool existeCodVendArchivo(int codigo) {
    Vendedor vendedor;
    FILE* archivo = fopen("vendedores.dat", "rb");
    if (!archivo) return false;

    while (fread(&vendedor, sizeof(Vendedor), 1, archivo) == 1) {
        if (vendedor.cod_vend == codigo) {
            fclose(archivo);
            return true;
        }
    }
    fclose(archivo);
    return false;
}

void cargarVentas() {
    FILE* archivo = fopen("ventas_diarias.dat", "ab"); // Append binario
    if (!archivo) {
        cout << "❌ Error al abrir ventas_diarias.dat para escritura.\n";
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

        do {
            cout << "Ingrese código del vendedor (debe existir en vendedores.dat): ";
            cin >> venta.cod_vend;
            if (!existeCodVendArchivo(venta.cod_vend))
                cout << "⚠️ Código no encontrado. Intente otro.\n";
        } while (!existeCodVendArchivo(venta.cod_vend));

        do {
            cout << "Ingrese región (0 a 3): ";
            cin >> venta.region;
        } while (venta.region < 0 || venta.region > 3);

        fwrite(&venta, sizeof(Venta), 1, archivo);
        cout << "✅ Venta guardada.\n";

        cout << "¿Desea ingresar otra venta? (1: sí, 0: no): ";
        cin >> opcion;
    }

    fclose(archivo);
    cout << "\n📁 Archivo ventas_diarias.dat actualizado.\n";
}

void mostrarVentas() {
    FILE* archivo = fopen("ventas_diarias.dat", "rb");
    if (!archivo) {
        cout << "❌ Error al abrir ventas_diarias.dat para lectura.\n";
        return;
    }

    Venta venta;
    cout << "\n📊 Listado de Ventas:\n";
    while (fread(&venta, sizeof(Venta), 1, archivo)) {
        cout<< "Venta: $" << venta.valor
            << " | Mes: " << venta.mes
            << " | Cod. Vendedor: " << venta.cod_vend
            << " | Región: " << venta.region << "\n";
    }

    fclose(archivo);
}
