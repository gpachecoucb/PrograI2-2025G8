#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include "Producto.h"
#include "Facturacion_detalle.h" 

using namespace std;

struct Fecha {
    int dia;
    int mes;
    int año;
};

struct Facturacion {
    int nro_factura;
    int ci_cliente;
    int nit;
    int beneficiario;
    Fecha fecha;
    double total_factura;
    bool eliminado;
};

void ActualizarTotalFactura(string ArchivoFacturas, string ArchivoDetalles, int nroFactura) {

    double nuevoTotal = SumarPrecioSubTotalNroFactura(ArchivoDetalles, nroFactura);
    fstream archivoF(ArchivoFacturas, ios::binary | ios::in | ios::out);
    Facturacion fact;
    
    while(archivoF.read((char*)&fact, sizeof(Facturacion))) {
        if(fact.nro_factura == nroFactura) {
            fact.total_factura = nuevoTotal;
            archivoF.seekp(-(int)sizeof(Facturacion), ios::cur);
            archivoF.write((char*)&fact, sizeof(Facturacion));
            break;
        }
    }
    archivoF.close();
}

void ModificarFacturaCompleta(string ArchivoFacturas, string ArchivoDetalles) {
    int nroFactura;
    cout << "Ingrese el Numero de Factura a modificar: ";
    cin >> nroFactura;

    fstream archivoF(ArchivoFacturas, ios::binary | ios::in | ios::out);
    if (!archivoF) {
        cout << "Error al abrir archivo de facturas." << endl;
        return;
    }

    Facturacion fact;
    bool encontrada = false;

    while (archivoF.read((char*)&fact, sizeof(Facturacion))) {
        if (fact.nro_factura == nroFactura && !fact.eliminado) {
            encontrada = true;
            
            int opcionMod;
            do {
                cout << "\n=== MODIFICANDO FACTURA NRO: " << fact.nro_factura << " ===" << endl;
                cout << "1. Modificar Datos Cliente (CI, NIT, Beneficiario)" << endl;
                cout << "2. Modificar Detalle (Cantidades de productos)" << endl;
                cout << "3. Salir y Guardar Cambios" << endl;
                cout << "Seleccione opcion: ";
                cin >> opcionMod;
                cin.ignore();

                if (opcionMod == 1) {
                    // MODIFICAR CABECERA
                    cout << "Nuevo CI Cliente (Actual " << fact.ci_cliente << "): "; cin >> fact.ci_cliente;
                    cout << "Nuevo NIT (Actual " << fact.nit << "): "; cin >> fact.nit;
                    cout << "Nuevo Beneficiario (Actual " << fact.beneficiario << "): "; cin >> fact.beneficiario;
                    
                    archivoF.seekp(-(int)sizeof(Facturacion), ios::cur);
                    archivoF.write((char*)&fact, sizeof(Facturacion));
                    archivoF.seekg(archivoF.tellp());
                    cout << "Cabecera actualizada." << endl;

                } else if (opcionMod == 2) {
                    // MODIFICAR DETALLE
                    MostrarFacturacionDetallesNroFacturas(ArchivoDetalles, nroFactura);
                    ModificarDetalleEspecifico(ArchivoDetalles, nroFactura);
                    archivoF.close(); 
                    ActualizarTotalFactura(ArchivoFacturas, ArchivoDetalles, nroFactura);
                    
                    archivoF.open(ArchivoFacturas, ios::binary | ios::in | ios::out);
                    archivoF.seekg(0, ios::beg);
                    while(archivoF.read((char*)&fact, sizeof(Facturacion))){
                        if(fact.nro_factura == nroFactura) break;
                    }
                    cout << "--- TOTAL FACTURA RECALCULADO: " << fact.total_factura << " ---" << endl;
                }

            } while (opcionMod != 3);
            break;
        }
    }
    archivoF.close();
    if (!encontrada) cout << "Factura no encontrada o eliminada." << endl;
}

void AnularFacturaLogica(string ArchivoFacturas, string ArchivoDetalles) {
    int nroFacturaEliminar;
    cout << "Ingrese el Numero de Factura a anular: ";
    cin >> nroFacturaEliminar;
    fstream archivoF(ArchivoFacturas, ios::binary | ios::in | ios::out);
    Facturacion fact;
    bool encontrada = false;

    while (archivoF.read((char*)&fact, sizeof(Facturacion))) {
        if (fact.nro_factura == nroFacturaEliminar && !fact.eliminado) {
            encontrada = true;
            cout << "Factura encontrada. Total: " << fact.total_factura << endl;
            char confirm;
            cout << "Seguro que desea anular esta factura y sus detalles? (s/n): ";
            cin >> confirm;

            if (confirm == 's' || confirm == 'S') {
                fact.eliminado = true;
                archivoF.seekp(-(int)sizeof(Facturacion), ios::cur);
                archivoF.write((char*)&fact, sizeof(Facturacion));
                cout << "Factura anulada." << endl;
            } else {
                cout << "Cancelado." << endl;
                archivoF.close();
                return;
            }
            break;
        }
    }
    archivoF.close();

    if (!encontrada) {
        cout << "Factura no encontrada." << endl;
        return;
    }

    fstream archivoD(ArchivoDetalles, ios::binary | ios::in | ios::out);
    FacturacionDetalle detalle;
    int contador = 0;

    while (archivoD.read((char*)&detalle, sizeof(FacturacionDetalle))) {
        if (detalle.nro_factura == nroFacturaEliminar && !detalle.eliminado) {
            detalle.eliminado = true;
            archivoD.seekp(-(int)sizeof(FacturacionDetalle), ios::cur);
            archivoD.write((char*)&detalle, sizeof(FacturacionDetalle));
            archivoD.seekg(archivoD.tellp()); 
            contador++;
        }
    }
    archivoD.close();
    cout << "Se anularon " << contador << " detalles asociados." << endl;
}

void CargarDatosBinarioVectorF(string NombreArchivo, vector<Facturacion> &vector_facturaciones)
{
    vector_facturaciones.clear();
    ifstream archivo(NombreArchivo, ios::binary);
    if (!archivo.good()) return;
    Facturacion facturacion;
    while (archivo.read((char*)&facturacion, sizeof(Facturacion))) {
        vector_facturaciones.push_back(facturacion);
    }
    archivo.close();
}

void AgregarFacturacion(vector<Facturacion> &vector_Facturaciones, string NombreArchivo, vector<FacturacionDetalle> &vector_FacturacionDetalles)
{
    ofstream archivo;
    Facturacion Facturacion1;
    archivo.open(NombreArchivo, ios::binary | ios::app);

    if (archivo.good())
    {
        // 1. Lógica del ID 
        
        if (vector_Facturaciones.empty())
        {
            Facturacion1.nro_factura = 1;
        }
        else
        {
            Facturacion1.nro_factura = vector_Facturaciones.back().nro_factura + 1;
        }

        cout << "--- NUEVA FACTURA NRO: " << Facturacion1.nro_factura << " ---" << endl;

        // 2. Datos del Cliente
        cout << "Ingrese CI cliente: "; cin >> Facturacion1.ci_cliente;
        cout << "Ingrese NIT: "; cin >> Facturacion1.nit;
        cout << "Ingrese Beneficiario: "; cin >> Facturacion1.beneficiario;

        // 3. Fecha Automática
        time_t now = time(0);
        tm *ltm = localtime(&now);
        Facturacion1.fecha.dia = ltm->tm_mday;
        Facturacion1.fecha.mes = 1 + ltm->tm_mon;
        Facturacion1.fecha.año = 1900 + ltm->tm_year;

        cout << "Fecha registrada: " << Facturacion1.fecha.dia << "/" << Facturacion1.fecha.mes << "/" << Facturacion1.fecha.año << endl;

        // 4. Agregar Detalles 
       
        AgregarFacturacionDetalle(vector_FacturacionDetalles, "FacturacionDetalles.bin", Facturacion1.nro_factura);

        // 5. Calcular Total
        Facturacion1.total_factura = SumarPrecioSubTotalNroFactura("FacturacionDetalles.bin", Facturacion1.nro_factura);
        Facturacion1.eliminado = false;

        archivo.write((char *)&Facturacion1, sizeof(Facturacion));
        vector_Facturaciones.push_back(Facturacion1);
    }
    archivo.close();
    cout << "Facturacion registrada con exito. Total: " << Facturacion1.total_factura << endl;
    
}

void MostrarFacturaciones(string NombreArchivo){
    ifstream archivo;
    archivo.open(NombreArchivo, ios::binary);
    Facturacion Facturacion;
    if(archivo.good()){
        cout << "----------------FACTURACIONES REGISTRADAS--------------------" << endl;
        while(archivo.read((char*)&Facturacion, sizeof(Facturacion))){
            if(!Facturacion.eliminado){
                cout << "------------------------------------" << endl;
                cout << "Nro Factura: " << Facturacion.nro_factura <<endl;
                cout << "Ci Cliente: " << Facturacion.ci_cliente << endl;
                cout << "Fecha: " << Facturacion.fecha.dia << "/" << Facturacion.fecha.mes << "/"<<Facturacion.fecha.año << endl;
                cout << "TOTAL: " << Facturacion.total_factura << endl;
                cout << "------------------------------------" << endl;
                MostrarFacturacionDetallesNroFacturas("FacturacionDetalles.bin", Facturacion.nro_factura);
            }
        }
    }
    archivo.close();
}

void MostrarMenuFacturacion(){
    cout << "=============================" << endl;
    cout << "Menu: Facturaciones" << endl;
    cout << "=============================" << endl;
    cout << "1. Agregar facturacion" << endl;
    cout << "2. Listar facturaciones" << endl;
    cout << "3. Anular Factura (Eliminar Completo)" << endl;
    cout << "4. Modificar Factura (Conjunto)" << endl;
    cout << "5. Salir"<< endl;
    cout << "=============================" << endl;
}

int ControlFacturaciones(vector<Facturacion> vector_Facturaciones, vector<FacturacionDetalle> &vector_FacturacionDetalles){
    string NombreArchivo = "Facturaciones.bin";
    int opcion;
    do {
        system("cls");
        MostrarMenuFacturacion();
        cout << "Escoja una opcion: ";
        cin >> opcion;
        cin.ignore();
        
        switch (opcion){
            case 1:    
                system("cls");
                AgregarFacturacion(vector_Facturaciones, NombreArchivo, vector_FacturacionDetalles); 
                system("pause");
                break;
            case 2: 
                system("cls");
                MostrarFacturaciones(NombreArchivo); 
                system("pause");
                break;
            case 3: 
                AnularFacturaLogica(NombreArchivo, "FacturacionDetalles.bin"); 
                system("pause");
                break;
            case 4: 
                ModificarFacturaCompleta(NombreArchivo, "FacturacionDetalles.bin"); 
                system("pause");
                break;
            case 5: 
                cout << "Saliendo..." << endl; 
                break;
            default: 
                cout << "Opcion no valida." << endl; 
                system("pause");
                break;
        }
    } while(opcion != 5);
    return 0;
}