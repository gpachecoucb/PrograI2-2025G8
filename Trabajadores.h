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

vector <Trabajadores> Resgistro_Trabajadores();
bool Validar_Datos_Caracteres(string Datos_Registrados);
bool Validar_Datos_Numericos(string Datos_Registrados );
void Menu_Trabajadores ();
void Crear_Lista_Trabajadores_txt(vector <Trabajadores> Lista_Trabajadores);
void Imprimir_Vectores_Trabajadores(vector <Trabajadores> Lista_Trabajadores);
void Cargar_Lista_Trabajadores_txt(vector <Trabajadores>& Lista_Trabajadores);

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
      cout << "Ingrese un numero para comenzar el registro." << endl;
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

//Funcion Que Crea El Archivo De Texto
void Crear_Lista_Trabajadores_txt(vector <Trabajadores> Lista_Trabajadores)
{
   ofstream archivo;
   archivo.open("Lista_de_Trabajadores.txt", ios::out);
   if (archivo.fail())
   {
      cout<<"No se logro crear el archivo con exito"<<endl; 
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
    cout << "Archivo 'Lista_de_Trabajadores.txt' creado exitosamente." << endl;
    archivo.close();
    system("pause");
   }
}

//Funcion Que Carga Los Datos desde un Archivo de Texto
void Cargar_Lista_Trabajadores_txt(vector <Trabajadores> &Lista_Trabajadores)
{
    ifstream archivo("Lista_de_Trabajadores.txt", ios::in);
    if (archivo.fail())
    {
        cout << "No se logro abrir el archivo con exito" << endl;
        return;
    }
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
    archivo.close();
    cout << "\nSe logro cargar los datos del archivo de texto." << endl;
    system("pause");
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
      cout<<"2. Listar Trabajadores en un archivo .txt"<<endl;
      cout<<"3. Cargar lista de trabajadores desde un archivo .txt"<<endl;
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
         Lista_Trabajadores = Resgistro_Trabajadores();
         Imprimir_Vectores_Trabajadores(Lista_Trabajadores);
         system("pause");
         break;
      case 2:
         Crear_Lista_Trabajadores_txt( Lista_Trabajadores);
         break;
      case 3:
         Cargar_Lista_Trabajadores_txt(Lista_Trabajadores);
         break;
      }
   } while (opcion_numerica != 0);
   
}

//FUNCIONES AUXILIARES
void Imprimir_Vectores_Trabajadores(vector <Trabajadores> Lista_Trabajadores)
{
  system("cls");
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