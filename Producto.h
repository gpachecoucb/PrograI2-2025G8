#include <vector>
#pragma once
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
struct Producto
{
    int id_producto;
    int id_proveedor;
    char nombre[30];
    int tipo;
    char marca[20];
    char distribuidor[30];
    int cantidad;
    double precio_Compra;
    double precio_Venta;
};

void AgregarProducto(vector<Producto> &vector_productos, string NombreArchivo);
void MostrarProductos(string NombreArchivo);
void MostrarMenu();
void MostrarMenuVector(vector<string> vector_cadenas);
void BuscarProductoID(string NombreArchivo, int id, Producto &producto_buscado);


int ControlProductos(){
    vector<Producto> vector_productos;
    string NombreArchivo = "Productos.bin";
    int opcion;
    do {
        MostrarMenu();
        cout << "Escoja una opcion: " << endl;
        cin >> opcion;
        cin.ignore();
        
        switch (opcion)
        {
        case 1:
            AgregarProducto(vector_productos, NombreArchivo);
            
            break;
        case 2:
            MostrarProductos(NombreArchivo);
            
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


void AgregarProducto(vector<Producto> &vector_productos, string NombreArchivo){

    ofstream archivo;
    vector<string> tipo_productos = {"Construccion", "Electricidad", "Fontaneria",
                                     "Herramientas", "Cocina", "Jardin", 
                                     "Pintura", "Decoracion", "Hogar y limpieza", 
                                     "Seguridad y Proteccion", "Ferreteria", "Automotriz",
                                    };
    archivo.open(NombreArchivo, ios::binary|ios::app);
    Producto producto1;
    if(archivo.good()){
        if(vector_productos.size() == 0){
            producto1.id_producto = 1;
        }
        else{
            producto1.id_producto = vector_productos[0].id_producto + 1;
        }
        cout <<"Ingrese el nombre del producto: ";
        cin.getline(producto1.nombre,30);
        cout << "Ingrese el tipo del producto: " << endl;
        MostrarMenuVector(tipo_productos);
        cout << endl;
        cin >> producto1.tipo;
        cin.ignore();
        cout << "Ingrese la marca del producto: ";
        cin.getline(producto1.marca,20);
        cout << "Ingrese el id del Proveedor: ";
        cin.getline(producto1.distribuidor,30);
        cout << "Ingrese la cantidad en inventario: ";
        cin >> producto1.cantidad;
        cout << "Ingrese el precio de compra del producto: ";
        cin >> producto1.precio_Compra;
        producto1.precio_Venta = producto1.precio_Compra*1.2; 
        
        archivo.write((char*)&producto1, sizeof(Producto));

    }
    archivo.close();
    cout << "El producto se registro correctamente" << endl;
    
}
void MostrarProductos(string NombreArchivo){
    vector<string> tipo_productos = {"Construccion", "Electricidad", "Fontaneria",
                                     "Herramientas", "Cocina", "Jardin", 
                                     "Pintura", "Decoracion", "Hogar y limpieza", 
                                     "Seguridad y Proteccion", "Ferreteria", "Automotriz",
                                    };
    ifstream archivo;
    archivo.open(NombreArchivo, ios::binary);
    Producto producto;
    if(archivo.good()){
        while(archivo.read((char*)&producto, sizeof(Producto))){
            cout << "ID_producto: " << producto.id_producto <<endl;
            cout << "ID_proveedor: " << producto.id_proveedor<<endl;
            cout << "Nombre: " << producto.nombre << endl;
            cout << "Tipo: " << tipo_productos[producto.tipo - 1] << endl;
            cout << "Marca: " << producto.marca << endl;
            cout << "Distribuidor: " << producto.distribuidor << endl;
            cout << "Cantidad en inventario: " << producto.cantidad << endl;
            cout << "Precio de compra: " << producto.precio_Compra << endl;
            cout << "Precio de venta: " << producto.precio_Venta << endl;        
        }
    }
    archivo.close();
    
    
    

}


void MostrarMenu(){
    cout << "=============================" << endl;
    cout << "Menu Ferreteria: PRODUCTOS" << endl;
    cout << "=============================" << endl;
    cout << "1. Agregar Productos" << endl;
    cout << "2. Listar Productos"<< endl;
    cout << "3. Salir"<< endl;
    cout << "###REPORTES###" << endl;    
    cout << "=============================" << endl;
}

void MostrarMenuVector(vector<string> vector_cadenas){
    for(int i = 0; i < vector_cadenas.size(); i++){
        if((i+1)%3 != 0){
            cout << i+1 << " " << vector_cadenas[i] << "\t";    
        }
        else{
            cout << i+1 << " " << vector_cadenas[i] << endl;    
        }
        

    }
}
void BuscarProductoID(string NombreArchivo, int id, Producto &producto_buscado){
    
    ifstream archivo;
    archivo.open(NombreArchivo, ios::binary);
    Producto producto;
    
    
    if(archivo.good()){
        while(archivo.read((char*)&producto, sizeof(Producto))){
            if(producto.id_producto == id){
                cout << "Se encontro un producto" << endl;
                producto_buscado = producto;
                break;
            }
        }
    }
    

    archivo.close();
    
    

}
