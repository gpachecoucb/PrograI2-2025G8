#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Producto.h"
#pragma once
using namespace std;
struct FacturacionDetalle
{
    int nro_factura;
    int id_producto;
    int cantidad;
    float precio_unitario;
    float precio_total;
};

void AgregarFacturacionDetalle(vector<FacturacionDetalle> &vector_FacturacionDetalles, string NombreArchivo);
void MostrarFacturacionDetalles(string NombreArchivo);
void MostrarMenuFacturacionDetalle();
void MostrarMenuFacturacionDetalleVector(vector<string> vector_cadenas);
double SumarPrecioSubTotalNroFactura(string NombreArchivo, int nroFactura);
void MostrarFacturacionDetallesNroFacturas(string NombreArchivo, int nroFactura);

int ControlFacturacionDetalles(){
    vector<FacturacionDetalle> vector_FacturacionDetalles;
    string NombreArchivo = "FacturacionDetalles.bin";
    int opcion;
    do {
        MostrarMenuFacturacionDetalle();
        cout << "Escoja una opcion: " << endl;
        cin >> opcion;
        cin.ignore();
        
        switch (opcion)
        {
        case 1:
            AgregarFacturacionDetalle(vector_FacturacionDetalles, NombreArchivo);
            
            break;
        case 2:
            MostrarFacturacionDetalles(NombreArchivo);
            
            break;
        
        case 3:
            cout << "Saliendo del sistema..." << endl;
            
            break;
        default:
            cout << "Opcion no valida. Intente de nuevo." << endl;
            
            break;
        }
        
    } while(opcion != 3);
    
    return 0;
}


void AgregarFacturacionDetalle(vector<FacturacionDetalle> &vector_FacturacionDetalles, string NombreArchivo){

    ofstream archivo;
    
    FacturacionDetalle FacturacionDetalle1;
    Producto producto;
    double precio_unitario_producto = 0;
    archivo.open(NombreArchivo, ios::binary|ios::app);
    if(archivo.good()){
        if(vector_FacturacionDetalles.size() == 0){
            FacturacionDetalle1.nro_factura = 1;
        }
        else{
            FacturacionDetalle1.nro_factura = vector_FacturacionDetalles[0].nro_factura + 1;
        }
        do{
            Producto producto_buscado;
            cout << "Ingrese el ID del producto: ";
            cin >> FacturacionDetalle1.id_producto;
            BuscarProductoID("Producto.bin", FacturacionDetalle1.id_producto, producto);
            precio_unitario_producto = producto.precio_Venta;
            if(precio_unitario_producto == 0){
                cout << "El producto buscado no existe, ingrese el id de un producto registrado" << endl;
            }
        }while(precio_unitario_producto == 0);
        FacturacionDetalle1.precio_unitario = precio_unitario_producto;
        cout << "Ingrese la cantidad del producto: ";
        cin >> FacturacionDetalle1.cantidad;
        FacturacionDetalle1.precio_total = FacturacionDetalle1.precio_unitario*FacturacionDetalle1.cantidad;
        archivo.write((char*)&FacturacionDetalle1, sizeof(FacturacionDetalle));

    }
    archivo.close();
    cout << "El FacturacionDetalle se registro correctamente" << endl;
    
}
void MostrarFacturacionDetalles(string NombreArchivo){
    ifstream archivo;
    archivo.open(NombreArchivo, ios::binary);
    FacturacionDetalle FacturacionDetalle;
    Producto producto;
    if(archivo.good()){
        while(archivo.read((char*)&FacturacionDetalle, sizeof(FacturacionDetalle))){
            cout << "Nro Factura: " << FacturacionDetalle.nro_factura <<endl;
            cout << "ID_Producto: " << FacturacionDetalle.id_producto << endl;
            BuscarProductoID("Producto.bin", FacturacionDetalle.id_producto, producto);
            cout << "Nombre Producto: " << producto.nombre << endl;;
            cout << "Cantidad: " << FacturacionDetalle.cantidad<<endl;
            cout << "Precio unitario: " << FacturacionDetalle.precio_unitario << endl;
            cout << "Precio total: " << FacturacionDetalle.precio_total << endl;
            
        }
    }
    archivo.close();
    
    
    

}
void MostrarMenuFacturacionDetalle(){
    cout << "=============================" << endl;
    cout << "Menu Ferreteria: FacturacionDetalleS" << endl;
    cout << "=============================" << endl;
    cout << "1. Agregar Detalles a la facturacion" << endl;
    cout << "2. Listar Detalles a la facturacion"<< endl;
    cout << "3. Salir"<< endl;
    cout << "###REPORTES###" << endl;    
    cout << "=============================" << endl;
}

void MostrarMenuFacturacionDetalleVector(vector<string> vector_cadenas){
    for(int i = 0; i < vector_cadenas.size(); i++){
        if(i%3 != 0){
            cout << i+1 << " " << vector_cadenas[i] << "\t";    
        }
        else{
            cout << i+1 << " " << vector_cadenas[i] << endl;    
        }
        

    }
}
double SumarPrecioSubTotalNroFactura(string NombreArchivo, int nroFactura){
    ifstream archivo;
    archivo.open(NombreArchivo, ios::binary);
    FacturacionDetalle facturaciondetalle;
    double total_suma;
    if(archivo.good()){
        while(archivo.read((char*)&facturaciondetalle, sizeof(FacturacionDetalle))){
            if(facturaciondetalle.nro_factura == nroFactura){
                total_suma+=facturaciondetalle.precio_total;
            }
        }
    }
    archivo.close();
    return total_suma;
}

void MostrarFacturacionDetallesNroFacturas(string NombreArchivo, int nroFactura){
    ifstream archivo;
    archivo.open(NombreArchivo, ios::binary);
    FacturacionDetalle FacturacionDetalle;
    Producto producto;
    if(archivo.good()){
        while(archivo.read((char*)&FacturacionDetalle, sizeof(FacturacionDetalle))){
            if(nroFactura == FacturacionDetalle.nro_factura){
                cout << "Nro Factura: " << FacturacionDetalle.nro_factura << endl;
                cout << "ID_Producto: " << FacturacionDetalle.id_producto << endl;
                BuscarProductoID("Producto.bin", FacturacionDetalle.id_producto,producto);
                cout << "Nombre Producto:" << producto.nombre << endl;;
                cout << "Cantidad: " << FacturacionDetalle.cantidad<<endl;
                cout << "Precio unitario: " << FacturacionDetalle.precio_unitario << endl;
                cout << "Precio total: " << FacturacionDetalle.precio_total << endl;
            }
        }
    }
    archivo.close();
    
    
    

}