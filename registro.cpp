#include <iostream>
#include <cstring>
using namespace std;

struct Vendedor {
    int cod_vend;
    char nombre_vend[100];
    char nombre_suc[100];
};

int existeCodVend(int valor);
int contarVendedoresEnArchivo();
void leerYOrdenarArchivo();
void registro();
bool verif_suc(const char suc[]);

int main() {
    leerYOrdenarArchivo();
    int i = contarVendedoresEnArchivo();
    if (i >= 15) {
        cout << "La lista esta llena.\n";
    } else {
        cout << "Hay lugar para registrar mas vendedores.\n";
        registro();
    }
    leerYOrdenarArchivo();
    return 0;
}

void registro() {
    int opcion;
    int valor;
    bool salir = false;
    Vendedor v1;

    FILE* archivo = fopen("vendedores.dat", "ab");
    if (archivo == NULL) {
        cout << "Error al abrir el archivo para escritura.";
        return;
    }

    while (!salir) {
        cout << "Nombre del vendedor nuevo: \n";
        cin.getline(v1.nombre_vend, sizeof(v1.nombre_vend));

        do {
            cout << "Nombre de la sucursal a la cual pertenece: \n";
            cin.getline(v1.nombre_suc, sizeof(v1.nombre_suc));
            if (!verif_suc(v1.nombre_suc)) {
                cout << "La sucursal no existe. Intente nuevamente.\n";
            }
        } while (!verif_suc(v1.nombre_suc));

        do {
            cout << "Codigo unico del vendedor: ";
            cin >> valor;
            cin.ignore();
            if (existeCodVend(valor)) {
                cout << "El codigo ya existe. Intente nuevamente.\n";
            }
        } while (existeCodVend(valor));

        v1.cod_vend = valor;

        fwrite(&v1, sizeof(Vendedor), 1, archivo);
        cout << "Se ha guardado correctamente el vendedor!\n";

        cout << "Si quiere ingresar otro vendedor ingrese (1) o si quiere salir ingrese (0)\n";
        cin >> opcion;
        cin.ignore();

        if (opcion == 0) {
            cout << "Saliendo del programa...\n";
            salir = true;
        }
    }

    fclose(archivo);
    cout << "Archivo actualizado exitosamente.\n";
}

bool verif_suc(const char suc[]) {
    char sucursales[3][100] = {"Suc1", "Suc2", "Suc3"};
    for (int i = 0; i < 3; i++) {
        if (strcmp(suc, sucursales[i]) == 0) {
            return true;
        }
    }
    return false;
}

int existeCodVend(int valor) {
    Vendedor vendedor;
    FILE* archivo = fopen("vendedores.dat", "rb");
    if (archivo == NULL) return 0;

    while (fread(&vendedor, sizeof(Vendedor), 1, archivo) == 1) {
        if (vendedor.cod_vend == valor) {
            fclose(archivo);
            return 1;
        }
    }

    fclose(archivo);
    return 0;
}

void leerYOrdenarArchivo() {
    Vendedor vendedores[15];
    int len = 0;

    FILE* archivo = fopen("vendedores.dat", "rb");
    if (archivo == NULL) {
        cout << "Error al abrir el archivo.\n";
        return;
    }

    while (fread(&vendedores[len], sizeof(Vendedor), 1, archivo) == 1 && len < 15) {
        len++;
    }
    fclose(archivo);

    // Mostrar
    cout << "\nLista de vendedores ordenada por codigo:\n";
    for (int i = 0; i < len; i++) {
        cout << "Vendedor: " << vendedores[i].nombre_vend
             << " | Sucursal: " << vendedores[i].nombre_suc
             << " | Codigo: " << vendedores[i].cod_vend << endl;
    }
}

int contarVendedoresEnArchivo() {
    FILE* archivo = fopen("vendedores.dat", "rb");
    if (archivo == NULL) return 0;

    int contador = 0;
    Vendedor vendedor;
    while (fread(&vendedor, sizeof(Vendedor), 1, archivo) == 1) {
        contador++;
    }
    fclose(archivo);
    return contador;
}
