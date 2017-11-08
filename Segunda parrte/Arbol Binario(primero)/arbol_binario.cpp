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
		
		while( *temp ){
			if( dato_ < (*temp)->dato){
				temp=&(*temp)->left;
			}
			else {
				temp=&(*temp)->right;
			}
		}
		if((*temp)==NULL || (*temp)->dato!=dato_){
			return false;
		}
		return true;
	}
	
	void insertar(T dato_){
		
		if(!head){
			nodo<T>* new_nodo=new nodo<T>(dato_);
			head = new_nodo;
		}
		else {
			nodo <T> **next_insert;
			if (!buscar(dato_,next_insert)){
				nodo<T>* new_nodo=new nodo<T>(dato_);
				*next_insert = new_nodo;
			}
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
	Arbol_binario<int> lista(6);
	lista.insertar(5);
	lista.insertar(7);
	lista.insertar(8);
	//lista.borrar(9);
	//lista.borrar(5);
	
	lista.imprimir_en_Orden(lista.head);
	
	return 0;
}
