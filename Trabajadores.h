#include <iostream>

using namespace std;

struct Datos_Trabajadores
{
char Nombre [50];
char Cargo  [40];
char Turno  [10];
int  Nro_CI;
int  Sueldo;
};

void Resgistrar_Trabajadores()
{
    Datos_Trabajadores Empleados;
    cout<<"Ingrese el nombre completo del empleado: ";
    cin.getline(Empleados.Nombre, 50); 
     
}