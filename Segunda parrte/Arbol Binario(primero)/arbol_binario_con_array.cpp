#include <iostream>
using namespace std;

template<typename T>
struct nodo{
public:
	T dato;
	nodo* hijos[2];
	nodo(int dato_){
		dato=dato_;
		hijos[1]=NULL;
		hijos[0]=NULL;
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
			temp= &(*temp)->hijos[dato_ > (*temp)->dato];
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
		nodo_devuelto = &(*nodo_devuelto)->hijos[0];
		while((*nodo_devuelto)->hijos[1]){
			nodo_devuelto = &(*nodo_devuelto)->hijos[1];
		}
	}
	
	bool borrar(T dato_){
		nodo<T>** nodo_borrar;
		if (buscar(dato_,nodo_borrar)){
			if((*nodo_borrar)->hijos[0] && (*nodo_borrar)->hijos[1]){
				nodo<T>** nodo_suplente = nodo_borrar;
				buscar_suplente(nodo_suplente);
				(*nodo_borrar)->dato = (*nodo_suplente)->dato;
				nodo_borrar=nodo_suplente;
			}
			nodo<T>* aux=*nodo_borrar;
			*nodo_borrar=(*nodo_borrar)->hijos[(*nodo_borrar)->hijos[1]!=NULL];
			
			delete aux;
			return 1;
		}
		return 0;
	}
	
	void imprimir_en_Orden(nodo<T> *pointer){
		if(pointer){
			imprimir_en_Orden(pointer->hijos[0]);
			cout<<pointer->dato<<", ";
			imprimir_en_Orden(pointer->hijos[1]);
		}
	}
	
	void destructor(nodo<T>* &pointer){
		if(pointer){
			destructor(pointer->hijos[0]);
			destructor(pointer->hijos[1]);
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
	lista.insertar(5);//cout<<lista.head->dato;
	lista.insertar(8);
	
	lista.imprimir_en_Orden(lista.head);cout<<endl;
	lista.borrar(4);
	/*lista.borrar(3);
	lista.borrar(6);
	lista.borrar(2);
	*/
	lista.imprimir_en_Orden(lista.head);cout<<endl;
	
	return 0;
}
