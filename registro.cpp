#include <iostream>
using namespace std;

struct Vendedor
{
    char nombre_vend[100];
    char nombre_surc[100];
    int cod_vend;
};
int existeCodVend(Vendedor vendedores[15][3], int valor);
void registro();
void leerArchivo();

int main()
{
    registro();
    leerArchivo();
    return 0;
}

void registro(){
    int opcion;
    int valor;
    bool salir = false;
    Vendedor vendedores[15][3];

    string arr1[3] = {"San Justo", "Moron", "Tapiales"};
    
    FILE* archivo = fopen("vendedores.dat", "ab");  // Modo binario (append)
    if (archivo == NULL) {
    cout << "Error al abrir el archivo para escritura.";
    }
    // Carga de vendedor
    for(int i = 0; i < 15 && !salir; i++) {
        for(int j = 0; j < 3 && !salir ; j++) {
            cout << "Ingrese el elemento [" << i << "][" << j << "]: \n";
            cout << "Nombre del vendedor nuevo: \n";
            cin.getline(vendedores[i][j].nombre_vend, sizeof(vendedores[i][j].nombre_vend));
            cout << "Nombre de la sucursal a la cual pertenece: \n";
            cin.getline(vendedores[i][j].nombre_surc, sizeof(vendedores[i][j].nombre_surc));

            // Verifica que el codigo de vendedor sea unico
            do {
                cout << "Codigo unico del vendedor: ";
                cin >> valor;
                cin.ignore();
                if (existeCodVend(vendedores, valor)) {
                    cout << "El codigo ya existe. Intente nuevamente.\n";
                }
            } while (existeCodVend(vendedores, valor) == 1); // Si existe retorna 1 y luego te pide otro.

            vendedores[i][j].cod_vend = valor;
            cout << "Se ha guardado correctamente el vendedor! \n";
     
            // Guardar los datos en archivo binario
            if (archivo != NULL) {
                fwrite(&vendedores[i][j], sizeof(Vendedor), 1, archivo);  // Escribir un vendedor
            } else {
                cout << "No se pudo crear el archivo.\n";
            }

            cout << "Si quiere ingresar otro vendedor ingrese (1) o si quiere salir ingrese (0) \n";
            cin >> opcion;
            cin.ignore();
            if (opcion == 0) {
                cout << "Saliendo del programa... \n";
                salir = true;
                break; 
            }
        }
    } 

    fclose(archivo);
    cout << "Archivo actualizado exitosamente.\n";
}

int existeCodVend(Vendedor vendedores[15][3], int valor){
    for(int i = 0; i < 15; i++) {
        for(int j = 0; j < 3; j++) {
            if (vendedores[i][j].cod_vend == valor) {
                return 1;  // Si el código ya existe
            } 
        }
    }
    return 0;  // Si el código no existe
}

void leerArchivo() {
    FILE* archivo = fopen("vendedores.dat", "rb");

    if (archivo == NULL) {
        cout << "Error al abrir el archivo";
    }
    cout << "Lista de vendedores: \n";
    Vendedor vendedor;
    while (fread(&vendedor, sizeof(Vendedor), 1, archivo) == 1) {
        cout << "Vendedor: " << vendedor.nombre_vend << ", ";
        cout << "Sucursal: " << vendedor.nombre_surc << ", ";
        cout << "Codigo: " << vendedor.cod_vend << endl;
    }

    fclose(archivo);
}
