#include <iostream>
using namespace std;

template<typename T>
struct nodo{
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
class Arbol_binario{
public:
	nodo<T> *head;
	
	Arbol_binario()
	{
		head = NULL;
	}
	
	Arbol_binario(T dato_)
	{
		head = new nodo<T> (dato_);
	}
	
	bool buscar(T dato_, nodo<T>** &nodo_devuelto){
		nodo<T> **temp=&head;                      
		
		while( *temp && (*temp)->dato!=dato_){
			if( dato_ < (*temp)->dato){
				temp=&(*temp)->left;
			}
			else{
				temp=&(*temp)->right;
			}
		}
		nodo_devuelto=temp;
		if((*temp)==NULL || (*temp)->dato!=dato_){
			return false;
		}
		return true;
	}
	
	bool insertar(T dato_){
		nodo <T> **next_insert;
		if (!buscar(dato_,next_insert)){
			*next_insert = new nodo<T>(dato_);//cout<<(*next_insert)->dato<<",";
			return 1;
		}
		return 0;
	}	
	
	void buscar_suplente(nodo<T>** &nodo_devuelto){
		nodo_devuelto = &(*nodo_devuelto)->left;
		while((*nodo_devuelto)->right){
			nodo_devuelto = &(*nodo_devuelto)->right;
		}
	}
	
	bool borrar(T dato_){
		nodo<T>** nodo_borrar;
		if (buscar(dato_,nodo_borrar)){
			if((*nodo_borrar)->left && (*nodo_borrar)->right){
				nodo<T>** nodo_suplente = nodo_borrar;
				buscar_suplente(nodo_suplente);
				(*nodo_borrar)->dato = (*nodo_suplente)->dato;
				nodo_borrar=nodo_suplente;
			}
			nodo<T>** aux=nodo_borrar;
			if((*nodo_borrar)->left){
				nodo_borrar = &(*nodo_borrar)->left;
			}	
			else nodo_borrar = &(*nodo_borrar)->right;
			
			delete aux;
			return 1;
		}
		return 0;
	}
	
	void imprimir_en_Orden(nodo<T> *pointer){
		if(pointer){
			imprimir_en_Orden(pointer->left);
			cout<<pointer->dato<<", ";
			imprimir_en_Orden(pointer->right);
		}
	}
	
	void destructor(nodo<T>* &pointer){
		if(pointer){
			destructor(pointer->left);
			destructor(pointer->right);
			delete pointer;
		}
	}
	
	~Arbol_binario(){
		destructor(head);
	}
};

int main(int argc, char *argv[]) {
	Arbol_binario<int> lista(6);//cout<<lista.head->dato;
	lista.insertar(4);//cout<<lista.head->dato;
	lista.insertar(3);//cout<<lista.head->dato;
	lista.insertar(2);
	lista.borrar(4);
	lista.borrar(3);
	lista.borrar(6);
	lista.borrar(2);

	lista.imprimir_en_Orden(lista.head);
	
	return 0;
}
