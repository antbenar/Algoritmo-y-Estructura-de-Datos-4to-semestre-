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
	nodo<T> *tail;
	
	Lista(){
		head=NULL;
		tail=NULL;
	}
	
	Lista(T dato_)
	{
		head = new nodo<T> (dato_);
		tail=head;
	}
	
	void insertar(T data_){
		nodo<T> *temp = head;
		nodo<T> *new_nodo = new nodo<T> (data_);
		
		if (!head) {
			head = new_nodo;
			tail=head;
		} 
		else {
			if (head->dato > data_) {
				new_nodo->next = head;
				head->prev=new_nodo;
				head = new_nodo;
			} 
			else if(tail->dato > data_){
				while ((temp->next != NULL) && (temp->next->dato < data_)) {
					temp = temp->next;
				}
				if(temp->dato!=data_){
					new_nodo->next = temp->next;
					new_nodo->prev = temp;
					temp->next->prev = new_nodo;
					temp->next = new_nodo;
				}
			}
			else{
				tail->next=new_nodo;
				new_nodo->prev=tail;
				tail=new_nodo;
			}
		}
	}	
	
	void borrar(T dato_){
		nodo<T> *temp = head;
		
		if(!head){return;}
		else if (head->dato == dato_) {
			if(head!=tail){
				head = head->next;
				head->prev=NULL;		
				delete temp;
			}
			else{
				head=NULL;
				tail=head;
			}
		} 
		else if(tail->dato != dato_){
			while (temp->next) {
				if (temp->next->dato == dato_) {
					nodo<T> *aux_node = temp->next;
					nodo<T> *nodo_seguido = temp->next->next;
					temp->next = nodo_seguido;
					nodo_seguido->prev=temp;
					delete aux_node;
					imprimir_tail();
					return;
				}
				temp = temp->next;
			}
		}
		else{
			if(tail!=head){
				temp=tail;
				tail=tail->prev;
				tail->next=NULL;
				delete temp;
			}
		}
		imprimir_tail();
	}
	
	void imprimir_head(){
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
	
	void imprimir_tail(){
		if(!tail){
			cout<<"lista vacia"<<endl;
			return;
		}
		nodo<int> *temp=tail;
		
		while(temp->prev!=NULL){
			cout<<temp->dato<<", ";
			temp=temp->prev;
		}cout<<temp->dato<<endl;
	}
	
	
	~Lista(){
		nodo<T> *temp=head;
		while(temp!=NULL){
			head=head->next;
			delete temp;
			temp=head;
		}
	}
};

int main(int argc, char *argv[]) {
	Lista <int>a;
	a.insertar(5);
	a.insertar(6);
	a.insertar(7);
	a.insertar(8);
	a.borrar(9);
	a.borrar(6);
	a.borrar(8);
	a.borrar(5);
	a.borrar(7);
	a.imprimir_tail();
}
