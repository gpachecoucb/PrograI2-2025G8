#include "Libreria_Trabajadores.h"
#include "Libreria_Clientes.h"
void Menu_Ferreteria();

int main(){
    Menu_Ferreteria();
    return 0;
}

void Menu_Ferreteria()
{
    int opcion=0;
    do
    {
        system("cls");
        cout<<"FERRETERIA LEONEL"<<endl;
        cout<<"1. Trabajadores"<<endl;
        cout<<"2. Clientes"<<endl;
        cout<<"Seleccione una opcion: ";
        cin>> opcion;
        cin.ignore();
        switch (opcion)
        {
        case 1:
        Menu_Trabajadores();
            break;
        case 2:
        Menu_Clientes();
            break;
        default:
            break;
        }  
    } while (opcion!=0);
}

