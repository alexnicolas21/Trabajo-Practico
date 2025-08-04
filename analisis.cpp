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

cout<<"Vendedor que mas dinero generO: "<<vendedores[posMaxVend].nombre_vend
  <<"  $"<<totPorVendedor[posMaxVend]<<endl;


//sucursal que mas dinero generó

char sucursales[3][100]={"Suc1", "Suc2", "Suc3"}
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

// RANKING DE RPODUCTOS

const int MAX_PROD = 1000; // rango esperado de productos
int productos[MAX_PROD] = {0};  // indice = cod_producto, valor = cantidad de veces vendido

for (int i = 0; i < cantVentas; i++ {
    int cod = ventas [i].cod_producto;
    if (cod >=0 && cod < MAX_PROD) {
        productos[cod]++;
    }
}

// Mostrar productos más vendidos (orden descendente)
cout << "\n Ranking de productos más vendidos: \n";

for (int i = 0; i < MAX_PROD; i++) {
    for (int j = i + 1; j < MAX_PROD; j++) {
        if (productos[j] > productos[i]) {
       // swap conteo
        int aux = productos[i];
        productos[i] = productos[j];
        productos[j] = aux;

       // swap códigos
        int auxCod = i;
        i = j;
        j = auxCod;
        }
    }
}

// Mostrar top 10 productos más vendidos
int mostrados  = 0;
for (int i = 0; i < MAX_PROD && mostrados < 10; i++) {
    if (productos[i] > 0) {
       cout << "Producto " << i << " - Vendido " << productos[i] << "veces\n";
       mostrados++;
    }
}
