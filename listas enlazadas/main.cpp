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
        nodo<T> **temp=&head;                         cout<<(*temp)->dato<<"  dato inicial"<<endl;
        while(*temp!=NULL && (*temp)->dato<=dato_){
            *temp=(*temp)->next;                        cout<<(*temp)->dato<<  "  whileeeeee"<<endl;
        }
        nodo_devuelto=temp;             cout<<(*temp)->dato<<  "  (*temp)->dato"<<endl;
        if((*temp)==NULL){
            return 0;
        }
        return 1;
	}

	void insertar(T dato_, nodo<T>**& next_insert){
	    nodo<T>* aux=new nodo<T>(dato_);
		aux->next=*next_insert;
		*next_insert=aux;
	}

    void borrar(nodo<T>**& nodo_borrar){
	    nodo<T>* aux= (*nodo_borrar)->next;
        delete (*nodo_borrar);
        *nodo_borrar=aux;
	}
};

int main(int argc, char *argv[]) {
	Lista<int> lista(6);
	nodo<int> **next_= &(lista.head);
	lista.insertar(5,next_);
	lista.insertar(4,next_);
    //lista.borrar(next_);

    /*int dato=5;
    cout<<lista.buscar(dato,next_)<<endl;
    lista.insertar(dato,next_);*/

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
