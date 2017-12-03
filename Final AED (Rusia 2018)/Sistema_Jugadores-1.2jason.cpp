#include <iostream>
#include <stack>
#include <vector>
#include <stdlib.h>

using namespace std;

class nodo{///jugador
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
		key = key_;
		next = NULL;

		///datos jugador
		camiseta = camiseta_;
		apellido = apellido_;
		posicion = posicion_;
		edad = edad_;
		seleccion = seleccion_;
	}

	nodo(nodo *nuevo)
	{
		key = nuevo->key_;
		next = NULL;

		camiseta = nuevo->camiseta;
		apellido = nuevo->apellido;
		posicion = nuevo->posicion;
		edad = nuevo->edad;
		seleccion = nuevo->seleccion;
	}

	nodo()

};

template<class T>
class Lista{///General y las listas de jugadores de ciertas edades, posiciones y  selecciones
public:
	nodo *head;
	nodo *ultimo;
	int num_nodos;

	Lista(Lista *general, T dato, string tipo_dato)///dato viene del  nodo del arbol
	{
	    nodo temp = general->head;
	    nodo temp2 = head;
	    switch(tipo de dato)
	    {
            case "seleccion":
                while(temp){
                    if(temp->seleccion == dato){
                        nodo *nuevo = new nodo(temp);
                        temp2 = nuevo;
                        temp2 = temp2->next;
                        ultimo = temp2;
                    }
                }
                break;
            case "edad":
                while(temp){
                    if(temp->edad == dato){
                        nodo *nuevo = new nodo(temp);
                        temp2 = nuevo;
                        temp2 = temp2->next;
                        ultimo = temp2;
                    }
                }
                break;
            case "posicion";
                while(temp){
                    if(temp->edad == dato){
                        nodo *nuevo = new nodo(temp);
                        temp2 = nuevo;
                        temp2 = temp2->next;
                        ultimo = temp2;
                    }
                }
                break;
	    }
	}

	Lista(int key_, int camiseta_, string apellido_, char posicion_, int edad_, string seleccion_)
	{
		head = new nodo  (key_,camiseta_, apellido_, posicion_, edad_, seleccion_);
		ultimo = head;
		num_nodos++;
	}

	Lista()
	{
		head = NULL;
		ultimo = head;
	}

	void swap1(nodo<T> *&a, T *&b)///?????
    {
        T temp;
        temp = *num1;
        *num1 = *num2;
        *num2 =temp;
    }

	void ordenar()
	{
	    nodo *temp = head;
	    ///???
	}

	~Lista(){
		nodo *temp=head;
		while(temp != NULL){
			head = head->next;
			delete temp;
			temp = head;
		}
	}

	bool buscar(int key_, nodo **& nodo_devuelto){
		nodo  **temp = &head;

		while(*(temp)!= NULL && (*temp)->key<key_){
			temp = &((*temp)->next);
		}
		nodo_devuelto=temp;
		if((*temp) == NULL || (*temp)->key != key_){
			return false;
		}
		return true;
	}

	void insertar_tree(nodo *jugador){///metodo insertar de las listas apuntadas por los nodos de los arboles avl
		if(!head)
		{
			head = jugador;
			ultimo = head;
			return;
		}
		ultimo->next = jugador;
		ultimo = jugador;
	}


	void insertar(int key_, int camiseta_, string apellido_, char posicion_, int edad_, string seleccion_,nodo* jugador_actual){///metodo insertar de general
		if(!head)
		{
			nodo *aux = new nodo (key_, camiseta_, apellido_, posicion_, edad_, seleccion_);
			head = aux;
			ultimo = head;
			///jugador_actual = aux;
			return;
		}
		nodo * aux = new nodo (key_, camiseta_, apellido_, posicion_, edad_, seleccion_);
		ultimo->next = aux;
		ultimo = aux;
		///jugador_actual = aux;

	}

	void borrar(int key_){
		nodo ** nodo_borrar;
		if (buscar(key_, nodo_borrar)){
			nodo *aux = (*nodo_borrar)->next;
			delete (*nodo_borrar);
			*nodo_borrar=aux;
		}
	}

	void imprimir(){
		nodo *p = head;
		while(p != NULL){
			cout << p->key<<", ";
			cout << "camiseta: " << p->camiseta << endl;
			cout << "apellido: " << p->apellido << endl;
			cout << "posicion: " << p->posicion << endl;
			cout << "edad: "<<p->edad<<endl;
			cout << "seleccion: "<< p->seleccion << endl;
			cout << endl << endl;
			p=p->next;
		}
	}
};

///---------------------------------------------------------------------------------------------------------------------------------
///Implementacion de Arboles AVL
template <class T>
class C_Node///Nodo de arbol avl
{

public:
	T value;
	C_Node <T> *raices[2];
	int h_right;
	int h_left;
	Lista* jugador;

public:
	C_Node(T value, C_Node <T> *left, C_Node <T> *right)
	{
		this->value = value;
		raices[0] = left;
		raices[1] = right;
		h_right = 0;
		h_left = 0;
	}
};


template <class T>
class AVL_Tree///Arbol avl de selecciones, posiciones y edades
{

public:
    T dato; ///seleccion, edad o posicion
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
		C_Node <T> *newNode = new C_Node <T> (target, NULL , NULL);
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
		newNode->jugador->insertar_tree(jugador_);
		return 1;
	}

	bool Borrar(T target)
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
};


///------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
///Implementacion del sistema controlador
class Sistema{
public:
	AVL_Tree<string>* selecciones;
	AVL_Tree<char>* posiciones;
	AVL_Tree<int>* edades;
	Lista *general;
	Sistema(){
		selecciones = new AVL_Tree<string>;
		posiciones = new AVL_Tree<char>;
		edades = new AVL_Tree<int>;
		general = new Lista();
	}
	void insertar(int key_, int camiseta_, string apellido_, char posicion_, int edad_, string seleccion_){///insertar un nuevo jugador
//	    string selecciones[] = {"Nigeria", "Egipto", "Senegal", "Marruecos", "Tunez", "Brasil", "Uruguay", "Argentina", "Colombia", "Peru",  "Iran", "Japon", "Corea del Sur", "Arabia Saudita",
//	    "Mexico", "Costa Rica", "Panama", "Alemania", "Inglaterra", "Belgica", "Espania", "Polonia", "Islandia", "Serbia", "Francia", "Portugal", "Suiza", "Croacia", "Dinamarca", "Suecia", "Rusia", "Australia"};
//	    int edades[] = {17,18,19,20,21,22,23,24,252,62,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43};
//	    char posiciones[] = {'P', 'D', 'M', 'A'}; ///a = delantero(atacante)
		nodo *posicion_jugador;

		general->insertar(key_,camiseta_, apellido_, posicion_, edad_, seleccion_,posicion_jugador);
		selecciones->insertar_tree(seleccion_, posicion_jugador);
        posiciones->Insertar_tree(posicion_);
		edades->Insertar_tree(edad_);
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
//	sistema.insertar(2,4,"Yato",'A',18,"Peru");
//	sistema.insertar(1,3,"Ocola",'P',18,"Peru");
//
//	sistema.imprimir();
    char opcion;
    while(num != 0){
        cout << " Presione i para insertar, e para eliminar, p para imprimir o s para salir : "; cin >> opcion;
        if(opcion == 'i'){
            cout << "Escriba un valor para insertar : ";
            sistema.insertar();
        }
        else if(opcion == 'e'){
            cout << "Escriba un valor para eliminar : ";
        }

        else if(opcion == 's'){
            num = 0;
        }
    }

	return 0;
}
