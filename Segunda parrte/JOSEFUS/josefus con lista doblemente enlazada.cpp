#include <iostream>
using namespace std;

template<typename T>
class nodo{
public:
	T dato;
	nodo* next;
	nodo* prev;
	
	nodo(T dato_){
		dato=dato_;
		next=NULL;
		prev=NULL;
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
		head->next=head;
		head->prev=head;
		num_nodos = 1;
	}
	
	bool buscar(T dato_, nodo<T>*& nodo_devuelto){
		if(dato_ == head->dato){
			nodo_devuelto=head;
			return true;
		}
		if(dato_ < head->dato){
			nodo_devuelto=head;
			return false;
		}
		
		nodo<T> *temp = head->next;                      
		while(temp!=head && temp->dato<dato_){
			temp = temp->next;                      
		}
		nodo_devuelto=temp;       
		if(temp==head || temp->dato != dato_){
			return false;
		}
		return true;
	}
	
	void insertar(T dato_){
		nodo<T>* prev_insert;
		if (!buscar(dato_,prev_insert)){
			num_nodos++;
			nodo<T>* aux=new nodo<T>(dato_);
			if(prev_insert==head && head->dato > dato_){
				aux->prev=head->prev;
				aux->next=head;
				head->prev->next=aux;
				head->prev=aux;
				head=aux;
				return;
			}
			aux->next = prev_insert;
			aux->prev = prev_insert->prev;
			prev_insert->prev->next = aux;
			prev_insert->prev = aux;
		}
	}	
	
	void borrar(T dato_){
		nodo<T>* nodo_borrar;

		if (buscar(dato_,nodo_borrar)){
			num_nodos--;
			if(nodo_borrar==head){
				head->prev->next=head->next;
				head->next->prev=head->prev;
				head=head->next;
				delete nodo_borrar;
				return;
			}
			nodo_borrar->prev->next = nodo_borrar->next;
			nodo_borrar->next->prev = nodo_borrar->prev;
			delete nodo_borrar;
			return;
		}
	}
	
	void borrar_josefus(nodo<T>*& nodo_borrar){
		num_nodos--;
		if(nodo_borrar==head){
			head->prev->next=head->next;
			head->next->prev=head->prev;
			head=head->next;
			delete nodo_borrar;
			return;
		}
		nodo_borrar->prev->next = nodo_borrar->next;
		nodo_borrar->next->prev = nodo_borrar->prev;
		delete nodo_borrar;
		return;
	}
	
	
	void imprimir_head(){
		if(!head){
			cout<<"lista vacia"<<endl;
			return;
		}
		
		nodo<int> *temp=head->next;
		cout<<head->dato<<", ";
		while(temp->next!=head){
			cout<<temp->dato<<", ";
			temp=temp->next;
		}cout<<temp->dato<<endl;
	}
	
	
	~Lista(){
		if(!head){
			return;
		}
		nodo<T> *temp;
		nodo<T> *aux = head->next;
		while(aux!=head){
			temp = aux;
			aux=aux->next;
			delete temp;
		}
		delete head;
	}
};

template <typename T>
int josefus(Lista <T> &a, int salto){
	int i;
	nodo <T>* aux;
	nodo <T>* temp= a.head;
	while(a.num_nodos != 1){
		i=salto-1; //cout<<"a"<<endl;
		while(i>0){
			temp=temp->next; //cout<<"b"<<endl;
			i--;
		}
		aux=temp;
		temp=temp->next;
		a.imprimir_head();
		a.borrar_josefus(aux);
	}
	return temp->dato;
}

int main(int argc, char *argv[]) {
	Lista <int>a(3);
	
	int tam, saltos;
	cout<<"ingrese el tamaño del array: ";cin>>tam;
	cout<<"ingrese el numero de saltos: ";cin>>saltos;
	
	for(int i=1;i<=tam;i++){
		a.insertar(i);
	}
	/*a.imprimir_head();
	nodo <int>* temp= a.head->next->next;
	a.borrar_josefus(temp);
	a.imprimir_head();*/
	cout<<"el sobreviviente es el numero "<<josefus(a,saltos);
	
}
