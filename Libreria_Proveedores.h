#pragma once
#include "Libreria_Trabajadores.h"
#include "Producto.h"
using namespace std;

struct Proveedores
{
    int ID_Proveedor;
    char ID_Tipo_Producto[100];
    char Nombre[50];
    char Direccion[150];
    char Correo[150];
    char Contacto[100];
    int Telefono;
};
// Registro y visualización
vector<Proveedores> Registro_Proveedores();
void Imprimir_Vectores_Proveedores(vector<Proveedores>& Lista_Proveedores);
void Imprimir_Proveedor(Proveedores Datos_Proveedor);

// Archivos .bin
void Crear_Lista_Proveedores_bin(vector<Proveedores>& Lista_Proveedores);
vector<Proveedores> Leer_Archivo_BIN_estructura_proveedores();
void Agregar_Proveedores_BIN(vector<Proveedores> Nuevos);

// Submenú
void Sub_Menu_Registrar_Proveedores(vector<Proveedores>& Lista_Proveedores);

// Búsqueda
void Opciones_Busqueda_Proveedores(vector<Proveedores>);
void Buscar_NIT_Proveedor(vector<Proveedores>);
void Buscar_Tipo_Proveedor(vector<Proveedores>);

// Edición
Proveedores Sub_Menu_Editar_Proveedor(Proveedores Datos_Proveedor);
void Editar_Datos_Proveedor(vector<Proveedores>& Lista_Proveedores);

// Eliminación
void Borrar_Proveedor(vector<Proveedores>& Lista_Proveedores);

// Menú principal
void Menu_Proveedores();

void Menu_Proveedores()
{
    int opcion_numerica = 1;
    vector<Proveedores> Lista_Proveedores;

    do
    {
        string opcion;
        bool verificador = true;
        system("cls");

        cout << "MENU PROVEEDORES" << endl;
        cout << "1. Registrar Proveedores" << endl;
        cout << "2. Mostrar Lista de Proveedores" << endl;
        cout << "3. Cargar lista de proveedores desde archivo .bin" << endl;
        cout << "0. Salir" << endl;

        do {
            cout << "Ingrese una opcion: ";
            getline(cin, opcion);

            if (Validar_Datos_Numericos(opcion))
            {
                stringstream numeros(opcion);
                numeros >> opcion_numerica;
                verificador = true;
            }
            else
            {
                cout << "Opcion Invalida!" << endl;
                verificador = false;
            }

        } while (!verificador);

        switch (opcion_numerica)
        {
        case 1:
            Sub_Menu_Registrar_Proveedores(Lista_Proveedores);
            break;

        case 2:
            Imprimir_Vectores_Proveedores(Lista_Proveedores);
            break;

        case 3:
            Lista_Proveedores = Leer_Archivo_BIN_estructura_proveedores();
            break;

        default:
            break;
        }

    } while (opcion_numerica != 0);
}

vector <Proveedores> Registro_Proveedores()
{
   system ("cls");
   vector <Proveedores> Lista_Proveedores;
   Proveedores Datos_Proveedor;
   string Almacenador_Datos = "";
   int numero_proveedores = 0;
   bool verificador = true;
   int opcion_tipo=0;
   vector<string> tipo_productos = {"Construccion", "Electricidad", "Fontaneria",
                                     "Herramientas", "Cocina", "Jardin", 
                                     "Pintura", "Decoracion", "Hogar y limpieza", 
                                     "Seguridad y Proteccion", "Ferreteria", "Automotriz",
                                    };
   do {
      system ("cls");
      cout<<"Ingrese cuantos proveedores desea registrar: ";
      getline(cin, Almacenador_Datos);
      if (Validar_Datos_Numericos(Almacenador_Datos))
      {
        stringstream numeros(Almacenador_Datos);
        numeros>> numero_proveedores; 
        Almacenador_Datos = "";
        verificador = true;
      }
      else
      {
        system("cls");
        cout<<"Opcion invalida. "<<endl;
        system("pause");
        Almacenador_Datos = "";
        verificador = false;
      }
      } while (verificador != true);
   for (int i = 0; i < numero_proveedores; i++)
   {
     cout<<"Ingrese los datos del proveedor ["<<i+1<<"]"<<endl;
     do {
            cout << "Ingrese el nombre del proveedor: ";
            getline(cin, Almacenador_Datos);
            if (Validar_Datos_Caracteres(Almacenador_Datos))
            {
                strcpy(Datos_Proveedor.Nombre, Almacenador_Datos.c_str());
                Almacenador_Datos = "";
                verificador = true;
            }
            else
            {
                cout << "El nombre solo puede contener letras y espacios. Registre denuevo los nombres del proveedor." << endl;
                Almacenador_Datos = "";
                verificador = false;
            }
        } while (verificador != true);
      do {
            cout << "Ingrese el NIT del proveedor: ";
            getline(cin, Almacenador_Datos);
            if (Validar_Datos_Numericos(Almacenador_Datos))
            {
                stringstream numeros(Almacenador_Datos);
                numeros>> Datos_Proveedor.ID_Proveedor; 
                Almacenador_Datos = "";
                verificador = true;
            }
            else
            {
                cout << "El NIT solo puede contener numeros y espacios. Registre denuevo el NIT del proveedor." << endl;
                Almacenador_Datos = "";
                verificador = false;
            }
        } while (verificador != true);
        do {
            cout << "Ingrese el nombre del contacto del proveedor: ";
            getline(cin, Almacenador_Datos);
            if (Validar_Datos_Caracteres(Almacenador_Datos))
            {
                strcpy(Datos_Proveedor.Contacto, Almacenador_Datos.c_str());
                Almacenador_Datos = "";
                verificador = true;
            }
            else
            {
                cout << "El nombre del contacto solo puede contener letras y espacios. Registre denuevo el nombre del contacto con el proveedor." << endl;
                Almacenador_Datos = "";
                verificador = false;
            }
        } while (verificador != true);
        do {
            cout<<"Ingrese el telefono de contacto: ";
            getline(cin, Almacenador_Datos);
            if (Validar_Datos_Numericos(Almacenador_Datos))
            {
                stringstream numeros(Almacenador_Datos);
                numeros>> Datos_Proveedor.Telefono; 
                Almacenador_Datos = "";
                verificador = true;
            }
            else
            {
                cout << "El telefono solo puede contener numeros. Registre denuevo el telefono del proveedor." << endl;
                Almacenador_Datos = "";
                verificador = false;
            }
        } while (verificador != true);
        do {
            cout<<"Ingrese la direccion del proveedor: ";
            getline(cin, Almacenador_Datos);
            strcpy(Datos_Proveedor.Direccion, Almacenador_Datos.c_str()); 
        } while (verificador != true);
        do {
            cout<<"Ingrese el correo del proveedor: ";
            getline(cin, Almacenador_Datos);
            strcpy(Datos_Proveedor.Correo, Almacenador_Datos.c_str());
        } while (verificador != true);
        do {
            cout<<"Ingrese el tipo del proveedor: "<<endl;
            MostrarMenuVector(tipo_productos);
            cout<<"Selecion una opcion: ";
            getline(cin, Almacenador_Datos);
            if (Validar_Datos_Numericos(Almacenador_Datos))
            {
                opcion_tipo = stoi(Almacenador_Datos);
                strcpy(Datos_Proveedor.ID_Tipo_Producto, tipo_productos[opcion_tipo-1].c_str());
                Almacenador_Datos = "";
                verificador = true;
            }
            else
            {
                cout << "Opcion invalida." << endl;
                Almacenador_Datos = "";
                verificador = false;
            }
        } while (verificador != true);
     Lista_Proveedores.push_back(Datos_Proveedor);
   }
   return Lista_Proveedores;
}

void Imprimir_Vectores_Proveedores(vector<Proveedores>& Lista_Proveedores)
{
    system("cls");
    if (Lista_Proveedores.empty())
    {
        cout << "La lista de proveedores esta vacia." << endl;
    }
    else
    {
        for (int i = 0; i < Lista_Proveedores.size(); i++)
        {
            cout << "Datos del proveedor [" << i+1 << "]" << endl;
            cout << "ID / NIT del proveedor: " << Lista_Proveedores[i].ID_Proveedor << endl;
            cout << "Tipo de producto: " << Lista_Proveedores[i].ID_Tipo_Producto << endl;
            cout << "Nombre del proveedor: " << Lista_Proveedores[i].Nombre << endl;
            cout << "Direccion: " << Lista_Proveedores[i].Direccion << endl;
            cout << "Correo: " << Lista_Proveedores[i].Correo << endl;
            cout << "Persona de contacto: " << Lista_Proveedores[i].Contacto << endl;
            cout << "Telefono: " << Lista_Proveedores[i].Telefono << endl;
        }
    }
    system("pause");
}

void Imprimir_Proveedor(Proveedores Datos_Proveedor)
{
    cout<<"=========================="<<endl;
    cout<<"NIT del proveedor: "<<Datos_Proveedor.ID_Proveedor<<endl;
    cout<<"Tipo de producto: "<<Datos_Proveedor.ID_Tipo_Producto<<endl;
    cout<<"Nombre del proveedor: "<<Datos_Proveedor.Nombre<<endl;
    cout<<"Direccion del proveedor: "<<Datos_Proveedor.Direccion<<endl;
    cout<<"Correo del proveedor: "<<Datos_Proveedor.Correo<<endl;
    cout<<"Contacto del proveedor: "<<Datos_Proveedor.Contacto<<endl;
    cout<<"Telefono del proveedor: "<<Datos_Proveedor.Telefono<<endl;
    cout<<"=========================="<<endl;
}

//Archivos .bin
void Crear_Lista_Proveedores_bin(vector<Proveedores>& Lista_Proveedores)
{
    ofstream archivo;
    archivo.open("Lista_de_Proveedores.bin", ios::binary | ios::trunc);
    if (archivo.fail())
    {
        cout << "El archivo no se logro crear con exito" << endl;
    }
    else
    {
        for (Proveedores p : Lista_Proveedores)
        {
            archivo.write((char*)&p, sizeof(Proveedores));
        }
        cout << "Se registro la lista de proveedores. " << endl;
        system("pause");
    }
    archivo.close();
}

vector<Proveedores> Leer_Archivo_BIN_estructura_proveedores()
{
    system("cls");
    ifstream archivo;
    Proveedores Datos_Proveedor;
    vector<Proveedores> Lista_Proveedores;
    archivo.open("Lista_de_Proveedores.bin", ios::binary);
    if (archivo.fail())
    {
        cout<<"El archivo no se logro abrir con exito"<<endl;
        system("pause");
    }
    else
    {
        while (archivo.read((char*)&Datos_Proveedor, sizeof(Proveedores)))
        {
            Lista_Proveedores.push_back(Datos_Proveedor);
        }
    }
    archivo.close();
    return Lista_Proveedores;
}

//ABM Proveedores
void Sub_Menu_Registrar_Proveedores(vector<Proveedores>& Lista_Proveedores)
{
    int opcion_numerica;
    bool verificador = true;
    string Almacenador_Datos;
    vector<Proveedores> Lista_Proveedores_Anadidos;

    do
    {
        do {
            system("cls");
            cout << "REGISTRAR PROVEEDORES" << endl;
            cout << "1. Crear Nueva Lista de Proveedores" << endl;
            cout << "2. Aniadir Proveedor" << endl;
            cout << "3. Buscar Proveedor" << endl;
            cout << "4. Editar Proveedor" << endl;
            cout << "5. Borrar Proveedor" << endl;
            cout << "0. Salir" << endl;
            cout << "Ingrese una opcion: ";
            getline(cin, Almacenador_Datos);

            if (Validar_Datos_Numericos(Almacenador_Datos))
            {
                stringstream numeros(Almacenador_Datos);
                numeros >> opcion_numerica;
                verificador = true;
            }
            else
            {
                system("cls");
                cout << "Opcion invalida. Ingrese un numero." << endl;
                system("pause");
                verificador = false;
            }
        } while (!verificador);

        switch (opcion_numerica)
        {
        case 1:
            system("cls");
            Lista_Proveedores = Registro_Proveedores();
            Imprimir_Vectores_Proveedores(Lista_Proveedores);
            Crear_Lista_Proveedores_bin(Lista_Proveedores);
            break;

        case 2:
            system("cls");
            Lista_Proveedores = Leer_Archivo_BIN_estructura_proveedores();
            Lista_Proveedores_Anadidos = Registro_Proveedores();
            Agregar_Proveedores_BIN(Lista_Proveedores_Anadidos);

            for (auto& p : Lista_Proveedores_Anadidos)
                Lista_Proveedores.push_back(p);

            Imprimir_Vectores_Proveedores(Lista_Proveedores);
            break;

        case 3:
            system("cls");
            Lista_Proveedores = Leer_Archivo_BIN_estructura_proveedores();
            Opciones_Busqueda_Proveedores(Lista_Proveedores);
            break;

        case 4:
            Editar_Datos_Proveedor(Lista_Proveedores);
            break;

        case 5:
            Borrar_Proveedor(Lista_Proveedores);
            break;
        }
    } while (opcion_numerica != 0);
}

void Agregar_Proveedores_BIN(vector<Proveedores> Nuevos)
{
    ofstream archivo("Lista_de_Proveedores.bin", ios::binary | ios::app);

    if (archivo.fail())
    {
        cout<<"No se pudo abrir el archivo"<<endl;
        return;
    }
    else
    {
        for (Proveedores Datos_Proveedor : Nuevos)
        {
            archivo.write((char*)&Datos_Proveedor, sizeof(Proveedores));
        }
    }

    archivo.close();
    cout<<"Se agregaron nuevos proveedores."<<endl;
    system("pause");
}

Proveedores Sub_Menu_Editar_Proveedor(Proveedores Datos_Proveedor)
{
    int opcion = 0;
    string texto;
    int numero;

    cout<<"EDITAR DATOS DEL PROVEEDOR"<<endl;
    cout<<"1. Editar Nombre"<<endl;
    cout<<"2. Editar Tipo de Producto"<<endl;
    cout<<"3. Editar NIT"<<endl;
    cout<<"4. Editar Direccion"<<endl;
    cout<<"5. Editar Correo"<<endl;
    cout<<"6. Editar Contacto"<<endl;
    cout<<"7. Editar Telefono"<<endl;
    cout<<"Ingrese una opcion: ";
    cin>>opcion;
    cin.ignore();

    switch(opcion)
    {
        case 1:
            cout<<"Ingrese el nuevo nombre: ";
            getline(cin, texto);
            strcpy(Datos_Proveedor.Nombre, texto.c_str());
            break;

        case 2:
            cout<<"Ingrese el nuevo tipo de producto: ";
            getline(cin, texto);
            strcpy(Datos_Proveedor.ID_Tipo_Producto, texto.c_str());
            break;

        case 3:
            cout<<"Ingrese el nuevo NIT: ";
            getline(cin, texto);
            numero = stoi(texto);
            Datos_Proveedor.ID_Proveedor = numero;
            break;

        case 4:
            cout<<"Nueva direccion: ";
            getline(cin, texto);
            strcpy(Datos_Proveedor.Direccion, texto.c_str());
            break;

        case 5:
            cout<<"Nuevo correo: ";
            getline(cin, texto);
            strcpy(Datos_Proveedor.Correo, texto.c_str());
            break;

        case 6:
            cout<<"Nuevo contacto: ";
            getline(cin, texto);
            strcpy(Datos_Proveedor.Contacto, texto.c_str());
            break;

        case 7:
            cout<<"Nuevo telefono: ";
            getline(cin, texto);
            numero = stoi(texto);
            Datos_Proveedor.Telefono = numero;
            break;
    }

    return Datos_Proveedor;
}

void Opciones_Busqueda_Proveedores(vector<Proveedores> Lista_Proveedores)
{
    system("cls");
    int opcion = 0;
    string Almacenador_Datos;
    bool verificador = true;

    do {
        cout<<"OPCIONES DE BUSQUEDA"<<endl;
        cout<<"1. Buscar por NIT"<<endl;
        cout<<"2. Buscar por Tipo de Producto"<<endl;
        cout<<"Seleccione una opcion de busqueda: ";
        getline(cin, Almacenador_Datos);

        if (Validar_Datos_Numericos(Almacenador_Datos))
        {
            stringstream numeros(Almacenador_Datos);
            numeros >> opcion;
            verificador = true;
        }
        else
        {
            system("cls");
            cout << "Opcion invalida." << endl;
            system("pause");
            verificador = false;
        }

    } while (!verificador);

    switch (opcion)
    {
        case 1:
            Buscar_NIT_Proveedor(Lista_Proveedores);
            break;
        case 2:
            Buscar_Tipo_Proveedor(Lista_Proveedores);
            break;
        default:
            break;
    }
}

void Editar_Datos_Proveedor(vector<Proveedores>& Lista_Proveedores)
{
    if (Lista_Proveedores.empty())
    {
        system("cls");
        cout << "Lista vacia." << endl;
        system("pause");
        return;
    }

    string nit;
    cout << "Ingrese el NIT del proveedor a editar: ";
    getline(cin, nit);

    bool encontrado = false;

    for (int i = 0; i < Lista_Proveedores.size(); i++)
    {
        if (to_string(Lista_Proveedores[i].ID_Proveedor) == nit)
        {
            cout << "Proveedor encontrado:" << endl;
            Imprimir_Proveedor(Lista_Proveedores[i]);

            Lista_Proveedores[i] = Sub_Menu_Editar_Proveedor(Lista_Proveedores[i]);

            Crear_Lista_Proveedores_bin(Lista_Proveedores);

            cout << "Datos actualizados correctamente." << endl;
            system("pause");

            encontrado = true;
            break;
        }
    }

    if (!encontrado)
    {
        cout << "No existe un proveedor con ese NIT." << endl;
        system("pause");
    }
}

void Buscar_Tipo_Proveedor(vector<Proveedores> Lista_Proveedores)
{
    if (Lista_Proveedores.empty())
    {
        system("cls");
        cout << "Lista de proveedores vacia." << endl;
        system("pause");
        return;
    }

    string tipo;
    system("cls");
    cout << "Ingrese el Tipo de Producto a buscar: ";
    getline(cin, tipo);

    for (int i = 0; i < Lista_Proveedores.size(); i++)
    {
        if (Comparador_de_Strings(tipo, Lista_Proveedores[i].ID_Tipo_Producto))
        {
            Imprimir_Proveedor(Lista_Proveedores[i]);
        }
    }

    system("pause");
}

void Buscar_NIT_Proveedor(vector<Proveedores> Lista_Proveedores)
{
    if (Lista_Proveedores.empty())
    {
        system("cls");
        cout << "Lista de proveedores vacia." << endl;
        system("pause");
        return;
    }

    string nit;
    system("cls");
    cout << "Ingrese el NIT a buscar: ";
    getline(cin, nit);

    for (int i = 0; i < Lista_Proveedores.size(); i++)
    {
        if (to_string(Lista_Proveedores[i].ID_Proveedor) == nit)
        {
            Imprimir_Proveedor(Lista_Proveedores[i]);
        }
    }

    system("pause");
}

void Borrar_Proveedor(vector<Proveedores>& Lista_Proveedores)
{
    if (Lista_Proveedores.empty())
    {
        system("cls");
        cout << "Lista vacia." << endl;
        system("pause");
        return;
    }
    else
    {
        system("cls");
        string NIT;
        vector<Proveedores> Lista_Nueva;
        cout << "Ingrese el NIT del proveedor a borrar: ";
        getline(cin, NIT); 
        bool encontrado = false;
        for (int i = 0; i < Lista_Proveedores.size(); i++)
        {
            if (to_string(Lista_Proveedores[i].ID_Proveedor) == NIT) 
            {
                cout << "Proveedor Borrado:"<<endl;
                Imprimir_Proveedor(Lista_Proveedores[i]); 
                encontrado = true;
            }
            else
            {
                Lista_Nueva.push_back(Lista_Proveedores[i]);
            }
        }
        if (!encontrado)
        {
            cout << "No existe un proveedor con ese NIT." << endl;
            system("pause");
            return;
        }
        Crear_Lista_Proveedores_bin(Lista_Nueva); 
        cout << "El proveedor fue eliminado correctamente."<<endl;
        system("pause");
    }
}


