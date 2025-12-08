#include <iostream>
#include <vector>
#include <string.h>
#include <cctype>
#include <sstream>
#include <fstream>

using namespace std;

struct Trabajadores
{
char Nombres [50];
char Apellidos [50];
char Cargo  [40];
int  Nro_CI;
int  Sueldo;
};
//Registro
vector <Trabajadores> Resgistro_Trabajadores();
bool Validar_Datos_Caracteres(string Datos_Registrados);
bool Validar_Datos_Numericos(string Datos_Registrados );
void Imprimir_Vectores_Trabajadores(vector <Trabajadores>& Lista_Trabajadores);
//Menu
void Menu_Trabajadores ();
//Archivos .txt
void Crear_Lista_Trabajadores_txt(vector <Trabajadores> Lista_Trabajadores);
void Cargar_Lista_Trabajadores_txt(vector <Trabajadores>& Lista_Trabajadores);
//Archivos .bin
void Crear_Lista_Trabajadores_bin(vector<Trabajadores>& Lista_Trabajadores);
vector <Trabajadores> Leer_Lista_Trabajadores_bin();
vector <Trabajadores> Leer_Archivo_BIN_estructura();

//Funciones de ABM
void Imprimir_Trabajadores(Trabajadores Datos_Trabajador);
bool Comparador_de_Strings(string nombre_buscado, string nombre_trabajador);
string Volver_Cadena_Minuscula(string cadena_caracteres);

//SUB MENU REGISTRO TRABAJADORES
void Sub_Menu_Registrar_Trabajadores(vector<Trabajadores>& Lista_Trabajadores);

//OPCIONES ABM
//OPCION 2
void Agregar_Trabajadores_BIN(vector<Trabajadores> Nuevos);
//OPCION 3
void Opciones_Busqueda(vector <Trabajadores> Lista_Trabajadores);
void Buscar_Nombre(vector <Trabajadores> Lista_Trabajadores);
void Buscar_Apellido(vector <Trabajadores> Lista_Trabajadores);
void Buscar_CI(vector <Trabajadores> Lista_Trabajadores);
//OPCION 4
Trabajadores Sub_Menu_Editar_Trabajador(Trabajadores Datos_Trabajador);
void Editar_Datos(vector<Trabajadores> Lista_Trabajadores);
//OPCION 5 
void Borrar_Trabajador(vector<Trabajadores> Lista_Trabajadores);

//FUNCIONES TRABAJADORES
vector <Trabajadores> Resgistro_Trabajadores()
{
   system ("cls");
   vector <Trabajadores> Lista_Trabajadores;
   Trabajadores Datos_Trabajador;
   string Almacenador_Datos = "";
   int numero_trabajadores = 0;
   bool verificador = true;
   do {
      system ("cls");
      cout<<"Ingrese cuantos trabajadores desea registrar: ";
      getline(cin, Almacenador_Datos);
      if (Validar_Datos_Numericos(Almacenador_Datos))
      {
      stringstream numeros(Almacenador_Datos);
      numeros>> numero_trabajadores; 
      Almacenador_Datos = "";
      verificador = true;
      }
      else
      {
      system("cls");
      cout<< "Opcion invalida. ";
      cout << "Ingrese un numero para comenzar el registro." << endl;
      system("pause");
      Almacenador_Datos = "";
      verificador = false;
      }
      } while (verificador != true);
   for (int i = 0; i < numero_trabajadores; i++)
   {
     cout<<"Ingrese los datos del trabajador ["<<i+1<<"]"<<endl;
     do {
            cout << "Ingrese los nombres del trabajador: ";
            getline(cin, Almacenador_Datos);
            if (Validar_Datos_Caracteres(Almacenador_Datos))
            {
                strcpy(Datos_Trabajador.Nombres, Almacenador_Datos.c_str());
                Almacenador_Datos = "";
                verificador = true;
            }
            else
            {
                cout << "El nombre solo puede contener letras y espacios. Registre denuevo los nombres del trabajador." << endl;
                Almacenador_Datos = "";
                verificador = false;
            }
        } while (verificador != true);
      do {
            cout << "Ingrese los apellidos del trabajador: ";
            getline(cin, Almacenador_Datos);
            if (Validar_Datos_Caracteres(Almacenador_Datos))
            {
                strcpy(Datos_Trabajador.Apellidos, Almacenador_Datos.c_str());
                Almacenador_Datos = "";
                verificador = true;
            }
            else
            {
                cout << "El apellido solo puede contener letras y espacios. Registre denuevo los apellidos del trabajador." << endl;
                Almacenador_Datos = "";
                verificador = false;
            }
        } while (verificador != true);
        do {
            cout << "Ingrese el cargo del trabajador: ";
            getline(cin, Almacenador_Datos);
            if (Validar_Datos_Caracteres(Almacenador_Datos))
            {
                strcpy(Datos_Trabajador.Cargo, Almacenador_Datos.c_str());
                Almacenador_Datos = "";
                verificador = true;
            }
            else
            {
                cout << "El cargo solo puede contener letras y espacios. Registre denuevo el cargo del trabajador." << endl;
                Almacenador_Datos = "";
                verificador = false;
            }
        } while (verificador != true);
        do {
            cout<<"Ingrese el Nro_CI del trabajador: ";
            getline(cin, Almacenador_Datos);
            if (Validar_Datos_Numericos(Almacenador_Datos))
            {
                stringstream numeros(Almacenador_Datos);
                numeros>> Datos_Trabajador.Nro_CI; 
                Almacenador_Datos = "";
                verificador = true;
            }
            else
            {
                cout << "El Nro_CI solo puede contener numeros. Registre denuevo el Nro_CI del trabajador." << endl;
                Almacenador_Datos = "";
                verificador = false;
            }
        } while (verificador != true);
        do {
            cout<<"Ingrese el sueldo del trabajador: ";
            getline(cin, Almacenador_Datos);
            if (Validar_Datos_Numericos(Almacenador_Datos))
            {
                stringstream numeros(Almacenador_Datos);
                numeros>> Datos_Trabajador.Sueldo; 
                Almacenador_Datos = "";
                verificador = true;
            }
            else
            {
                cout << "El sueldo solo puede contener numeros. Registre denuevo el sueldo del trabajador." << endl;
                Almacenador_Datos = "";
                verificador = false;
            }
        } while (verificador != true);
     Lista_Trabajadores.push_back(Datos_Trabajador);
   }
   return Lista_Trabajadores;
}

bool Validar_Datos_Caracteres(string Datos_Registrados )
{
    if (Datos_Registrados.empty()) {
        return false;
    }
    
    for (char c : Datos_Registrados)
    {
        if (!isalpha(c) && !isspace(c))
        {
            return false; 
        }
    }
    return true; 
}

bool Validar_Datos_Numericos(string Datos_Registrados )
{
    if (Datos_Registrados.empty()) {
        return false;
    }
    
    for (char c : Datos_Registrados)
    {
        if (!isdigit(c))
        {
            return false; 
        }
    }
    return true; 
}

//FUNCIONES ARCHIVOS .TXT
void Crear_Lista_Trabajadores_txt(vector <Trabajadores> Lista_Trabajadores)
{
    if (Lista_Trabajadores.empty())
    {
    system("cls");
    cout<<"No se pueede crear el archivo porque no se registraron trabajadores"<<endl;
    system("pause");
    }
    else
    {
        ofstream archivo;
    archivo.open("Lista_de_Trabajadores.txt", ios::out);
    if (archivo.fail())
    {
      cout<<"No se logro crear el archivo con exito."<<endl; 
    }
    else
    {
      for (int i = 0; i < Lista_Trabajadores.size(); i++)
      {
        archivo << Lista_Trabajadores[i].Nombres << ",";
        archivo << Lista_Trabajadores[i].Apellidos << ",";
        archivo << Lista_Trabajadores[i].Cargo << ",";
        archivo << Lista_Trabajadores[i].Nro_CI << ",";
        archivo << Lista_Trabajadores[i].Sueldo << endl; 
      }
     system("cls");
     cout << "Archivo 'Lista_de_Trabajadores.txt' fue creado exitosamente." << endl;
     archivo.close();
     system("pause");
    }
    }
}

void Cargar_Lista_Trabajadores_txt(vector <Trabajadores> &Lista_Trabajadores)
{
    if (!Lista_Trabajadores.empty())
    {
    system("cls");
    cout<<"El sistema esta cargado de una lista previa de trabajadores"<<endl;
    system("pause");
    }
    else
    {
    ifstream archivo("Lista_de_Trabajadores.txt", ios::in);
    if (archivo.fail())
    {
        system("cls");
        cout << "No se logro abrir el archivo con exito" << endl;
        system("pause");
    }
    else
    {
    string linea;
    while (getline(archivo, linea))
    {
        stringstream partes_linea(linea);
        string nombre, apellido, cargo, ci, sueldo;
        getline(partes_linea, nombre, ',');
        getline(partes_linea, apellido, ',');
        getline(partes_linea, cargo, ',');
        getline(partes_linea, ci, ',');
        getline(partes_linea, sueldo, ',');
        if (!nombre.empty() && nombre[0] == ' ') nombre.erase(0, 1);
        if (!apellido.empty() && apellido[0] == ' ') apellido.erase(0, 1);
        if (!cargo.empty() && cargo[0] == ' ') cargo.erase(0, 1);
        Trabajadores Datos_Trabajador;
        strcpy(Datos_Trabajador.Nombres, nombre.c_str());
        strcpy(Datos_Trabajador.Apellidos, apellido.c_str());
        strcpy(Datos_Trabajador.Cargo, cargo.c_str());
        Datos_Trabajador.Nro_CI = stoi(ci);
        Datos_Trabajador.Sueldo = stoi(sueldo);
        Lista_Trabajadores.push_back(Datos_Trabajador);
    }
    system("cls");
    cout << "Se logro cargar los datos del archivo de texto." << endl;
    system("pause");
    }
    archivo.close();
    }
}

//FUNCIONES ARCHIVOS .BIN
void Crear_Lista_Trabajadores_bin(vector<Trabajadores>& Lista_Trabajdores)
{
    ofstream archivo;
    archivo.open("Lista_de_Trabajadores.bin", ios::binary | ios::trunc);  
    if (archivo.fail())
    {
    cout<<"El archivo no se loro crear con exito"<<endl;
    } 
    else
    {
        for (Trabajadores i : Lista_Trabajdores )
        {
        archivo.write((char*)&i, sizeof(Trabajadores));
        }
        cout << "Se registro la lista de trabajadores. "<<endl;
        system("pause");
    }
    archivo.close();
}

vector <Trabajadores> Leer_Lista_Trabajadores_bin()
{
    system("cls");
    ifstream archivo;
    Trabajadores Datos_Trabajador;
    vector<Trabajadores>Lista_Trabajadores;
    archivo.open("Lista_de_Trabajadores.bin", ios::binary);  
    if (archivo.fail())
    {
    cout<<"El archivo no se logro abrir con exito"<<endl;
    system("pause");
    } 
    else
    {
    while (archivo.read((char*)&Datos_Trabajador, sizeof(Trabajadores)))
    {
        Lista_Trabajadores.push_back(Datos_Trabajador);
    }
    cout << "Lista de trabajadores cargada al sistema. "<<endl;
    system("pause");
    }
    archivo.close();
    return Lista_Trabajadores;
}


//MENU PRINCIPAL DE TRABAJADORES
void Menu_Trabajadores ()
{
   int opcion_numerica = 1;
   vector <Trabajadores> Lista_Trabajadores;
   do
   {
      string opcion;
      bool verificador= true;
      system("cls");
      cout<<"MENU TRABAJADORES "<<endl;
      cout<<"1. Registrar Trabajadores "<<endl;
      cout<<"2. Mostrar Lista de Trabajadores "<<endl;
      cout<<"3. Listar Trabajadores en un archivo .txt"<<endl;
      cout<<"4. Cargar lista de trabajadores"<<endl;
      cout<<"5. Cargar lista de trabajadores desde un archivo .txt"<<endl;
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
         Sub_Menu_Registrar_Trabajadores(Lista_Trabajadores);
         break;
      case 2:
         Imprimir_Vectores_Trabajadores(Lista_Trabajadores);
         break;
      case 3:
         Crear_Lista_Trabajadores_txt( Lista_Trabajadores);
         break;
      case 4:
         Lista_Trabajadores = Leer_Lista_Trabajadores_bin();
         break;
      case 5:
         Cargar_Lista_Trabajadores_txt(Lista_Trabajadores);
         break;
      default:
         break;
      }
   } while (opcion_numerica != 0);
   
}

//FUNCIONES AUXILIARES
void Imprimir_Vectores_Trabajadores(vector <Trabajadores>& Lista_Trabajadores)
{
  system("cls");
  if(Lista_Trabajadores.empty())
  {
  cout<<"La lista de trbajadores esta vacia. "<<endl;
  }
  else
  {
  for (int i = 0; i < Lista_Trabajadores.size(); i++)
  {
   cout<<"Datos del trabajador ["<<i+1<<"]"<<endl;
   cout<<"Los nombres del trabajador es: "<<Lista_Trabajadores[i].Nombres<<endl;
   cout<<"Los apellidos del trabajador es: "<<Lista_Trabajadores[i].Apellidos<<endl;
   cout<<"El Nro_CI del trabajador es: "<<Lista_Trabajadores[i].Nro_CI<<endl;
   cout<<"El cargo del trabajadr es: "<<Lista_Trabajadores[i].Cargo<<endl;
   cout<<"El sueldo del trabajador es: "<<Lista_Trabajadores[i].Sueldo<<endl;
  }
  }
  system ("pause");
}

void Imprimir_Trabajadores(Trabajadores Datos_Trabajador)
{
   cout<<"=========================="<<endl;
   cout<<"Nombres del trabajador es: "<<Datos_Trabajador.Nombres<<endl;
   cout<<"Apellidos del trabajador es: "<<Datos_Trabajador.Apellidos<<endl;
   cout<<"Nro.CI del trabajador es: "<<Datos_Trabajador.Nro_CI<<endl;
   cout<<"Cargo del trabajador es: "<<Datos_Trabajador.Cargo<<endl;
   cout<<"Sueldo del trabajador es: "<<Datos_Trabajador.Sueldo<<endl;
   cout<<"=========================="<<endl;
}

vector <Trabajadores> Leer_Archivo_BIN_estructura()
{
    system("cls");
    ifstream archivo;
    Trabajadores Datos_Trabajador;
    vector<Trabajadores>Lista_Trabajadores;
    archivo.open("Lista_de_Trabajadores.bin", ios::binary);  
    if (archivo.fail())
    {
    cout<<"El archivo no se logro abrir con exito"<<endl;
    system("pause");
    } 
    else
    {
    while (archivo.read((char*)&Datos_Trabajador, sizeof(Trabajadores)))
    {
        Lista_Trabajadores.push_back(Datos_Trabajador);
    }
    }
    archivo.close();
    return Lista_Trabajadores;
}

bool Comparador_de_Strings(string nombre_buscado, string nombre_trabajador)
{
    nombre_buscado = Volver_Cadena_Minuscula(nombre_buscado);
    stringstream nombre_buscado_partes(nombre_buscado);
    string nombre_buscado_auxiliar;
    vector <string> nombre_buscado_vector;
    while (nombre_buscado_partes>>nombre_buscado_auxiliar)
    {
        nombre_buscado_vector.push_back(nombre_buscado_auxiliar);
    }

    nombre_trabajador = Volver_Cadena_Minuscula(nombre_trabajador);
    stringstream nombre_trabajadro_partes(nombre_trabajador);
    string nombre_trabajador_auxiliar;
    vector <string> nombre_trabajador_vector;
    while (nombre_trabajadro_partes>>nombre_trabajador_auxiliar)
    {
        nombre_trabajador_vector.push_back(nombre_trabajador_auxiliar);
    }
    
    for (string palabra_buscada : nombre_buscado_vector)
    {
        for (string palabra_trabajador : nombre_trabajador_vector)
        {
            if (palabra_buscada == palabra_trabajador)
            {
                return true; 
            }
        }
    }
    return false; 
}

string Volver_Cadena_Minuscula(string cadena_caracteres)
{
    for (int i = 0; i < cadena_caracteres.length(); i++)
    {
        cadena_caracteres[i] = tolower(cadena_caracteres[i]);
    }
    return cadena_caracteres;
}

//SUB MENU REGISTRAR TRABAJADORES
void Sub_Menu_Registrar_Trabajadores(vector<Trabajadores>& Lista_Trabajadores)
{
    int opcion_numerica;
    bool verificador =true;
    string Almacenador_Datos;
    vector <Trabajadores> Lista_Trabajadores_Aniadidos;
    do
    {
     do {
        system("cls");
        cout<<"REGISTRAR TRABAJADORES"<<endl;
        cout<<"1. Crear Nueva Lista de Trabajadores"<<endl;
        cout<<"2. Aniadir Trabajador"<<endl;
        cout<<"3. Buscar Trabajador"<<endl;
        cout<<"4. Editar Trabajador"<<endl;
        cout<<"5. Borrar Trabajador"<<endl;
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
            cout << "Ingrese un numero para comenzar el registro." << endl;
            system("pause");
            Almacenador_Datos = "";
            verificador = false;
        }
      } while (verificador != true);
    switch (opcion_numerica)
    {
    case 1:
        system("cls");
        Lista_Trabajadores = Resgistro_Trabajadores();
        Imprimir_Vectores_Trabajadores(Lista_Trabajadores);
        Crear_Lista_Trabajadores_bin(Lista_Trabajadores);
        break;
    case 2:
        system("cls");
        Lista_Trabajadores = Leer_Archivo_BIN_estructura();
        if (Lista_Trabajadores.empty())
        {
            cout << "La lista esta vacia" << endl;
            system("pause");
        }
        else
        {
            Lista_Trabajadores_Aniadidos = Resgistro_Trabajadores();
            Agregar_Trabajadores_BIN(Lista_Trabajadores_Aniadidos);
            for (Trabajadores Datos_Trabajadores : Lista_Trabajadores_Aniadidos)
            {
                Lista_Trabajadores.push_back(Datos_Trabajadores);
            }
            Imprimir_Vectores_Trabajadores(Lista_Trabajadores);
        }
        break;
    case 3:    
        system("cls");
        Lista_Trabajadores = Leer_Archivo_BIN_estructura();
        Opciones_Busqueda( Lista_Trabajadores);
        break;
    case 4:
        Editar_Datos(Lista_Trabajadores);
        break;
    case 5:
        Borrar_Trabajador( Lista_Trabajadores);
        break; 
    }
    } while (opcion_numerica!=0);
}

//OPCION 2 ANIADOR TRABAJADORES
//ANIADIR TRABAJADOR
void Agregar_Trabajadores_BIN(vector<Trabajadores> Nuevos)
{
    ofstream archivo("Lista_de_Trabajadores.bin", ios::binary | ios::app);
    if (archivo.fail())
    {
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }
    else
    {
        for (Trabajadores Datos_Trabajador : Nuevos)
        {
        archivo.write((char*)&Datos_Trabajador, sizeof(Trabajadores));
        }
    }
    archivo.close();
    cout << "Se agregaron nuevos trabajadores."<<endl;
    system("pause");
}

//OPCION 3 BUSCAR TRABJADORES
void Opciones_Busqueda(vector <Trabajadores> Lista_Trabajadores)
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
        Buscar_Nombre(Lista_Trabajadores);
        break;
    case 2:
        Buscar_Apellido(Lista_Trabajadores);
        break;
    case 3:
        Buscar_CI(Lista_Trabajadores);
        break;
    default:
        break;
    }
}

//OPCION BUSCAR NOMBRE
void Buscar_Nombre(vector <Trabajadores> Lista_Trabajadores)
{
    if (Lista_Trabajadores.empty())
    {
        system("cls");
        cout<<"Lista de trabajadores vacia. "<<endl;
        system("pause");
    }
    else
    {
        string nombre;
        string nombre_trabajador;
        system("cls");
        cout<<"Ingrese el nombre a buscar. ";
        getline(cin,nombre);
        for (int i = 0; i < Lista_Trabajadores.size(); i++)
        {
            nombre_trabajador=Lista_Trabajadores[i].Nombres;
            if (Comparador_de_Strings(nombre,nombre_trabajador))
            {
                Imprimir_Trabajadores(Lista_Trabajadores[i]);
            }
        }
        system("pause");
    }
}

// OPCION BUSCAR APELLIDO
void Buscar_Apellido(vector <Trabajadores> Lista_Trabajadores)
{
    if (Lista_Trabajadores.empty())
    {
        system("cls");
        cout<<"Lista de trabajadores vacia. "<<endl;
        system("pause");
    }
    else
    {
        string apellido;
        string apellido_trabajador;
        system("cls");
        cout<<"Ingrese el apellido a buscar. ";
        getline(cin,apellido);
        for (int i = 0; i < Lista_Trabajadores.size(); i++)
        {
            apellido_trabajador=Lista_Trabajadores[i].Apellidos;
            if (Comparador_de_Strings(apellido,apellido_trabajador))
            {
                Imprimir_Trabajadores(Lista_Trabajadores[i]);
            }
        }
        system("pause");
    }
}

//OPCION BUSCAR CI
void Buscar_CI(vector <Trabajadores> Lista_Trabajadores)
{
    string Nro_CI;
    if (Lista_Trabajadores.empty())
    {
        system("cls");
        cout<<"Lista de trabajadores vacia. "<<endl;
        system("pause");
    }
    else
    {
        system("cls");
        cout<<"Ingrese el Nro_CI del trabajador. ";
        getline(cin,Nro_CI);
        for (int i = 0; i < Lista_Trabajadores.size(); i++)
        {
            if (Comparador_de_Strings(Nro_CI,to_string(Lista_Trabajadores[i].Nro_CI)))
            {
                Imprimir_Trabajadores(Lista_Trabajadores[i]);
            }
        }
        system("pause");
    }
}

//OPCION EDITAR DATOS TRABAJADOR
void Editar_Datos(vector<Trabajadores> Lista_Trabajadores)
{
    if (Lista_Trabajadores.empty())
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
        cout << "Ingrese el CI del trabajador a editar: ";
        getline(cin, Nro_CI);
        for (int i = 0; i < Lista_Trabajadores.size(); i++)
        {
            if (Nro_CI == to_string(Lista_Trabajadores[i].Nro_CI))
            {
                cout << "Trabajador encontrado: "<<endl;
                Imprimir_Trabajadores(Lista_Trabajadores[i]);
                Lista_Trabajadores[i] = Sub_Menu_Editar_Trabajador(Lista_Trabajadores[i]);
                cout << "Datos actualizados correctamente.";
                system("pause");
                contador++;
                break;
            }
        }
        Crear_Lista_Trabajadores_bin(Lista_Trabajadores);
        if (contador == 0)
        {
            cout << "No existe un trabajador con ese CI." << endl;
            system("pause");
        }
        }
}

Trabajadores Sub_Menu_Editar_Trabajador(Trabajadores Datos_Trabajador)
{
    int opcion = 0;
    string Almacenador_Datos;
    bool verificador=true;
    string texto;
    int numero;
    do {
        cout << "EDITAR DATOS DEL TRABAJADOR";
        cout << "1. Editar Nombre"<<endl;
        cout << "2. Editar Apellido"<<endl;
        cout << "3. Editar CI"<<endl;
        cout << "4. Editar Cargo"<<endl;
        cout << "5. Editar Sueldo"<<endl;
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
        strcpy(Datos_Trabajador.Nombres, texto.c_str());
        break;

    case 2:
        system("cls");
        cout << "Ingrese el nuevo apellido: ";
        getline(cin, texto);
        strcpy(Datos_Trabajador.Apellidos, texto.c_str());
        break;
    case 3:
        system("cls");
        cout << "Ingrese el nuevo CI: ";
        getline(cin, texto);
        numero = stoi(texto);
        Datos_Trabajador.Nro_CI = numero;
        break;
    case 4:
        system("cls");
        cout << "Ingrese el nuevo cargo: ";
        getline(cin, texto);
        strcpy(Datos_Trabajador.Cargo, texto.c_str());
        break;
    case 5:
        system("cls");
        cout << "Ingrese el nuevo sueldo: ";
        getline(cin, texto);
        numero = stoi(texto);
        Datos_Trabajador.Sueldo = numero;
        break;
    default:
        cout << "Opcion invalida.\n";
        break;
    }
    return Datos_Trabajador;
}

//OPCION BORRAR TRABAJADOR LISTA
void Borrar_Trabajador(vector<Trabajadores> Lista_Trabajadores)
{
    if (Lista_Trabajadores.empty())
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
        vector<Trabajadores> Lista_Nueva;
        cout << "Ingrese el CI del trabajador a borrar: ";
        getline(cin, Nro_CI);
        bool encontrado = false;
        for (int i = 0; i < Lista_Trabajadores.size(); i++)
        {
            if (to_string(Lista_Trabajadores[i].Nro_CI) == Nro_CI)
            {
                cout << "Trabajador Borrado:"<<endl;
                Imprimir_Trabajadores(Lista_Trabajadores[i]);
                encontrado = true;
            }
            else
            {
                Lista_Nueva.push_back(Lista_Trabajadores[i]);
            }
        }
        if (!encontrado)
        {
            cout << "No existe un trabajador con ese CI.";
            system("pause");
            return;
        }
        Crear_Lista_Trabajadores_bin(Lista_Nueva);
        cout << "El trabajador fue eliminado correctamente."<<endl;
        system("pause");
    }
}
