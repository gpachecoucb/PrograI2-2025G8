#pragma once
#include "Libreria_Trabajadores.h"

using namespace std;

struct Clientes
{
    char Nombres [50];
    char Apellidos [50];
    char Correo  [40];
    int  Nro_CI;
    int  Telefono;
};
//REGISTRO
vector <Clientes> Resgistro_Clientes();
void Imprimir_Vectores_Clientes(vector <Clientes>& Lista_Clientes);
//MENU
void Menu_Clientes ();
//ARCHIVOS .txt
void Crear_Lista_Clientes_txt(vector <Clientes> Lista_Clientes);
//ARCHIVOS .bin
void Crear_Lista_Clientes_bin(vector<Clientes>& Lista_Clientes);
vector <Clientes> Leer_Lista_Clientes_bin();
vector <Clientes> Leer_Archivo_BIN_estructura_clientes();

//Funciones de ABM
void Imprimir_Clientes(Clientes Datos_Clientes);

//SUB MENU REGISTRO TRABAJADORES
void Sub_Menu_Registrar_Clientes(vector<Clientes>& Lista_Clientes);

//OPCIONES ABM
//OPCION 2
void Agregar_Clientes_BIN(vector<Clientes> Nuevos);
//OPCION 3
void Opciones_Busqueda_Clientes(vector <Clientes> Lista_Clientes);
void Buscar_Nombre_Cliente(vector <Clientes> Lista_Clientes);
void Buscar_Apellido_Cliente(vector <Clientes> Lista_Clientes);
void Buscar_CI_Cliente(vector <Clientes> Lista_Clientes);
//OPCION 4
Clientes Sub_Menu_Editar_Clientes(Clientes Datos_Cliente);
void Editar_Datos_Cliente(vector<Clientes>& Lista_Clientes);
//OPCION 5 
void Borrar_Cliente(vector<Clientes> Lista_Clientes);

//FUNCIONES CLIENTES
vector <Clientes> Resgistro_Clientes()
{
   system ("cls");
   vector <Clientes> Lista_Clientes;
   Clientes Datos_Clientes;
   string Almacenador_Datos = "";
   int numero_clientes = 0;
   bool verificador = true;
   do {
      system ("cls");
      cout<<"Ingrese cuantos clientes desea registrar: ";
      getline(cin, Almacenador_Datos);
      if (Validar_Datos_Numericos(Almacenador_Datos))
      {
      stringstream numeros(Almacenador_Datos);
      numeros>> numero_clientes; 
      Almacenador_Datos = "";
      verificador = true;
      }
      else
      {
      system("cls");
      cout<< "Opcion invalida. ";
      system("pause");
      Almacenador_Datos = "";
      verificador = false;
      }
      } while (verificador != true);
   for (int i = 0; i < numero_clientes; i++)
   {
     cout<<"Ingrese los datos del cliente ["<<i+1<<"]"<<endl;
     do {
            cout << "Ingrese los nombres del cliente: ";
            getline(cin, Almacenador_Datos);
            if (Validar_Datos_Caracteres(Almacenador_Datos))
            {
                strcpy(Datos_Clientes.Nombres, Almacenador_Datos.c_str());
                Almacenador_Datos = "";
                verificador = true;
            }
            else
            {
                cout << "El nombre solo puede contener letras y espacios. Registre denuevo los nombres del cliente." << endl;
                Almacenador_Datos = "";
                verificador = false;
            }
        } while (verificador != true);
      do {
            cout << "Ingrese los apellidos del cliente: ";
            getline(cin, Almacenador_Datos);
            if (Validar_Datos_Caracteres(Almacenador_Datos))
            {
                strcpy(Datos_Clientes.Apellidos, Almacenador_Datos.c_str());
                Almacenador_Datos = "";
                verificador = true;
            }
            else
            {
                cout << "El apellido solo puede contener letras y espacios. Registre denuevo los apellidos del cliente." << endl;
                Almacenador_Datos = "";
                verificador = false;
            }
        } while (verificador != true);
        //Correo
            cout << "Ingrese el correo del cliente: ";
            getline(cin, Almacenador_Datos);
            strcpy(Datos_Clientes.Correo, Almacenador_Datos.c_str());
            Almacenador_Datos = "";
        do {
            cout<<"Ingrese el Nro_CI del cliente: ";
            getline(cin, Almacenador_Datos);
            if (Validar_Datos_Numericos(Almacenador_Datos))
            {
                stringstream numeros(Almacenador_Datos);
                numeros>> Datos_Clientes.Nro_CI; 
                Almacenador_Datos = "";
                verificador = true;
            }
            else
            {
                cout << "El Nro_CI solo puede contener numeros. Registre denuevo el Nro_CI del cliente." << endl;
                Almacenador_Datos = "";
                verificador = false;
            }
        } while (verificador != true);
        do {
            cout<<"Ingrese el telefono del cliente: ";
            getline(cin, Almacenador_Datos);
            if (Validar_Datos_Numericos(Almacenador_Datos))
            {
                stringstream numeros(Almacenador_Datos);
                numeros>> Datos_Clientes.Telefono; 
                Almacenador_Datos = "";
                verificador = true;
            }
            else
            {
                cout << "El telefono solo puede contener numeros. Registre denuevo el telefono del cliente." << endl;
                Almacenador_Datos = "";
                verificador = false;
            }
        } while (verificador != true);
     Lista_Clientes.push_back(Datos_Clientes);
   }
   return Lista_Clientes;
}

//FUNCIONES ARCHIVOS .TXT
void Crear_Lista_Clientes_txt(vector <Clientes> Lista_Clientes)
{
    if (Lista_Clientes.empty())
    {
    system("cls");
    cout<<"No se pueede crear el archivo porque no se registraron clientes"<<endl;
    system("pause");
    }
    else
    {
        ofstream archivo;
        archivo.open("Lista_de_Clientes.txt", ios::out);
        if (archivo.fail())
        {
        cout<<"No se logro crear el archivo con exito."<<endl; 
        }
        else
        {
        for (int i = 0; i < Lista_Clientes.size(); i++)
        {
            archivo << Lista_Clientes[i].Nombres << ",";
            archivo << Lista_Clientes[i].Apellidos << ",";
            archivo << Lista_Clientes[i].Nro_CI << ",";
            archivo << Lista_Clientes[i].Correo << ",";
            archivo << Lista_Clientes[i].Telefono<< endl; 
        }
        system("cls");
        cout << "Archivo 'Lista_de_Clientes.txt' fue creado exitosamente." << endl;
        archivo.close();
        system("pause");
        }
        }
}

//FUNCIONES ARCHIVOS .BIN
/***************************************************************************************************/
void Crear_Lista_Clientes_bin(vector<Clientes>& Lista_Clientes)
{
    ofstream archivo;
    archivo.open("Lista_de_Clientes.bin", ios::binary | ios::trunc);  
    if (archivo.fail())
    {
    cout<<"El archivo no se logro crear con exito"<<endl;
    } 
    else
    {
        for (Clientes i : Lista_Clientes )
        {
            archivo.write((char*)&i, sizeof(Clientes));
        }
        cout << "Se registro la lista de clientes. "<<endl;
        system("pause");
    archivo.close();
    }
}
/***************************************************************************************************/
vector <Clientes> Leer_Lista_Clientes_bin()
{
    system("cls");
    ifstream archivo;
    Clientes Datos_Clientes;
    vector<Clientes>Lista_Clientes;
    archivo.open("Lista_de_Clientes.bin", ios::binary);  
    if (archivo.fail())
    {
    cout<<"El archivo no se logro abrir con exito"<<endl;
    system("pause");
    } 
    else
    {
    while (archivo.read((char*)&Datos_Clientes, sizeof(Clientes)))
    {
        Lista_Clientes.push_back(Datos_Clientes);
    }
    cout << "Lista de clientes cargada al sistema. "<<endl;
    system("pause");
    }
    archivo.close();
    return Lista_Clientes;
}


//MENU PRINCIPAL DE CLIENTES
void Menu_Clientes ()
{
   vector <Clientes> Lista_Clientes;
   int opcion_numerica = 0;
   do
   {
      string opcion;
      bool verificador= true;
      system("cls");
      cout<<"MENU CLIENTES "<<endl;
      cout<<"1. Registrar Clientes "<<endl;
      cout<<"2. Mostrar Lista de Clientes "<<endl;
      cout<<"3. Listar Clientes en un archivo .txt"<<endl;
      cout<<"4. Cargar lista de clientes"<<endl;
      cout<<"0. Salir"<<endl;
      do {
            cout<<"Ingrese una opcion: ";
            getline(cin, opcion);
            if (Validar_Datos_Numericos(opcion))
            {
                stringstream numeros(opcion);
                numeros>> opcion_numerica; 
                verificador = true;
            }
            else
            {
                cout << "Opcion Invalida!." << endl;
                verificador = false;
            }
      } while (verificador != true);
      switch (opcion_numerica)
      {
      case 1:
         Sub_Menu_Registrar_Clientes(Lista_Clientes);
         break;
      case 2:
         Imprimir_Vectores_Clientes(Lista_Clientes);
         break;
      case 3:
         Crear_Lista_Clientes_txt( Lista_Clientes);
         break;
      case 4:
         Lista_Clientes = Leer_Lista_Clientes_bin();
         break;
      default:
         break;
      }
   } while (opcion_numerica != 0);
   
}
//FUNCIONES AUXILIARES
void Imprimir_Vectores_Clientes(vector <Clientes>& Lista_Clientes)
{
  system("cls");
  if(Lista_Clientes.empty())
  {
  cout<<"La lista de clientes esta vacia. "<<endl;
  }
  else
  {
  for (int i = 0; i < Lista_Clientes.size(); i++)
  {
   cout<<"Datos del cliente ["<<i+1<<"]"<<endl;
   cout<<"Los nombres del cliente es: "<<Lista_Clientes[i].Nombres<<endl;
   cout<<"Los apellidos del clientes es: "<<Lista_Clientes[i].Apellidos<<endl;
   cout<<"El Nro_CI del cliente es: "<<Lista_Clientes[i].Nro_CI<<endl;
   cout<<"El correo del cliente es: "<<Lista_Clientes[i].Correo<<endl;
   cout<<"El telefono del cliente es: "<<Lista_Clientes[i].Telefono<<endl;
  }
  }
  system ("pause");
}

void Imprimir_Clientes(Clientes Datos_Cliente)
{
   cout<<"=========================="<<endl;
   cout<<"Los nombres del cliente es: "<<Datos_Cliente.Nombres<<endl;
   cout<<"Los apellidos del clientes es: "<<Datos_Cliente.Apellidos<<endl;
   cout<<"El Nro_CI del cliente es: "<<Datos_Cliente.Nro_CI<<endl;
   cout<<"El correo del cliente es: "<<Datos_Cliente.Correo<<endl;
   cout<<"El telefono del cliente es: "<<Datos_Cliente.Telefono<<endl;
   cout<<"=========================="<<endl;
}

vector <Clientes> Leer_Archivo_BIN_estructura_clientes()
{
    system("cls");
    ifstream archivo;
    Clientes Datos_Cliente;
    vector<Clientes> Lista_Clientes;
    archivo.open("Lista_de_Clientes.bin", ios::binary);  
    if (archivo.fail())
    {
    cout<<"El archivo no se logro abrir con exito"<<endl;
    system("pause");
    } 
    else
    {
    while (archivo.read((char*)&Datos_Cliente, sizeof(Clientes)))
    {
        Lista_Clientes.push_back(Datos_Cliente);
    }
    }
    archivo.close();
    return Lista_Clientes;
}

//SUB MENU REGISTRAR TRABAJADORES
void Sub_Menu_Registrar_Clientes(vector<Clientes>& Lista_Clientes)
{
    int opcion_numerica;
    bool verificador =true;
    string Almacenador_Datos;
    vector <Clientes> Lista_Clientes_Aniadidos;
    do
    {
     do {
        system("cls");
        cout<<"REGISTRAR CLIENTES"<<endl;
        cout<<"1. Crear Lista Nueva de Cliente"<<endl;
        cout<<"2. Aniadir Cliente"<<endl;
        cout<<"3. Buscar Cliente"<<endl;
        cout<<"4. Editar Cliente"<<endl;
        cout<<"5. Borrar Cliente"<<endl;
        cout<<"0. Salir"<<endl;
        cout<<"Ingrese una opcion: ";
        getline(cin, Almacenador_Datos);
        if (Validar_Datos_Numericos(Almacenador_Datos))
        {
            stringstream numeros(Almacenador_Datos);
            numeros>> opcion_numerica; 
            Almacenador_Datos = "";
            verificador = true;
        }
        else
        {
            system("cls");
            cout<< "Opcion invalida. ";
            system("pause");
            Almacenador_Datos = "";
            verificador = false;
        }
      } while (verificador != true);
    switch (opcion_numerica)
    {
    case 1:
        system("cls");
        Lista_Clientes = Resgistro_Clientes();
        Imprimir_Vectores_Clientes(Lista_Clientes);
        Crear_Lista_Clientes_bin(Lista_Clientes); 
        break;
    case 2:
        system("cls");
        Lista_Clientes = Leer_Archivo_BIN_estructura_clientes();
        Lista_Clientes_Aniadidos = Resgistro_Clientes();
        Agregar_Clientes_BIN(Lista_Clientes_Aniadidos);
        for (Clientes Datos_Clientes : Lista_Clientes_Aniadidos)
        {
            Lista_Clientes.push_back(Datos_Clientes);
        }
        Imprimir_Vectores_Clientes(Lista_Clientes);
        break;
    case 3:    
        system("cls");
        Lista_Clientes = Leer_Archivo_BIN_estructura_clientes();
        Opciones_Busqueda_Clientes( Lista_Clientes);
        break;
    case 4:
        Editar_Datos_Cliente(Lista_Clientes);
        break;
    case 5:
        Borrar_Cliente( Lista_Clientes);
        break;
    }
    } while (opcion_numerica!=0);
}

//OPCION 2 ANIADOR TRABAJADORES
//ANIADIR TRABAJADOR
void Agregar_Clientes_BIN(vector<Clientes> Nuevos_Clientes)
{
    ofstream archivo("Lista_de_Clientes.bin", ios::binary | ios::app);
    if (archivo.fail())
    {
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }
    else
    {
        for (Clientes Datos_Cliente : Nuevos_Clientes)
        {
        archivo.write((char*)&Datos_Cliente, sizeof(Clientes));
        }
    }
    archivo.close();
    cout << "Se registraron nuevos clientes."<<endl;
    system("pause");
}

//OPCION 3 BUSCAR TRABJADORES
void Opciones_Busqueda_Clientes(vector <Clientes> Lista_Clientes)
{
    system("cls");
    int opcion = 0;
    string Almacenador_Datos;
    bool verificador = true;
    do {
        cout<<"OPCIONES DE BUSQUEDA"<<endl;
        cout<<"1. Buscar por Nombre. "<<endl;
        cout<<"2. Buscar por Apellido. "<<endl;
        cout<<"3. Buscar por CI. "<<endl;
        cout<<"Seleccione una opcion de busqueda: "<<endl;
        getline(cin, Almacenador_Datos);
        if (Validar_Datos_Numericos(Almacenador_Datos))
        {
            stringstream numeros(Almacenador_Datos);
            numeros>> opcion; 
            Almacenador_Datos = "";
            verificador = true;
        }
        else
        {
            system("cls");
            cout<< "Opcion invalida. "<<endl;
            system("pause");
            Almacenador_Datos = "";
            verificador = false;
        }
      } while (verificador != true);
    switch (opcion)
    {
    case 1:
        Buscar_Nombre_Cliente(Lista_Clientes);
        break;
    case 2:
        Buscar_Apellido_Cliente(Lista_Clientes);
        break;
    case 3:
        Buscar_CI_Cliente(Lista_Clientes);
        break;
    default:
        break;
    }
}

//OPCION BUSCAR NOMBRE
void Buscar_Nombre_Cliente(vector <Clientes> Lista_Clientes)
{
    if (Lista_Clientes.empty())
    {
        system("cls");
        cout<<"Lista de clientes vacia. "<<endl;
        system("pause");
    }
    else
    {
        string nombre;
        string nombre_cliente;
        system("cls");
        cout<<"Ingrese el nombre a buscar. ";
        getline(cin,nombre);
        for (int i = 0; i < Lista_Clientes.size(); i++)
        {
            nombre_cliente=Lista_Clientes[i].Nombres;
            if (Comparador_de_Strings(nombre,nombre_cliente))
            {
                Imprimir_Clientes(Lista_Clientes[i]);
            }
        }
        system("pause");
    }
}

// OPCION BUSCAR APELLIDO
void Buscar_Apellido_Cliente(vector <Clientes> Lista_Clientes)
{
    if (Lista_Clientes.empty())
    {
        system("cls");
        cout<<"Lista de clientes vacia. "<<endl;
        system("pause");
    }
    else
    {
        string apellido;
        string apellido_cliente;
        system("cls");
        cout<<"Ingrese el apellido a buscar. ";
        getline(cin,apellido);
        for (int i = 0; i < Lista_Clientes.size(); i++)
        {
            apellido_cliente=Lista_Clientes[i].Apellidos;
            if (Comparador_de_Strings(apellido,apellido_cliente))
            {
                Imprimir_Clientes(Lista_Clientes[i]);
            }
        }
        system("pause");
    }
}

//OPCION BUSCAR CI
void Buscar_CI_Cliente(vector <Clientes> Lista_Clientes)
{
    string Nro_CI;
    if (Lista_Clientes.empty())
    {
        system("cls");
        cout<<"Lista de clientes vacia. "<<endl;
        system("pause");
    }
    else
    {
        system("cls");
        cout<<"Ingrese el Nro_CI del cliente. ";
        getline(cin,Nro_CI);
        for (int i = 0; i < Lista_Clientes.size(); i++)
        {
            if (Comparador_de_Strings(Nro_CI,to_string(Lista_Clientes[i].Nro_CI)))
            {
                Imprimir_Clientes(Lista_Clientes[i]);
            }
        }
        system("pause");
    }
}

//OPCION EDITAR DATOS TRABAJADOR
void Editar_Datos_Cliente(vector<Clientes>& Lista_Clientes)
{
    if (Lista_Clientes.empty())
    {
        system("cls");
        cout << "Lista vacia." << endl;
        system("pause");
        return;
    }
    else
    {
        int contador=0;
        string Nro_CI;
        system("cls");
        cout << "Ingrese el CI del cliente a editar: ";
        getline(cin, Nro_CI);
        for (int i = 0; i < Lista_Clientes.size(); i++)
        {
            if (Nro_CI == to_string(Lista_Clientes[i].Nro_CI))
            {
                cout << "Cliente encontrado: "<<endl;
                Imprimir_Clientes(Lista_Clientes[i]);
                Lista_Clientes[i] = Sub_Menu_Editar_Clientes(Lista_Clientes[i]);
                cout << "Datos actualizados correctamente.";
                system("pause");
                contador++;
                break;
            }
        }
        Crear_Lista_Clientes_bin(Lista_Clientes);
        if (contador == 0)
        {
            cout << "No existe un cliente con ese CI." << endl;
            system("pause");
        }
        }
}

Clientes Sub_Menu_Editar_Clientes(Clientes Datos_Cliente)
{
    int opcion = 0;
    string Almacenador_Datos;
    bool verificador=true;
    string texto;
    int numero;
    do {
        cout << "EDITAR DATOS DEL CLIENTE";
        cout << "1. Editar Nombre"<<endl;
        cout << "2. Editar Apellido"<<endl;
        cout << "3. Editar CI"<<endl;
        cout << "4. Editar Correo"<<endl;
        cout << "5. Editar Telefono"<<endl;
        cout << "Seleccione una opcion: ";
        getline(cin, Almacenador_Datos);
        if (Validar_Datos_Numericos(Almacenador_Datos))
        {
            stringstream numeros(Almacenador_Datos);
            numeros>> opcion; 
            Almacenador_Datos = "";
            verificador = true;
        }
        else
        {
            system("cls");
            cout<< "Opcion invalida. "<<endl;
            system("pause");
            Almacenador_Datos = "";
            verificador = false;
        }
      } while (verificador != true);
    switch (opcion)
    {
    case 1:
        system("cls");
        cout << "Ingrese el nuevo nombre: ";
        getline(cin, texto);
        strcpy(Datos_Cliente.Nombres, texto.c_str());
        break;
    case 2:
        system("cls");
        cout << "Ingrese el nuevo apellido: ";
        getline(cin, texto);
        strcpy(Datos_Cliente.Apellidos, texto.c_str());
        break;
    case 3:
        system("cls");
        cout << "Ingrese el nuevo CI: ";
        getline(cin, texto);
        numero = stoi(texto);
        Datos_Cliente.Nro_CI = numero;
        break;
    case 4:
        system("cls");
        cout << "Ingrese el nuevo correo: ";
        getline(cin, texto);
        strcpy(Datos_Cliente.Correo, texto.c_str());
        break;
    case 5:
        system("cls");
        cout << "Ingrese el nuevo telefono: ";
        getline(cin, texto);
        numero = stoi(texto);
        Datos_Cliente.Telefono = numero;
        break;
    default:
        cout << "Opcion invalida."<<endl;
        break;
    }
    return Datos_Cliente;
}

//OPCION BORRAR CLIENTE LISTA
void Borrar_Cliente(vector<Clientes> Lista_Clientes)
{
    if (Lista_Clientes.empty())
    {
        system("cls");
        cout << "Lista vacia." << endl;
        system("pause");
        return;
    }
    else
    {
        system("cls");
        string Nro_CI;
        vector<Clientes> Lista_Nueva;
        cout << "Ingrese el CI del cliente a borrar: ";
        getline(cin, Nro_CI);
        bool encontrado = false;
        for (int i = 0; i < Lista_Clientes.size(); i++)
        {
            if (to_string(Lista_Clientes[i].Nro_CI) == Nro_CI)
            {
                cout << "Cliente Borrado:"<<endl;
                Imprimir_Clientes(Lista_Clientes[i]);
                encontrado = true;
            }
            else
            {
                Lista_Nueva.push_back(Lista_Clientes[i]);
            }
        }
        if (!encontrado)
        {
            cout << "No existe un cliente con ese CI.";
            system("pause");
            return;
        }
        Crear_Lista_Clientes_bin(Lista_Nueva);
        cout << "El cliente fue eliminado correctamente."<<endl;
        system("pause");
    }
}