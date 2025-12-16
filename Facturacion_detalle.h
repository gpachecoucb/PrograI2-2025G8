#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Producto.h"

using namespace std;

struct FacturacionDetalle
{
    int nro_factura;
    int id_producto;
    int cantidad;
    float precio_unitario;
    float precio_total;
    bool eliminado; 
};


double SumarPrecioSubTotalNroFactura(string NombreArchivo, int nroFactura){
    ifstream archivo;
    archivo.open(NombreArchivo, ios::binary);
    FacturacionDetalle facturaciondetalle;
    double total_suma = 0;
    if(archivo.good()){
        while(archivo.read((char*)&facturaciondetalle, sizeof(FacturacionDetalle))){
            if(facturaciondetalle.nro_factura == nroFactura && !facturaciondetalle.eliminado){
                total_suma += facturaciondetalle.precio_total;
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

            if(nroFactura == FacturacionDetalle.nro_factura && !FacturacionDetalle.eliminado){
                cout << "--------------------------------------" << endl;
                cout << "ID_Producto: " << FacturacionDetalle.id_producto << endl;
                
                BuscarProductoID("Productos.bin", FacturacionDetalle.id_producto, producto);
                cout << "Nombre Producto: " << producto.nombre << endl;
                cout << "Cantidad: " << FacturacionDetalle.cantidad << endl;
                cout << "Precio unitario: " << FacturacionDetalle.precio_unitario << endl;
                cout << "Precio total: " << FacturacionDetalle.precio_total << endl;
            }
        }
    }
    archivo.close();
}


void ModificarDetalleEspecifico(string NombreArchivo, int nroFactura) {
    int idProductoBuscar;
    cout << "\n--- MODIFICAR LINEA DE DETALLE ---" << endl;
    cout << "Ingrese el ID del producto que desea modificar en esta factura: ";
    cin >> idProductoBuscar;

    fstream archivo(NombreArchivo, ios::binary | ios::in | ios::out);
    if(!archivo) {
        cout << "Error al abrir archivo de detalles." << endl;
        return;
    }

    FacturacionDetalle detalle;
    bool encontrado = false;

    while(archivo.read((char*)&detalle, sizeof(FacturacionDetalle))) {
        if(detalle.nro_factura == nroFactura && detalle.id_producto == idProductoBuscar && !detalle.eliminado) {
            encontrado = true;
            cout << "Detalle actual -> Cantidad: " << detalle.cantidad << " | Precio Unit: " << detalle.precio_unitario << endl;
            
            cout << "Ingrese la NUEVA cantidad: ";
            cin >> detalle.cantidad;
            
            // Recalculamos el subtotal de esa linea
            detalle.precio_total = detalle.cantidad * detalle.precio_unitario;

            // Guardamos usando el retroceso negativo (int)
            archivo.seekp(-(int)sizeof(FacturacionDetalle), ios::cur);
            archivo.write((char*)&detalle, sizeof(FacturacionDetalle));
            cout << "Detalle actualizado correctamente." << endl;
            break; 
        }
    }
    archivo.close();

    if(!encontrado) {
        cout << "No se encontro ese producto en esta factura." << endl;
    }
}



void CargarDatosBinarioVectorDF(string NombreArchivo, vector<FacturacionDetalle> &vector_facturacionesDetalle){
    vector_facturacionesDetalle.clear();
    ifstream archivo(NombreArchivo, ios::binary);
    if (!archivo.good()) return;
    FacturacionDetalle facturacionDetalle;
    while (archivo.read((char*)&facturacionDetalle, sizeof(FacturacionDetalle))) {
        vector_facturacionesDetalle.push_back(facturacionDetalle);
    }
    archivo.close();
}

void AgregarFacturacionDetalle(vector<FacturacionDetalle> &vector_FacturacionDetalles, string NombreArchivo, int nro_factura_asignado)
{
    ofstream archivo;
    FacturacionDetalle FacturacionDetalle1;
    int opcion;
    double precio_unitario_producto = 0;
    
    archivo.open(NombreArchivo, ios::binary | ios::app);
    if (archivo.good())
    {
        // YA NO calculamos el ID aquí. Usamos el que nos mandaron.
        // El nro_factura es el enlace con el Padre.
        FacturacionDetalle1.nro_factura = nro_factura_asignado; 

        do
        {
            Producto producto_buscado;
            do
            {
                cout << "Ingrese el ID del producto: ";
                cin >> FacturacionDetalle1.id_producto;
                BuscarProductoID("Productos.bin", FacturacionDetalle1.id_producto, producto_buscado);
                
                if (producto_buscado.id_producto == 0)
                {
                    cout << "El producto no existe." << endl;
                }
                else
                {
                    precio_unitario_producto = producto_buscado.precio_Venta;
                }
            } while (producto_buscado.id_producto == 0);

            FacturacionDetalle1.precio_unitario = precio_unitario_producto;
            
            cout << "Ingrese la cantidad del producto: ";
            cin >> FacturacionDetalle1.cantidad;
            
            FacturacionDetalle1.precio_total = FacturacionDetalle1.precio_unitario * FacturacionDetalle1.cantidad;
            FacturacionDetalle1.eliminado = false;

            // Guardamos el detalle (que ya tiene el nro_factura correcto)
            archivo.write((char *)&FacturacionDetalle1, sizeof(FacturacionDetalle));
            vector_FacturacionDetalles.push_back(FacturacionDetalle1);

            do
            {
                cout << "Quiere seguir agregando mas productos? 1.SI 2.NO: ";
                cin >> opcion;
            } while (opcion != 1 && opcion != 2);

        } while (opcion != 2);
    }
    archivo.close();
    cout << "Detalles registrados correctamente" << endl;
}
void MostrarMenuFacturacionDetalle(){
    cout << "=============================" << endl;
    cout << "Menu: FacturacionDetalles" << endl;
    cout << "=============================" << endl;
    cout << "1. Agregar Detalles" << endl;
    cout << "2. Listar Todos los Detalles"<< endl;
    cout << "3. Salir"<< endl;
    cout << "=============================" << endl;
}

void MostrarFacturacionDetalles(string NombreArchivo){
    ifstream archivo;
    archivo.open(NombreArchivo, ios::binary);
    FacturacionDetalle FacturacionDetalle;
    Producto producto;
    if(archivo.good()){
        while(archivo.read((char*)&FacturacionDetalle, sizeof(FacturacionDetalle))){
            if(!FacturacionDetalle.eliminado){
                cout << "Nro Factura: " << FacturacionDetalle.nro_factura <<endl;
                cout << "ID_Producto: " << FacturacionDetalle.id_producto << endl;
                cout << "Cantidad: " << FacturacionDetalle.cantidad<<endl;
                cout << "Total: " << FacturacionDetalle.precio_total << endl;
                cout << "-----------------------" << endl;
            }
        }
    }
    archivo.close();
}

int ControlFacturacionDetalles(vector<FacturacionDetalle> &vector_FacturacionDetalles){
    string NombreArchivo = "FacturacionDetalles.bin";
    int opcion;
    do {
        system("cls");
        MostrarMenuFacturacionDetalle();
        cout << "Escoja una opcion: ";
        cin >> opcion;
        cin.ignore();
        
        switch (opcion){
            case 1:
                system("cls");
                //AgregarFacturacionDetalle(vector_FacturacionDetalles, NombreArchivo); 
                system("pause");
                break;
            case 2: 
                system("cls");
                MostrarFacturacionDetalles(NombreArchivo); 
                system("pause");
                break;
            case 3:
                cout << "Saliendo..." << endl; 
                break;
            default: 
                cout << "Opcion no valida." << endl; 
                system("pause");
                break;
        }
    } while(opcion != 3);
    return 0;
}