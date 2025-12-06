#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Producto.h"
#include "Facturacion_detalle.h"
#include <ctime>
#pragma once
using namespace std;
struct Fecha
{
    int dia;
    int mes;
    int año;
};
struct Facturacion
{
    int nro_factura;
    int ci_cliente;
    int nit;
    int beneficiario;
    Fecha fecha;
    double total_factura;
};
void AgregarFacturacion(vector<Facturacion> &vector_Facturaciones, string NombreArchivo);
void MostrarFacturaciones(string NombreArchivo);
void MostrarMenuFacturacion();
void MostrarMenuFacturacionVector(vector<string> vector_cadenas);


int ControlFacturaciones(){
    vector<Facturacion> vector_Facturacions;
    string NombreArchivo = "Facturaciones.bin";
    int opcion;
    do {
        MostrarMenuFacturacion();
        cout << "Escoja una opcion: " << endl;
        cin >> opcion;
        cin.ignore();
        
        switch (opcion)
        {
        case 1:
            AgregarFacturacion(vector_Facturacions, NombreArchivo);
            
            break;
        case 2:
            MostrarFacturaciones(NombreArchivo);
            
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


void AgregarFacturacion(vector<Facturacion> &vector_Facturaciones, string NombreArchivo){

    ofstream archivo;
    
    Facturacion Facturacion1;
    Producto producto;
    Fecha fecha;
    int dia, mes, año;
    double precio_unitario_producto = 0;
    archivo.open(NombreArchivo, ios::binary|ios::app);
    if(archivo.good()){
        if(vector_Facturaciones.size() == 0){
            Facturacion1.nro_factura = 1;
        }
        else{
            Facturacion1.nro_factura = vector_Facturaciones[0].nro_factura + 1;
        }
        cout << "Ingrese el numero de carnet del cliente ";
        cin >> Facturacion1.ci_cliente;
        cout << "Ingrese el nit: ";
        cin >> Facturacion1.nit;
        cout << "Ingrese el beneficiario";
        cin >> Facturacion1.beneficiario;
        cout << "Ingrese la fecha de hoy en numero:" << endl;
        cout << "EJEMPLO: Fecha 27/09/2025 dia: 27, mes: 9, año: 2025" << endl;
        cout << "Dia: ";
        cin >> dia;
        cout << "Mes: ";
        cin >> mes;
        cout << "Año: ";
        cin >> año;
        fecha.dia = dia;
        fecha.mes = mes;
        fecha.año = año;
        Facturacion1.fecha = fecha;
        Facturacion1.total_factura = SumarPrecioSubTotalNroFactura("FacturacionDetalles.bin", Facturacion1.nro_factura);
        archivo.write((char*)&Facturacion1, sizeof(Facturacion));

    }
    archivo.close();
    cout << "El Facturacion se registro correctamente" << endl;
    
}
void MostrarFacturaciones(string NombreArchivo){
    ifstream archivo;
    archivo.open(NombreArchivo, ios::binary);
    Facturacion Facturacion;
    Producto producto;
    if(archivo.good()){
        while(archivo.read((char*)&Facturacion, sizeof(Facturacion))){
            cout << "Nro Factura: " << Facturacion.nro_factura <<endl;
            cout << "Ci del Cliente " << Facturacion.ci_cliente;
            
            cout << "NIT: " << Facturacion.nit<<endl;
            cout << "Beneficiario: " << Facturacion.beneficiario << endl;
            cout << "Fecha: " << Facturacion.fecha.dia << "/" << Facturacion.fecha.mes << "/"<<Facturacion.fecha.año << endl;
            cout << "Precio final de la factura: " << Facturacion.total_factura << endl;
            cout << "------------------------------------" << endl;
            MostrarFacturacionDetallesNroFacturas("FacturacionDetalles.bin", Facturacion.nro_factura);
            
        }
    }
    archivo.close();
    
    
    

}
void MostrarMenuFacturacion(){
    cout << "=============================" << endl;
    cout << "Menu Ferreteria: FacturacionS" << endl;
    cout << "=============================" << endl;
    cout << "1. Agregar Detalles a la facturacion" << endl;
    cout << "2. Listar Detalles a la facturacion"<< endl;
    cout << "3. Salir"<< endl;
    cout << "###REPORTES###" << endl;    
    cout << "=============================" << endl;
}

void MostrarMenuFacturacionVector(vector<string> vector_cadenas){
    for(int i = 0; i < vector_cadenas.size(); i++){
        if(i%3 != 0){
            cout << i+1 << " " << vector_cadenas[i] << "\t";    
        }
        else{
            cout << i+1 << " " << vector_cadenas[i] << endl;    
        }
        

    }
}