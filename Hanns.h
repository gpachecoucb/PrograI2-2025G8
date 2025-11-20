#include <iostream>

using namespace std ;

int sumar(int x,int y){
    return x+y;
}

int factorial(int x){
    int factorial=1;
    for (int i = 1; i <= x; i++)
    {
        factorial*=i;
    }
    return factorial;
}

int restar(int x,int y){
    return x-y;
}

void EsPar(int x){
    if(x%2==0){
        cout<<"Es Par";
    }
    else{
        cout<<"Es Impar";
    }
}