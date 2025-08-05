#include <iostream>
#include <cstring>
using namespace std;

struct Vendedor
{
    char nombre_vend[100];
    char nombre_suc[100];
    int cod_vend;
};

int existeCodVend(int valor);
void ordenamiento_De_Vendedores(Vendedor vend[15], int len);
int contarVendedoresEnArchivo();
void leerYOrdenarArchivo();
void registro();
void leerArchivo();
bool verif_suc( Vendedor v);
int main()
{   
    leerYOrdenarArchivo();
    int i = contarVendedoresEnArchivo();
    if (i >= 15)
    {
        cout << "La lista esta llena.\n";
    }else{
    cout << "Hay lugar para registrar mas vendedores.\n";
    registro();
    }
    leerYOrdenarArchivo();
    return 0;
}

void registro(){
    int opcion;
    int valor;
    int i = 0; 
    bool sucursal_valida;
    bool salir = false;
    Vendedor v1;
    Vendedor vendedores[15];
     
     int j = contarVendedoresEnArchivo();

      if (j >= 15) {
        cout << "La lista ya está llena.\n";
        return;
      }  


    FILE* archivo = fopen("vendedores.dat", "ab");  // Modo binario (append)
    if (archivo == NULL) {
    cout << "Error al abrir el archivo para escritura.";
    }
    // Carga de vendedor
    while (!salir){
            cout << "Nombre del vendedor nuevo: \n";
            cin.getline(vendedores[i].nombre_vend, sizeof(vendedores[i].nombre_vend));


            do
            {
            cout << "Nombre de la sucursal a la cual pertenece: \n";
            cin.getline(v1.nombre_suc, sizeof(v1.nombre_suc));
            sucursal_valida = verif_suc(v1);
            if (!sucursal_valida) {
            cout << "La sucursal no existe. Intente nuevamente.\n";
            }
            } while (!sucursal_valida);
        
            strcpy(vendedores[i].nombre_suc, v1.nombre_suc);

            // Verifica que el codigo de vendedor sea unico
            do {
                cout << "Codigo unico del vendedor: ";
                cin >> valor;
                cin.ignore();
                if (existeCodVend(valor)) {
                    cout << "El codigo ya existe. Intente nuevamente.\n";
                }
            } while (existeCodVend(valor) == 1); // Si existe retorna 1 y luego te pide otro.

            vendedores[i].cod_vend = valor;
            cout << "Se ha guardado correctamente el vendedor! \n";
    
            // Guardar los datos en archivo binario
            if (archivo != NULL) {
                fwrite(&vendedores[i], sizeof(Vendedor), 1, archivo);  // Escribir un vendedor
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

            i++;
}
    fclose(archivo);
    cout << "Archivo actualizado exitosamente.\n";
}

bool verif_suc( Vendedor v){
    char sucursales[3][100] = {"Suc1", "Suc2", "Suc3"};
    
    for (int i = 0; i < 3; i++) {
        if (strcmp(v.nombre_suc, sucursales[i]) == 0) {
            return true;
        }
    }
    return false;
}

int existeCodVend(int valor){
    Vendedor vendedores;
    FILE* archivo = fopen("vendedores.dat", "rb");
        if (archivo == NULL) {
        cout << "Error al abrir el archivo para escritura.\n";
        }
    while (fread(&vendedores, sizeof(Vendedor), 1, archivo) == 1) {
        if (vendedores.cod_vend == valor) {
            fclose(archivo);
            return 1; // Código ya existe
        }
    }
    fclose(archivo);
    return 0;  // Si el código no existe retorna 0
} 

void leerYOrdenarArchivo() {
    Vendedor vendedores[15];
    int len = 0;

    FILE* archivo = fopen("vendedores.dat", "rb");
    if (archivo == NULL) {
        cout << "Error al abrir el archivo.\n";
        return;
    }

    // Leer vendedores del archivo
    while (fread(&vendedores[len], sizeof(Vendedor), 1, archivo) == 1 && len < 15) {
        len++;
    }
    fclose(archivo);

    // Ordenar
    ordenamiento_De_Vendedores(vendedores, len);

    // Mostrar
    cout << "\nLista de vendedores ordenada por codigo:\n";
    for (int i = 0; i < len; i++) {
        cout << "Vendedor: " << vendedores[i].nombre_vend << " | ";
        cout << "Sucursal: " << vendedores[i].nombre_suc << " | ";
        cout << "Codigo: " << vendedores[i].cod_vend << endl;
    }
}
// Ordenamiento simple
void ordenamiento_De_Vendedores(Vendedor vend[15], int len) {
       for (int i = 0; i < len - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < len; j++) {
         if (vend[j].cod_vend < vend[minIndex].cod_vend) {
             minIndex = j;
         }
        }
         Vendedor temp = vend[i];
          vend[i] = vend[minIndex];
          vend[minIndex].cod_vend = temp.cod_vend;
  }
}

int contarVendedoresEnArchivo() {
    FILE* archivo = fopen("vendedores.dat", "rb");
       if (archivo == NULL) {
        return 0; 
       }

    Vendedor vendedor;
    int contador = 0;
      while (fread(&vendedor, sizeof(Vendedor), 1, archivo) == 1) {
        contador++;
      }

    fclose(archivo);
    return contador;
}