#pragma once
#include <vector>
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
    bool eliminado; // Campo para borrado lógico
};

// Prototipos
void BuscarProductoID(string NombreArchivo, int id, Producto &producto_buscado);
void MostrarMenuVector(vector<string> vector_cadenas);

void CargarDatosBinarioVectorP(string NombreArchivo, vector<Producto> &vector_productos){
    ifstream archivo(NombreArchivo, ios::binary);
    if (!archivo.good()) return;
    Producto producto;
    while (archivo.read((char*)&producto, sizeof(Producto))) {
        if(!producto.eliminado) { // Solo cargamos los no eliminados
            vector_productos.push_back(producto);
        }
    }
    archivo.close();
}

void AgregarProducto(vector<Producto> &vector_productos, string NombreArchivo){
    ofstream archivo;
    vector<string> tipo_productos = {"Construccion", "Electricidad", "Fontaneria",
                                     "Herramientas", "Cocina", "Jardin", 
                                     "Pintura", "Decoracion", "Hogar y limpieza", 
                                     "Seguridad y Proteccion", "Ferreteria", "Automotriz"};
    archivo.open(NombreArchivo, ios::binary|ios::app);
    Producto producto1;
    if(archivo.good()){
        if(vector_productos.empty()){
            producto1.id_producto = 1;
        } else {
            producto1.id_producto = vector_productos.back().id_producto + 1;
        }
        
        cin.ignore();
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
        cin >> producto1.id_proveedor;
        cin.ignore();
        cout << "Ingrese el Distribuidor: ";
        cin.getline(producto1.distribuidor,30);
        cout << "Ingrese la cantidad en inventario: ";
        cin >> producto1.cantidad;
        cout << "Ingrese el precio de compra del producto: ";
        cin >> producto1.precio_Compra;
        
        producto1.precio_Venta = producto1.precio_Compra*1.2; 
        producto1.eliminado = false; // Inicializamos en false

        archivo.write((char*)&producto1, sizeof(Producto));
        vector_productos.push_back(producto1);
    }
    archivo.close();
    cout << "El producto se registro correctamente" << endl;
}

void MostrarProductos(string NombreArchivo){
    vector<string> tipo_productos = {"Construccion", "Electricidad", "Fontaneria",
                                     "Herramientas", "Cocina", "Jardin", 
                                     "Pintura", "Decoracion", "Hogar y limpieza", 
                                     "Seguridad y Proteccion", "Ferreteria", "Automotriz"};
    ifstream archivo;
    archivo.open(NombreArchivo, ios::binary);
    Producto producto;
    if(archivo.good()){
        while(archivo.read((char*)&producto, sizeof(Producto))){
            if(!producto.eliminado){ // FILTRO LOGICO
                cout << "---------------------------------------" << endl;
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
    }
    archivo.close();
}

void BuscarProductoID(string NombreArchivo, int id, Producto &producto_buscado){
    ifstream archivo(NombreArchivo, ios::binary);
    if (!archivo.good()) return;

    Producto producto;
    bool sw = false;

    while (archivo.read((char*)&producto, sizeof(Producto))) {
        if(!producto.eliminado){
            if (producto.id_producto == id) {   
                producto_buscado = producto;
                sw = true;
                break;
            }
        }
    }

    if(sw){
        // Encontrado
    } else {
        producto_buscado.id_producto = 0; // Indicador de no encontrado
    }
    archivo.close();
}

void eliminarProductoLogico(string nombreArchivo) {
    int idEliminar;
    cout << "Ingrese ID del producto a eliminar: ";
    cin >> idEliminar;
    cin.ignore();
    
    fstream archivo(nombreArchivo, ios::binary | ios::in | ios::out);
    if(!archivo) {
        cout << "Error: No se pudo abrir el archivo." << endl;
        return;
    }
    
    Producto producto;
    bool encontrado = false;
    while(archivo.read((char*)&producto, sizeof(Producto))) {
        if(producto.id_producto == idEliminar && !producto.eliminado) {
            encontrado = true;
            cout << "\n=== PRODUCTO ENCONTRADO ===" << endl;
            cout << "Nombre: " << producto.nombre << endl;
            
            char confirmar;
            cout << "\nEsta seguro de eliminar este producto? (s/n): ";
            cin >> confirmar;
            cin.ignore();
            
            if(confirmar == 's' || confirmar == 'S') {
                producto.eliminado = true;
                archivo.seekp(-(int)sizeof(Producto), ios::cur); // Retroceder
                archivo.write((char*)&producto, sizeof(Producto));
                cout << "\nProducto eliminado correctamente." << endl;
            } else {
                cout << "\nEliminacion cancelada." << endl;
            }
            break;
        }
    }
    archivo.close();
    if(!encontrado) cout << "\nProducto no encontrado." << endl;
}

void modificarProducto(string nombreArchivo){

    int idBuscado;

    cout << "Ingrese ID del producto a modificar: ";

    cin >> idBuscado;

    cin.ignore();

   

    // Abrir en modo lectura/escritura

    fstream archivo(nombreArchivo, ios::binary | ios::in | ios::out);

   

    if(!archivo) {

        cout << "Error: No se pudo abrir el archivo." << endl;

        system("pause");

        return;

    }

   

    Producto producto;

    bool encontrado = false;

    while(archivo.read((char*)&producto, sizeof(Producto))) {

        if(producto.id_producto == idBuscado) {

            encontrado = true;

            vector<string> tipo_productos = {"Construccion", "Electricidad", "Fontaneria",

                                     "Herramientas", "Cocina", "Jardin",

                                     "Pintura", "Decoracion", "Hogar y limpieza",

                                     "Seguridad y Proteccion", "Ferreteria", "Automotriz",

                                    };

           

            archivo.seekp(-sizeof(Producto), ios::cur);

            int opcion;

            bool cambiosGuardados = false;

           

            do {

               

                cout << "=========================================" << endl;

                cout << "       MODIFICAR PRODUCTO ID: " << producto.id_producto << endl;

                cout << "=========================================" << endl;

                cout << "1. Nombre          : " << producto.nombre << endl;

                cout << "2. ID Proveedor    : " << producto.id_proveedor << endl;

                cout << "3. Tipo            : " << producto.tipo << endl;

                cout << "4. Marca           : " << producto.marca << endl;

                cout << "5. Distribuidor    : " << producto.distribuidor << endl;

                cout << "6. Cantidad        : " << producto.cantidad << endl;

                cout << "7. Precio compra   : $" << producto.precio_Compra << endl;

                cout << "8. Precio venta    : $" << producto.precio_Venta << endl;

                cout << "9. Guardar cambios y salir" << endl;

                cout << "0. Salir sin guardar" << endl;

                cout << "=========================================" << endl;

                cout << "Seleccione campo a modificar: ";

               

                cin >> opcion;

                cin.ignore();

               

                switch(opcion) {

                    case 1:

                        cout << "Nuevo nombre: ";

                        cin.getline(producto.nombre, 30);

                        break;

                    case 2:

                        cout << "Nuevo ID proveedor: ";

                        cin >> producto.id_proveedor;

                        cin.ignore();

                        break;

                    case 3:

                        cout << "Nuevo tipo (1-12): " << endl;

                        MostrarMenuVector(tipo_productos);

                        cin >> producto.tipo;

                        cin.ignore();

                        break;

                    case 4:

                        cout << "Nueva marca: ";

                        cin.getline(producto.marca, 20);

                        break;

                    case 5:

                        cout << "Nuevo distribuidor: ";

                        cin.getline(producto.distribuidor, 30);

                        break;

                    case 6:

                        cout << "Nueva cantidad: ";

                        cin >> producto.cantidad;

                        cin.ignore();

                        break;

                    case 7:

                        cout << "Nuevo precio compra: $";

                        cin >> producto.precio_Compra;

                        cin.ignore();

                        producto.precio_Venta = producto.precio_Compra * 1.2;

                        cout << "Nuevo precio venta calculado: $" << producto.precio_Venta << endl;

                       

                        break;

                    case 8:

                        cout << "Nuevo precio venta: $";

                        cin >> producto.precio_Venta;

                        cin.ignore();

                        break;

                    case 9:

                        // Guardar cambios

                        archivo.write((char*)&producto, sizeof(Producto));

                        cambiosGuardados = true;

                        cout << "\n¡Cambios guardados exitosamente!" << endl;

                       

                        break;

                    case 0:

                        cout << "\nModificacion cancelada. No se guardaron cambios." << endl;

                       

                        break;

                    default:

                        cout << "Opcion invalida." << endl;

                       

                        break;

                }

               

            } while(opcion != 9 && opcion != 0);

           

            archivo.close();

           

            if(cambiosGuardados) {

                cout << "\nProducto modificado correctamente." << endl;

            }

           

            break;

        }

    }

   

    if(!encontrado) {

        cout << "\nProducto con ID " << idBuscado << " no encontrado." << endl;

        archivo.close();

       

    }

}

void MostrarMenu(){
    cout << "=============================" << endl;
    cout << "Menu Ferreteria: PRODUCTOS" << endl;
    cout << "=============================" << endl;
    cout << "1. Agregar Productos" << endl;
    cout << "2. Listar Productos"<< endl;
    cout << "3. Modificar Productos"<< endl;
    cout << "4. Eliminar Productos"<< endl;
    cout << "5. Salir"<< endl;
    cout << "=============================" << endl;
}

void MostrarMenuVector(vector<string> vector_cadenas){
    for(int i = 0; i < vector_cadenas.size(); i++){
        if(i%3 != 0){
            cout << i+1 << " " << vector_cadenas[i] << "\t";    
        } else {
            cout << i+1 << " " << vector_cadenas[i] << endl;    
        }
    }
}

int ControlProductos(vector<Producto> &vector_productos){
    string NombreArchivo = "Productos.bin";
    int opcion;
    do {
        MostrarMenu();
        cout << "Escoja una opcion: ";
        cin >> opcion;
        cin.ignore();
        
        switch (opcion){
        case 1: AgregarProducto(vector_productos, NombreArchivo); break;
        case 2: MostrarProductos(NombreArchivo); break;
        case 3: modificarProducto(NombreArchivo); break;
        case 4: eliminarProductoLogico(NombreArchivo); break;
        case 5: cout << "Saliendo..." << endl; break;
        default: cout << "Opcion no valida." << endl; break;
        }
    } while(opcion != 5);
    return 0;
}