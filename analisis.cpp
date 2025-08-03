#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;


struct Vendedor {
int cod_vent;
char nombre_vend[100];
char nombre_sucur[100];
};

struct Venta  {
int valor;
int mes;
int cod_vend;
int region;
};

//vendedor que mas dinero generó

float totPorVendedor[50]= {0};

for(int i =0; i< cantVentas;i++){
     for (int j=0; j<cantVendedores; j++) {
        if (ventas[i].cod_vend == vendedores[j].cod_vend) {
             totPorVendedor[j] += ventas[i].valor;
        break;
     }
  }
}

int posMaxVend =0;

for(int i=0; i<cantVendedores; i++){
  if (totPorVendedor[i] > totPorVendedor[posMaxVend]){
       posMaxVend = i;
    }
}

cout<<"Vendedor que mas dinero generO: ""<<vendedores[posMaxVend].nombre_vend
  <<"  $"<<totPorVendedor[posMaxVend]<<endl;


//sucursal que mas dinero generó

char sucursales[3][100]={"Sucursal1", "Sucursal2", "Sucursal3"}
float totPorSucursal[3] ={0};
   for(int i=0; i<cantVendedores; i++){
   int suc=0;
     for(int j=0; j<3; j++){
       if (strcmp(vendedores[i].nombre_sucur, sucursales[j]) == 0) {
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
cout << "Sucursal que mas dinero genero: " << sucursales[posMaxSuc]
      << "  $" << totPorSucursal[posMaxSuc] << endl;

    return 0;
}

//FLATA EL RANKING 


  


    













   

