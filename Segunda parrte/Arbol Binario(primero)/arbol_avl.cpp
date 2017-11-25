#include <iostream>
#include <stack>
#define mayor(a, b) (a > b ? a : b)
using namespace std;

template<typename T>
struct nodo{
public:
	T dato;
	nodo* hijos[2];
	unsigned int altura;
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
	
	bool buscar(T dato_, nodo<T>** &nodo_devuelto, stack< nodo<T>** > &recorrido){
		nodo<T> **temp=&head;                      
		
		while( *temp && (*temp)->dato!=dato_){
			recorrido.push(temp);//
			temp= &(*temp)->hijos[dato_ > (*temp)->dato];
		}
		nodo_devuelto=temp;
		if((*temp)==NULL || (*temp)->dato!=dato_){
			return false;
		}
		return true;
	}
	
	int altura_(nodo<T> *N)
	{
		if (N == NULL)
			return 0;
		return N->altura;
	}
	
	int altura(nodo<T> *n,int l,int r){
		if(!n)
			return 0;
		if(n->hijos[0]){
			l=altura(n->hijos[0],l,r)+1;
		}
		if(n->hijos[1]){
			r=altura(n->hijos[1],0,r)+1;
		}
		if(l>r)
			return l;
		else
			return r;
	}
	
	
	bool balancear(nodo<T> **n){
		int l=1,r=1;
		nodo<T>* temp;
		if((altura((*n)->hijos[0],l,r)-altura((*n)->hijos[1],l,r)>=2)){
			if(altura((*n)->hijos[0]->hijos[0],l,r)>altura((*n)->hijos[0]->hijos[1],l,r)){
				temp=(*n)->hijos[0];
				(*n)->hijos[0]=(*n)->hijos[0]->hijos[1];
				temp->hijos[1]=*n;
				*n=temp;
			}
			else{
				temp=(*n)->hijos[0]->hijos[1];
				(*n)->hijos[0]->hijos[1]=temp->hijos[0];
				temp->hijos[0]=(*n)->hijos[0];
				(*n)->hijos[0]=temp->hijos[1];
				temp->hijos[1]=*n;
				*n=temp;
			}
			return 1;
		}
		if((altura((*n)->hijos[0],l,r)-altura((*n)->hijos[1],l,r)<=-2)){
			if(altura((*n)->hijos[1]->hijos[0],l,r)>altura((*n)->hijos[1]->hijos[1],l,r)){
				temp=(*n)->hijos[1]->hijos[0];
				(*n)->hijos[1]->hijos[0]=temp->hijos[1];
				temp->hijos[1]=(*n)->hijos[1];
				(*n)->hijos[1]=temp->hijos[0];
				temp->hijos[0]=*n;
				*n=temp;
			}
			else{
				temp=(*n)->hijos[1];
				(*n)->hijos[1]=(*n)->hijos[1]->hijos[0];
				temp->hijos[0]=*n;
				*n=temp;
			}
			return 1;
		}

		return 0;
	}
	
	bool insertar(T dato_){
		nodo <T> **next_insert;
		stack< nodo<T>** >recorrido;
		if (!buscar(dato_,next_insert,recorrido)){
			*next_insert = new nodo<T>(dato_);//cout<<(*next_insert)->dato<<",";
			while(!recorrido.empty()&&!balancear(recorrido.top())){
				recorrido.pop();
			}
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
	
	bool borrar_(T dato_){
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
	
	void borrar(int val){
		nodo<T>** p= &head;
		stack<nodo<T>**> recorrido;
		if(buscar(val,p,recorrido)){
			if((*p)->hijos[0]&&(*p)->hijos[1]){
				nodo<T>* aux = *p;
				p=&((*p)->hijos[0]);
				recorrido.push(p);
				while((*p)->hijos[1])
					p=&((*p)->hijos[1]);
				recorrido.push(p);
				aux->dato=(*p)->dato;
			}
			nodo<T>* temp=*p;
			*p=(*p)->hijos[(*p)->hijos[1]!=NULL];
			delete(temp);
			recorrido.pop();
			while(!recorrido.empty()&&!balancear(recorrido.top())){
				recorrido.pop();
			}
		}
	}
	void imprimir_Arbol(nodo<T> *pointer){
		if(pointer){
			cout<< "\t" << pointer->dato<<"\t: hijo izquierdo: ";
			if(pointer->hijos[0]){
				cout << pointer->hijos[0]->dato;
			}else cout<<"NULL";
			
			cout<<  ",\thijo derecho: ";
			if(pointer->hijos[1]){
				cout << pointer->hijos[1]->dato;
			}else cout<<"NULL";
			
			cout<<endl;
			
			imprimir_Arbol(pointer->hijos [0]);
			imprimir_Arbol(pointer->hijos[1]);
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
	Arbol_binario<int> lista(10);
	lista.insertar(8);
	lista.insertar(15);
	lista.insertar(7);
	lista.insertar(9);
	lista.insertar(11);
	lista.insertar(16);
	lista.insertar(17);
	lista.insertar(18);
	lista.insertar(19);
	lista.insertar(20);
	lista.insertar(21);
	lista.borrar(17);
	lista.borrar(16);
	lista.borrar(11);
		
	lista.imprimir_Arbol(lista.head);cout<<endl;
	return 0;
}
