#include <iostream>
using namespace std;

template<typename T>
class nodo{
public:
	T dato;
	nodo* left;
	nodo* right;
	
	nodo(T dato_){
		dato=dato_;
		left=NULL;
		right=NULL;
	}
};

template<typename T>
class Lista{
public:
	nodo<T> *head;
	
	Lista(T dato_)
	{
		head = new nodo<T> (dato_);
	}
	
	~Lista(){
		nodo<T> *temp=head;
		while(temp!=NULL){
			head=head->next;
			delete temp;
			temp=head;
		}
	}
	
	bool buscar(T dato_, nodo<T>**& nodo_devuelto){
		nodo<T> **temp=&head;                      
		
		while(*(temp)->left != NULL && *(temp)->right != NULL && *(temp)->dato != dato){
			if(dato_ < *(temp)->dato)temp=&(*temp)->right;
			else temp=&(*temp)->left;
		}
		
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
	
	void imprimir(){
		nodo<int> *temp=head;
		while(temp->next!=NULL){
			cout<<temp->dato<<", ";
			temp=temp->next;
		}cout<<temp->dato<<endl;
	}
};

int main(int argc, char *argv[]) {
	Lista<int> lista(6);
	lista.insertar(5);
	lista.insertar(3);
	lista.insertar(7);
	//lista.borrar(9);
	//lista.borrar(5);
	
	lista.imprimir();
	
	return 0;
}
