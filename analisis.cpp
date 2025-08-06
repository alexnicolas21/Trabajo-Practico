#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

struct Vendedor {
    int cod_vend;
    char nombre_vend[100];
    char nombre_suc[100];
};

struct Venta {
    int cod_vend;
    int cod_producto;
    int valor;
    int fecha;
};

int main() {
    Vendedor vendedores[50];
    int cantVendedores = 0;

    FILE* archVend = fopen("vendedores.dat", "rb");
    if (!archVend) {
        cout << "No se pudo abrir vendedores.dat" << endl;
        return 1;
    }
    while (fread(&vendedores[cantVendedores], sizeof(Vendedor), 1, archVend) == 1) {
        cantVendedores++;
    }
    fclose(archVend);

    Venta ventas[1000];
    int cantVentas = 0;

    FILE* archVentas = fopen("ventas_diarias.dat", "rb");
    if (!archVentas) {
        cout << "No se pudo abrir ventas_diarias.dat" << endl;
        return 1;
    }
    while (fread(&ventas[cantVentas], sizeof(Venta), 1, archVentas) == 1) {
        cantVentas++;
    }
    fclose(archVentas);

    // Vendedor que más dinero generó
    int totPorVendedor[50] = {0};
    for (int i = 0; i < cantVentas; i++) {
        for (int j = 0; j < cantVendedores; j++) {
            if (ventas[i].cod_vend == vendedores[j].cod_vend) {
                totPorVendedor[j] += ventas[i].valor;
                break;
            }
        }
    }

    int posMaxVend = 0;
    for (int i = 1; i < cantVendedores; i++) {
        if (totPorVendedor[i] > totPorVendedor[posMaxVend]) {
            posMaxVend = i;
        }
    }

    cout << "\nVendedor que mas dinero genero: " << vendedores[posMaxVend].nombre_vend
         << "  $" << totPorVendedor[posMaxVend] << endl;

    // Sucursal que más dinero generó
    char sucursales[3][100] = {"Suc1", "Suc2", "Suc3"};
    int totPorSucursal[3] = {0};

    for (int i = 0; i < cantVendedores; i++) {
        int suc = 0;
        for (int j = 0; j < 3; j++) {
            if (strcmp(vendedores[i].nombre_suc, sucursales[j]) == 0) {
                suc = j;
                break;
            }
        }
        totPorSucursal[suc] += totPorVendedor[i];
    }

    int posMaxSuc = 0;
    for (int i = 1; i < 3; i++) {
        if (totPorSucursal[i] > totPorSucursal[posMaxSuc]) {
            posMaxSuc = i;
        }
    }

    cout << "\nSucursal que mas dinero genero: " << sucursales[posMaxSuc]
         << "  $" << totPorSucursal[posMaxSuc] << endl;

    // Ranking de productos
    const int MAX_PROD = 1000;
    int productos[MAX_PROD] = {0};
    int codigos[MAX_PROD];
    for (int i = 0; i < MAX_PROD; i++) codigos[i] = i;

    for (int i = 0; i < cantVentas; i++) {
        int cod = ventas[i].cod_producto;
        if (cod >= 0 && cod < MAX_PROD) {
            productos[cod]++;
        }
    }

    for (int i = 0; i < MAX_PROD - 1; i++) {
        for (int j = i + 1; j < MAX_PROD; j++) {
            if (productos[j] > productos[i]) {
                swap(productos[i], productos[j]);
                swap(codigos[i], codigos[j]);
            }
        }
    }

    cout << "\nRanking de productos más vendidos:\n";
    int mostrados = 0;
    for (int i = 0; i < MAX_PROD && mostrados < 10; i++) {
        if (productos[i] > 0) {
            cout << "Producto " << codigos[i] << " - Vendido " << productos[i] << " veces\n";
            mostrados++;
        }
    }

    return 0;
}
