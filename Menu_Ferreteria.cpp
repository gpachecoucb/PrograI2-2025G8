#include <iostream>
#include "Producto.h"
#include "Facturacion_detalle.h"
#include "Facturacion.h"
#include "Libreria_Trabajadores.h"
#include "Libreria_Clientes.h"
#include "Libreria_Proveedores.h"
void MostrarMenuPrincipal();
int main(){
    int opcion;
    vector<Producto> vector_productos;
    CargarDatosBinarioVectorP("Productos.bin", vector_productos);
    vector<FacturacionDetalle> vector_FacturacionDetalles;
    CargarDatosBinarioVectorDF("FacturacionDetalles.bin", vector_FacturacionDetalles);
    vector<Facturacion> vector_Facturaciones;
    CargarDatosBinarioVectorF("Facturaciones.bin", vector_Facturaciones);

    cin.clear();
    do{
        MostrarMenuPrincipal();
        
        cout << "Escoja una opcion"<< endl;
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            ControlProductos(vector_productos);
            break;
        case 2:
            ControlFacturacionDetalles(vector_FacturacionDetalles);
            break;
        case 3:
            ControlFacturaciones(vector_Facturaciones, vector_FacturacionDetalles);
            break;
        case 4:
            Menu_Trabajadores();
            break;
        case 5:
            Menu_Clientes();
            break;
        case 6:
            Menu_Proveedores();
            break;
        case 7:
            cout << "Saliendo del programa..." << endl;
            
        default:
            break;
        }
       
        
        
    }while (opcion != 7);
    return 0;
}
void MostrarMenuPrincipal(){
    cout << "=============================" << endl;
    cout << "Menu Ferreteria:" << endl;
    cout << "=============================" << endl;
    cout << "1. Control de Productos" << endl;
    cout << "2. Control de FacturacionDetalles"<< endl;
    cout << "3. Control de Facturacion"<< endl;
    cout << "4. Control de Trabajadores"<<endl;
    cout << "5. Control de Clientes"<<endl;
    cout << "6. Control de Proveedores" << endl;

    cout <<  "7. Salir" << endl;
    cout << "###REPORTES###" << endl;    
    cout << "=============================" << endl;
}