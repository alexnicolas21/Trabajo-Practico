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


int main()
{
    registro();
    return 0;
}


void registro(){
    int opcion;
    int valor;
    bool salir = false;
    Vendedor vendedores[15][3];
    FILE* archivo = fopen("vendedores.dat", "ab");

    //  Carga de vendedor
     for(int i = 0; i < 15 && !salir; i++) {
         for(int j = 0; j < 3; j++) {
       cout << "Ingrese el elemento [" << i << "][" << j << "]: \n";
       cout<<"Nombre del vendedor nuevo: \n";
       cin.getline(vendedores[i][j].nombre_vend, sizeof(vendedores[i][j].nombre_vend));
       cout<<"Nombre de la surcual a la cual pertenece: \n";
       cin.getline(vendedores[i][j].nombre_surc, sizeof(vendedores[i][j].nombre_surc));
    
    //  Verifica que el codigo de vendedor sea unico
        do {
             cout << "Codigo unico del vendedor: ";
             cin >> valor;
             cin.ignore();
                if (existeCodVend(vendedores, valor)) {
                    cout << "El codigo ya existe. Intente nuevamente.\n";
            }
        } while (existeCodVend(vendedores, valor) == 1); //   Si exite retorna 1 la funcion y luegp te pide que ingreses otro.


       vendedores[i][j].cod_vend= valor;
       cout << "Se ha guardado correctamente el vendedor! \n";
     
    //   Guardar los datos en archivo de texto legible
    
    if (archivo != NULL) {
        fwrite(vendedores, sizeof(Vendedor), 3, archivo);
        fclose(archivo);
        cout << "Archivo creado exitosamente.\n";
    } else {
         cout << "No se pudo crear el archivo.\n";
    }
       cout << "Si quiere ingresar otro vendedor ingrese (1) o si quiere volver al menu ingrese (0) \n";
       cin >> opcion;
          if (opcion == 0) {
            salir = true;
            break; 
        }
       cin.ignore();
     }

     } 
}


int existeCodVend(Vendedor vendedores[15][3], int valor){
    for(int i = 0; i < 15; i++) {
         for(int j = 0; j < 3; j++) {
            if ( vendedores[i][j].cod_vend == valor)
            {
                 return 1;
            } 
        }
   }
   return 0;
}