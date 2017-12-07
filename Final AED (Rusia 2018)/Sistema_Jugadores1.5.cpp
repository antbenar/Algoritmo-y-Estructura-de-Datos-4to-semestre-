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
    int buscar_2(int camiseta_, string apellido_, char posicion_, int edad_, string seleccion_)
    {
        nodo  **temp=&head;
		while(*(temp)!=NULL && (*temp)->apellido!=apellido_){
			temp=&((*temp)->next);
		}
		if((*temp)->apellido == apellido_)
        {
            return (*temp)->key;
        }

    }
	bool buscar(int key_, nodo **& nodo_devuelto){
		nodo  **temp=&head;
		while(*(temp)!=NULL && (*temp)->key!=key_){
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

	void borrar(int key_){
		nodo ** nodo_borrar;
		if (buscar(key_,nodo_borrar)){
			nodo * aux= (*nodo_borrar)->next;
			delete (*nodo_borrar);
			*nodo_borrar=aux;
		}
	}

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

    bool buscar(int camiseta_,nodo_punt_jugador **& nodo_devuelto){

		nodo_punt_jugador  **temp=&head;
		while(*(temp)!=NULL && (*temp)->jugador->camiseta<camiseta_){
			temp=&((*temp)->next);
		}
		nodo_devuelto=temp;
		return true;
	}

	void insertar(nodo *jugador_){
	    nodo_punt_jugador *nuevo = new nodo_punt_jugador(jugador_);
		if(!head)
		{
			head=nuevo;
			ultimo=head;
			return;
		}
		nodo_punt_jugador **temp;
		buscar(jugador_->camiseta,temp);
		nuevo->next=*temp;
        *temp=nuevo;
	}
    void borrado(int key_){
		nodo_punt_jugador  **temp=&head;
		while(*(temp)!=NULL && (*temp)->jugador->key!=key_){
			temp=&((*temp)->next);
		}
		*temp = (*temp)->next;
	}

	void imprimir()
	{
	    nodo_punt_jugador *p=head;
		while(p!=NULL){
			cout<<p->jugador->key<<", ";
			cout<<"camiseta: "<<p->jugador->camiseta<<endl;
			cout<<"apellido: "<<p->jugador->apellido<<endl;
			cout<<"posicion: "<<p->jugador->posicion<<endl;
			cout<<"edad: "<<p->jugador->edad<<endl;
			cout<<"seleccion: "<<p->jugador->seleccion<<endl;
			cout<<endl<<endl;
			p=p->next;
		}
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
		if(Buscar(target, ptr, path)){
		    (*ptr)->jugador->insertar(jugador_);
		    return 1;
		}
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
	bool Borrar(T target)///MODIFICAR EL BORRADO, AUN NO ESTA
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
	}

	void Borrar_2(T borrado,int key_)
	{
	    C_Node <T> **ptr;
		vector <C_Node <T> **> path;
        if(Buscar(borrado,ptr,path))
        {
            if((*ptr)->jugador->head->next == NULL)
            {
                Borrar(borrado);
                return;
            }
            (*ptr)->jugador->borrado(key_);
        }
	}
	void Imprimir(C_Node <T> *p, int indent = 0)
	{
		if(p==NULL)
			return;
		Imprimir(p->raices[1], indent+1);

		for(int i=0; i<indent; i++){
			cout<<"   ";
		}
		cout<< p->value <<endl;
		Imprimir(p->raices[0], indent+1);
	}

	void Imprimir_Node(T target)
	{
		C_Node <T> ** a;
		vector<C_Node <T> **>b;
		if(Buscar(target,a,b)){
			(*a)->jugador->imprimir();
		}
	}
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
		posicion->Insertar(posicion_,posicion_jugador);
		edades->Insertar(edad_,posicion_jugador);
	}

	void Borrar(int key_,char posicion_,int edad_,string seleccion_)
	{
		seleccion->Borrar_2(seleccion_,key_);
        posicion->Borrar_2(posicion_,key_);
		edades->Borrar_2(edad_,key_);
		general->borrar(key_);

	}

	void imprimir()
	{
		seleccion->Imprimir(seleccion->raiz);
		cout<<"-------------------------------"<<endl;
		posicion->Imprimir(posicion->raiz);
		cout<<"-----------------------------"<<endl;
		edades->Imprimir(edades->raiz);
	}

	void imprimir_general(){
		general->imprimir();
	}

	void imprimir_by_seleccion(string target)
	{
		seleccion->Imprimir_Node(target);
	}

	void imprimir_by_posicion(char target)
	{
		posicion->Imprimir_Node(target);
	}

	void imprimir_by_edades(int edad_menor, int edad_mayor)
	{
		Lista_Jugadores aux;
		C_Node <int> ** a;
		vector<C_Node <int> **> b;
		nodo_punt_jugador* temp;

		for(int i=edad_menor;i<=edad_mayor;i++){
			if(edades->Buscar(i,a,b)){
				temp = (*a)->jugador->head;
				while(temp!=NULL){
					aux.insertar(temp->jugador);
					temp=temp->next;
				}
			}
		}
		aux.imprimir();
	}



};



int main()
{
	Sistema sistema;
	//Lista a(1,3,"Ocola",'P',18,"Peru");
	sistema.insertar(5,4,"Yato",'A',18,"Ecuador");
	sistema.insertar(6,3,"Ocola",'P',19,"Colombia");
	sistema.insertar(3,8,"cassa",'D',17,"Ecuador");
	sistema.insertar(1,2,"cassa",'D',20,"Ecuador");
	sistema.insertar(3,7,"marica",'M',21,"Peru");
	sistema.insertar(4,20,"jeisson",'M',26,"Ecuador");
	sistema.insertar(6,2,"cassa_marica",'M',28,"Colombia");
	/*sistema.Borrar(6,'M',28,"Colombia");
	sistema.Borrar(4,'M',26,"Ecuador");*/
	//sistema.imprimir_by_seleccion("Ecuador");
	//sistema.imprimir_by_posicion('M');
//	sistema.imprimir_by_edades(15,20);
	//sistema.imprimir();




	int key =0;
	bool salir = true;
	int caso;
	while(salir==true){
		cout<<"\t\t\tMENU:"<<endl<<endl;
        cout<<"\tIngrese 1 si desea Insertar"<<endl;
        cout<<"\tIngrese 2 si desea Borrar"<<endl;
        cout<<"\tIngrese 3 si desea Imprimir el Listado de Jugadores en el Orden en que se Ingresaron"<<endl;
        cout<<"\tIngrese 4 si desea Imprimir el Listado Jugadores por seleccion"<<endl;
        cout<<"\tIngrese 5 si desea Imprimir el Listado Jugadores por posicion"<<endl;
        cout<<"\tIngrese 6 si desea Imprimir el Listado Jugadores por rango de edades"<<endl;
        cout<<"\tIngrese 7 si desea Imprimir los arboles"<<endl;
        cout<<"\tIngrese 0 para salir"<<endl<<endl;
        cin>>caso;
         cout<<endl<<endl;
        switch(caso)
        {
        case 1:{
            int camiseta,edad;
            char posicion;
            string seleccion,apellido;
            cout<<"\tINSERTE LOS DATOS DEL JUGADOR"<<endl;
            cout<<"\tIngrese camiseta: ";
            cin>>camiseta;
            cout<<"\tIngrese edad: ";
            cin>>edad;
            cout<<"\tIngrese posicion: ";
            cin>>posicion;
            cout<<"\tIngrese seleccion: ";
            cin>>seleccion;
            cout<<"\tIngrese apellido: ";
            cin>>apellido;
            sistema.insertar(key,camiseta,apellido,posicion,edad,seleccion);
            key++;
            cout<<"\tEl jugador fue insertado"<<endl;
            cout<<endl<<endl;
            break;
        }
        case 2:
        {
            int camiseta,edad;
            char posicion;
            string seleccion,apellido;
            cout<<"\tINSERTE LOS DATOS DEL JUGADOR"<<endl;
            cout<<"\tIngrese camiseta: ";
            cin>>camiseta;
            cout<<"\tIngrese edad: ";
            cin>>edad;
            cout<<"\tIngrese posicion: ";
            cin>>posicion;
            cout<<"\tIngrese seleccion: ";
            cin>>seleccion;
            cout<<"\tIngrese apellido: ";
            cin>>apellido;
            int key = sistema.general->buscar_2(camiseta,apellido,posicion,edad,seleccion);
            sistema.Borrar(key,posicion,edad,seleccion);
            cout<<endl<<endl;
            break;
        }
        case 3:{
            sistema.imprimir_general();
            cout<<endl<<endl;
            break;
        }
        case 4:{
            string seleccion;
            cout<<"\tIngrese seleccion: ";
            cin>>seleccion;
            cout<<endl;
            sistema.imprimir_by_seleccion(seleccion);
            cout<<endl<<endl;
            break;
        }
        case 5:
        {
            char posicion;
            cout<<"\tIngrese posicion: ";
            cin>>posicion;
            cout<<endl;
            sistema.imprimir_by_posicion(posicion);
            cout<<endl<<endl;
            break;
        }
        case 6:
        {
            int edad,edad2;
            cout<<"\tIngrese rango de edad menor: ";
            cin>>edad;
            cout<<"\tIngrese rango de edad mayor: ";
            cin>>edad2;
            cout<<endl;
            sistema.imprimir_by_edades(edad,edad2);
            cout<<endl<<endl;
            break;
        }
        case 7:
            {
                sistema.imprimir();
            }
        case 0:
            {
                salir = false;
            }

        }
	}


	return 0;
}
