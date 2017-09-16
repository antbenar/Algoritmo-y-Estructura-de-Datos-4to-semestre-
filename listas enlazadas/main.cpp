#include <iostream>
using namespace std;

template<typename T>
class nodo{
public:
	T dato;
	nodo* next;
	
	nodo(T dato_){
		dato=dato_;
		next=NULL;
	}
};

template<typename T>
class Lista{
public:
	nodo<T> *head;
	int num_nodos;
	
	Lista(T dato_)
	{
		head = new nodo<T> (dato_);
		num_nodos++;
	}
	
	bool buscar(T dato_, nodo<T>**& nodo_devuelto){
		nodo<T> **temp=&head;                      
		
		while(*(temp)!=NULL && (*temp)->dato<dato_){
			temp=&((*temp)->next);                      
		}
		nodo_devuelto=temp;       
		if((*temp)==NULL || (*temp)->dato!=dato_){
			return false;
		}
		return true;
	}
	
	void insertar(T dato_){
		nodo<T>** next_insert;
		if (!buscar(dato_,next_insert)){
			nodo<T>* aux=new nodo<T>(dato_);
			aux->next=*next_insert;
			*next_insert=aux;
		}
	}
	
	void borrar(T dato_){
		nodo<T>** nodo_borrar;
		if (buscar(dato_,nodo_borrar)){
			nodo<T>* aux= (*nodo_borrar)->next;
			delete (*nodo_borrar);
			*nodo_borrar=aux;
		}
	}
};

int main(int argc, char *argv[]) {
	Lista<int> lista(6);
	lista.insertar(5);
	lista.insertar(3);
	lista.insertar(7);
	lista.borrar(9);
	lista.borrar(5);
	
	nodo<int> *temp=lista.head;
	while(temp!=NULL){
		cout<<temp->dato<<", ";
		temp=temp->next;
	}cout<<endl;

	while(temp!=NULL){
		temp=lista.head;
		lista.head=lista.head->next;
		delete temp;
	}cout<<endl;
	
	
	return 0;
}
