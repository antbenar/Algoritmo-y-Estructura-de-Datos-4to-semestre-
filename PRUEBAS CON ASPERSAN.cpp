#include <stdlib.h>
#include <iostream>
using namespace std;

int sumar(int a){
	a+=1;
}
int sumar_(int &a){
	a+=1;
}

int sumarp(int* a){//NO SE MODIFICA AL PUNTERO 
	a+=1;
}
int sumarp_(int* &a){//SE MODIFICA AL PUNTERO SOLO SI ESQUE TIENE "&"
	a+=1;
}

int main(){
	int a = 3;//PROBAR "&" CON ENTEROS NORMALES
	cout<< a<<endl;
	sumar(a);cout<< a<<endl;
	sumar_(a);cout<< a<<endl<<endl;
	
	int *p=&a;//PROBAR "&" CON PUNTEROS
	cout<<*p<<endl;
	sumarp(p);cout<<*p<<endl;
	sumarp_(p);cout<<*p<<endl;
	return 0;
}
