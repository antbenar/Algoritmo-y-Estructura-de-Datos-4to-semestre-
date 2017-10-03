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
	
	Lista(){
		head=NULL;
	}
	
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
	
	void insertar(T data_){
		nodo<T> *temp = head;
		nodo<T> *new_nodo = new nodo<T> (data_);
		if (!head) {
			head = new_nodo;
		} 
		else {
			if (head->dato > data_) {
				new_nodo->next = head;
				head = new_nodo;
			} 
			else {
				while ((temp->next != NULL) && (temp->next->dato < data_)) {
					temp = temp->next;
				}
				if(temp->dato!=data_){
					new_nodo->next = temp->next;
					temp->next = new_nodo;
				}
			}
		}
	}	
	
	void borrar(T dato_){
		nodo<T> *temp = head;
		
		if(!head){return;}
		else if (head->dato == dato_) {
			head = head->next;
			delete temp;
		} 
		else {
			while (temp->next) {
				if (temp->next->dato == dato_) {
					nodo<T> *aux_node = temp->next;
					if(temp->next->next){
						temp->next = temp->next->next;
						delete aux_node;
						return;
					}
					else{
						temp->next = NULL;
						delete aux_node;
						return;
					}
				}
				temp = temp->next;
			}
		}
	}

	void imprimir(){
		if(!head){
			cout<<"lista vacia"<<endl;
			return;
		}
		nodo<int> *temp=head;
		
		while(temp->next!=NULL){
			cout<<temp->dato<<", ";
			temp=temp->next;
		}cout<<temp->dato<<endl;
	}
};

int main(int argc, char *argv[]) {
	Lista <int>a;
	a.insertar(5);
	a.insertar(5);
	a.insertar(5);
	a.insertar(8);

	a.imprimir();
}

