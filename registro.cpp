#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

struct Venta {
    int cod_vend;
    int cod_producto;
    int valor;
    int fecha;
};

struct Vendedor {
    int cod_vend;
    char nombre_vend[100];
    char nombre_suc[100];
};

bool existeCodVendArchivo(int codigo);
void cargarVentas();
void mostrarVentas();

int main() {
    cargarVentas();
    mostrarVentas();
    return 0;
}

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
    FILE* archivo = fopen("ventas_diarias.dat", "ab");
    if (!archivo) {
        cout << "Error al abrir ventas_diarias.dat\n";
        return;
    }

    Venta venta;
    int opcion = 1;

    while (opcion == 1) {
        cout << "\n--- Nueva Venta ---\n";

        do {
            cout << "Ingrese codigo del vendedor (debe existir en vendedores.dat): ";
            cin >> venta.cod_vend;
            if (!existeCodVendArchivo(venta.cod_vend))
                cout << "Codigo no encontrado. Intente otro.\n";
        } while (!existeCodVendArchivo(venta.cod_vend));

        cout << "Ingrese codigo del producto: ";
        cin >> venta.cod_producto;

        cout << "Ingrese monto de la venta: ";
        cin >> venta.valor;

        do {
            cout << "Ingrese fecha (formato AAAAMMDD): ";
            cin >> venta.fecha;
        } while (venta.fecha < 19000101 || venta.fecha > 21001231);

        fwrite(&venta, sizeof(Venta), 1, archivo);
        cout << "Venta guardada.\n";

        cout << "Desea ingresar otra venta? (1: si, 0: no): ";
        cin >> opcion;
    }

    fclose(archivo);
    cout << "\nArchivo ventas_diarias.dat actualizado.\n";
}

void mostrarVentas() {
    FILE* archivo = fopen("ventas_diarias.dat", "rb");
    if (!archivo) {
        cout << "Error al abrir ventas_diarias.dat\n";
        return;
    }

    Venta venta;
    cout << "\nListado de Ventas:\n";
    while (fread(&venta, sizeof(Venta), 1, archivo)) {
        cout << "Fecha: " << venta.fecha
             << " | Vendedor: " << venta.cod_vend
             << " | Producto: " << venta.cod_producto
             << " | Monto: $" << venta.valor << "\n";
    }

    fclose(archivo);
}
