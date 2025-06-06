#include <iostream>
using namespace std;
struct Vendedor
{
    string nombre_vend;
    string nombre_surc;
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
    Vendedor vendedores[15][3];

    //Carga de vendedor
     for(int i = 0; i < 15; i++) {
         for(int j = 0; j < 3; j++) {
       cout << "Ingrese el elemento [" << i << "][" << j << "]: \n";
       cout<<"Nombre del vendedor nuevo: \n";

       getline(cin, vendedores[i][j].nombre_vend);
       cout<<"Nombre de la surcual a la cual pertenece: \n";
       getline(cin, vendedores[i][j].nombre_surc);
    // Verifica que el codigo de vendedor sea unico
        do {
             cout << "Codigo unico del vendedor: ";
             cin >> valor;
             cin.ignore();
                if (existeCodVend(vendedores, valor)) {
                    cout << "El codigo ya existe. Intente nuevamente.\n";
            }
        } while (existeCodVend(vendedores, valor) == 1);


       vendedores[i][j].cod_vend= valor;
       cout << "Se ha guardado correctamente el vendedor! \n";
       cout << "Si quiere ingresar otro vendedor ingrese (1) o si quiere volver al menu ingrese (0) \n";
       cin >> opcion;
    
       if (opcion == 0) {
        cout << "Saliendo del programa...\n";
        exit(0); 
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