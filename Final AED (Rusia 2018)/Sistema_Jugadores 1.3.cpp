#include <iostream>
#include <stack>
#include <vector>
#include <stdlib.h>

using namespace std;

class nodo{
public:
	int key;
	nodo* next;
	
	///datos jugador
	int camiseta;
	string apellido;
	char posicion;
	int edad;
	string seleccion;
	
public:
	nodo(int key_, int camiseta_, string apellido_, char posicion_, int edad_, string seleccion_)
	{
		key=key_;
		next=NULL;
		
		///datos jugador
		camiseta=camiseta_;
		apellido=apellido_;
		posicion=posicion_;
		edad=edad_;
		seleccion=seleccion_;
	}
	
};

///Hay dos tipos de Lista: Una con nodos que contienen los datos y otra con nodos que solo tienen punteros
class Lista_General{///PRIMERA LISTA: GENERAL
public:
	nodo *head;
	nodo *ultimo;
	
	Lista_General(int key_, int camiseta_, string apellido_, char posicion_, int edad_, string seleccion_)
	{
		head = new nodo  (key_,camiseta_, apellido_, posicion_, edad_, seleccion_);
		ultimo = head;
	}
	
	Lista_General()
	{
		head = NULL;
		ultimo =head;
	}
	
	~Lista_General(){
		nodo  *temp=head;
		while(temp!=NULL){
			head=head->next;
			delete temp;
			temp=head;
		}
	}
	
	bool buscar(int key_, nodo **& nodo_devuelto){
		nodo  **temp=&head;                      
		
		while(*(temp)!=NULL && (*temp)->key<key_){
			temp=&((*temp)->next);                      
		}
		nodo_devuelto=temp;       
		if((*temp)==NULL || (*temp)->key!=key_){
			return false;
		}
		return true;
	}
	
	void insertar(int key_, int camiseta_, string apellido_, char posicion_, int edad_, string seleccion_,nodo*& jugador_actual){
		if(!head)
		{
			nodo * aux=new nodo (key_, camiseta_, apellido_, posicion_, edad_, seleccion_);
			head=aux;
			ultimo=aux;
			jugador_actual = aux;
			return;
		}
		nodo * aux=new nodo (key_, camiseta_, apellido_, posicion_, edad_, seleccion_);
		ultimo->next=aux;
		ultimo=aux;
		jugador_actual = ultimo;
	}
	
	/*void borrar(int key_){
		nodo ** nodo_borrar;
		if (buscar(key_,nodo_borrar)){
			nodo * aux= (*nodo_borrar)->next;
			delete (*nodo_borrar);
			*nodo_borrar=aux;
		}
	}*/
	
	void imprimir(){
		nodo *p=head;
		while(p!=NULL){
			cout<<p->key<<", ";
			cout<<"camiseta: "<<p->camiseta<<endl;
			cout<<"apellido: "<<p->apellido<<endl;
			cout<<"posicion: "<<p->posicion<<endl;
			cout<<"edad: "<<p->edad<<endl;
			cout<<"seleccion: "<<p->seleccion<<endl;
			cout<<endl<<endl;
			p=p->next;
		}
	}
};

class nodo_punt_jugador{
public:
	nodo_punt_jugador* next;
	nodo* jugador;
	
public:
	nodo_punt_jugador(nodo* jugador_)
	{
		jugador=jugador_;
		next=NULL;
	}
};

class Lista_Jugadores{///SEGUNDA LISTA: LISTA DE PUNTEROS A LOS JUGADORES
public:
	nodo_punt_jugador *head;
	nodo_punt_jugador *ultimo;
	
	Lista_Jugadores(nodo* jugador_)
	{
		head = new nodo_punt_jugador  (jugador_);
		ultimo = head;
	}
	
	Lista_Jugadores()
	{
		head = NULL;
		ultimo = NULL;
	}
	
	void insertar(nodo *jugador_){
		if(!head)
		{
			head=new nodo_punt_jugador(jugador_);
			ultimo=head;
			return;
		}
		ultimo->next=new nodo_punt_jugador(jugador_);
		ultimo=ultimo->next;
	}
};

template <class T>
class C_Node
{
	
public:
	T value;
	C_Node <T> *raices[2];
	int h_right;
	int h_left;
	Lista_Jugadores* jugador;
	
public:
	C_Node(T value)
	{
		jugador=new Lista_Jugadores;
		this->value = value;
		raices[0] = NULL;
		raices[1] = NULL;
		h_right = 0;
		h_left = 0;
	}
};


template <class T>
class AVL_Tree
{
	
public:
	C_Node <T> *raiz = NULL;
	
public:
	void actualizar(C_Node <T> *&node)
	{
		if(node->raices[0]!=NULL)
		{
			if(node->raices[0]->h_left < node->raices[0]->h_right)
			{
				node->h_left = node->raices[0]->h_right + 1;
			}
			else
			{
				node->h_left = node->raices[0]->h_left + 1;
			}
		}
		else
		{
			node->h_left = 0;
		}
		if(node->raices[1]!=NULL)
		{
			if(node->raices[1]->h_left < node->raices[1]->h_right)
			{
				node->h_right = node->raices[1]->h_right + 1;
			}
			else
			{
				node->h_right = node->raices[1]->h_left + 1;
			}
		}
		else
		{
			node->h_right = 0;
		}
	}
	bool Buscar(T target, C_Node <T> **& ptr, vector <C_Node <T> **> &path)
	{
		ptr = &raiz;
		while(*ptr != NULL && target != (*ptr)->value)
		{
			path.push_back(ptr);
			if(target > (*ptr)->value)
			{
				ptr = &(*ptr)->raices[1];
			}
			else
			   ptr = &(*ptr)->raices[0];
		}
		return *ptr && (*ptr)->value == target;
	}
	bool Rotacion_DR(C_Node <T> *&raiz)
	{
		C_Node <T> *newraiz = raiz->raices[1];
		raiz->raices[1] = newraiz->raices[0];
		newraiz->raices[0] = raiz;
		raiz = newraiz;
		return 1;
	}
	bool Rotacion_DL(C_Node <T> *&raiz)
	{
		C_Node <T> *newraiz = raiz->raices[0];
		raiz->raices[0] = newraiz->raices[1];
		newraiz->raices[1] = raiz;
		raiz = newraiz;
		return 1;
	}
	bool Rotacion_RL(C_Node <T> *&raiz)
	{
		C_Node <T> *newraiz = raiz->raices[1]->raices[0];
		raiz->raices[1]->raices[0] = newraiz->raices[1];
		newraiz->raices[1] = raiz->raices[1];
		raiz->raices[1] = newraiz->raices[0];
		newraiz->raices[0] = raiz;
		raiz = newraiz;
		return 1;
	}
	bool Rotacion_LR(C_Node <T> *&raiz)
	{
		C_Node <T> *newraiz = raiz->raices[0]->raices[1];
		raiz->raices[0]->raices[1] = newraiz->raices[0];
		newraiz->raices[0] = raiz->raices[0];
		raiz->raices[0] = newraiz->raices[1];
		newraiz->raices[1] = raiz;
		raiz = newraiz;
		return 1;
	}
	bool balancear(C_Node <T> **&raiz)
	{
		if((*raiz)->h_right - (*raiz)->h_left == -2)
		{
			if((*raiz)->raices[0]->h_left >= (*raiz)->raices[0]->h_right)
			{
				Rotacion_DL((*raiz));
				return 1;
			}
			else
				Rotacion_LR((*raiz));
			return 1;
		}
		else if((*raiz)->h_right - (*raiz)->h_left == 2)
		{
			if((*raiz)->raices[1]->h_right >= (*raiz)->raices[1]->h_left)
			{
				Rotacion_DR((*raiz));
				return 1;
			}
			else
				Rotacion_RL((*raiz));
			return 1;
		}
		return 0;
	}
	bool Insertar(T target,nodo* jugador_)
	{
		C_Node <T> **ptr;
		vector <C_Node <T> **> path;
		if(Buscar(target, ptr, path)) return 0;
		
		C_Node <T> *newNode = new C_Node <T> (target);
		*ptr = newNode;
		for(int i = path.size() - 1; i >= 0; i--)
		{
			actualizar(*path[i]);
			if(balancear(path[i]))
			{
				actualizar((*path[i])->raices[0]);
				actualizar((*path[i])->raices[1]);
				actualizar(*path[i]);
			}
		}
		newNode->jugador->insertar(jugador_);
		return 1;
	}
	/*bool Borrar(T target)///MODIFICAR EL BORRADO, AUN NO ESTA
	{
		C_Node <T> **ptr;
		vector <C_Node <T> **> path;
		if(!Buscar(target, ptr, path)) return 0;
		if((*ptr)->raices[0] && (*ptr)->raices[1])
		{
			C_Node<T> **q = ptr;
			q = &((*q)->raices[1]);
			while((*q)->raices[0])
			{
				q = &((*q)->raices[0]);
			}
			(*ptr)->value = (*q)->value;
			ptr = q;
		}
		C_Node<T> *t = *ptr;
		*ptr = (*ptr)->raices[(*ptr)->raices[1] != 0];
		delete t;
		for(int i = path.size() - 1; i >= 0; i--)
		{
			actualizar(*path[i]);
			if(balancear(path[i]))
			{
				actualizar((*path[i])->raices[0]);
				actualizar((*path[i])->raices[1]);
				actualizar(*path[i]);
			}
		}
		return 1;
	}*/
	/*void Imprimir(C_Node <T> *p)
	{
		if(p->raices[0])Imprimir(p->raices[0]);
		
		cout<<"camiseta: "<<p->jugador->camiseta<<endl;
		cout<<"apellido: "<<p->jugador->apellido<<endl;
		cout<<"posicion: "<<p->jugador->posicion<<endl;
		cout<<"edad: "<<p->jugador->edad<<endl;
		cout<<"seleccion: "<<p->jugador->seleccion<<endl;
		cout<<endl;
		
		if(p->raices[1])Imprimir(p->raices[1]);
	}*/
};


class Sistema{
public:
	AVL_Tree<string>* seleccion;
	AVL_Tree<char>* posicion;
	AVL_Tree<int>* edades;
	Lista_General *general;
	
	Sistema(){
		seleccion = new AVL_Tree<string>;
		posicion= new AVL_Tree<char>;
		edades = new AVL_Tree<int>;
		general= new Lista_General();
	}
	
	void insertar(int key_, int camiseta_, string apellido_, char posicion_, int edad_, string seleccion_){
		nodo *posicion_jugador;
		general->insertar(key_,camiseta_, apellido_, posicion_, edad_, seleccion_,posicion_jugador);
		seleccion->Insertar(seleccion_,posicion_jugador);
		//posicion->Insertar(posicion_);
		//edades->Insertar(edad_);
	}
	void imprimir()
	{
		general->imprimir();
	}
};



int main()
{
	Sistema sistema;
	//Lista a(1,3,"Ocola",'P',18,"Peru");
	sistema.insertar(2,4,"Yato",'A',18,"Peru");
	//sistema.insertar(1,3,"Ocola",'P',18,"Peru");
	
	sistema.imprimir();

	
	return 0;
}
