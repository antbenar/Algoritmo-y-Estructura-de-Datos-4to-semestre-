#include <iostream>
#include <vector>
using namespace std;

template<class G>
struct CEdge{
	typedef typename G::Node Node_;
	typedef typename G::E_ E;
	
	Node_ * m_nodes[2];
	E m_data;
	bool m_dir;//0 bidireccional, 1 va de 0 a 1 (0->1)
	
	CEdge(Node_ *a, Node_ *b, bool dir, E dato)
	{
		m_nodes[0] = a;
		m_nodes[1] = b;
		m_data = dato;
		m_dir=dir;
	}
};

template<class G>
struct CNode{
	typedef typename G::Edge Edge_;
	typedef typename G::N_ N;
	
	N m_data;
	vector <Edge_*> m_edges;
	//N peso = -1;
	
	CNode(N dato)
	{
		m_data = dato;
	}
};

template <class N, class E>
class CGraph{
public:
	typedef CGraph<N,E> self;
	typedef CNode<self> Node;
	typedef CEdge<self> Edge;
	typedef N N_;
	typedef E E_;
	
	vector<Node*> m_nodes;
	
	bool find(N dato,Node *&devuelto)
	{
		for(int i=0;i<m_nodes.size();i++)
		{
			if(m_nodes[i]->m_data == dato)
			{
				devuelto = m_nodes[i];
				return 1;
			}
		}
		return 0;
	}
	
	bool InsertNode(N x)
	{
		Node *temp;
		if(!find(x,temp))
		{
			Node *nuevo = new Node(x);
			m_nodes.push_back(nuevo);
			return 1;
		}
		return 0;
	}
	
	bool InsertEdge(N a,N b,bool dir,E dato)
	{
		Node *aux;
		Node *aux2;
		if(find(a,aux) && find(b,aux2))
		{
			if(dir == 0)
			{
				Edge *nuevo2 = new Edge(aux2,aux,dir,dato);
				aux->m_edges.push_back(nuevo2);
				aux2->m_edges.push_back(nuevo2);
				cout<<"se inserto la arista con peso "<<dato<<" de "<<aux2->m_data<<" a "<<aux->m_data<<endl;
			}
			Edge *nuevo = new Edge(aux,aux2,dir,dato);
			aux->m_edges.push_back(nuevo);
			aux2->m_edges.push_back(nuevo);
			cout<<"se inserto la arista con peso "<<dato<<" de "<<aux->m_data<<" a "<<aux2->m_data<<endl;
			return 1;
		}
		return 0;
	}
	
	bool find_edge(Node *x,Node *b,E t,Edge *&re, int& pos)
	{
		for(int i=0;i<x->m_edges.size();i++)
		{
			if(x->m_edges[i]->m_nodes[1]==b )//&& x->m_edges[i] == t)
			{
				re = x->m_edges[i];
				pos = i;
				return 1;
			}
		}
		return 0;
	}
	
<<<<<<< HEAD
	bool borrarEdgeByDato(N a, N b, E dato){
		Node *devuelto;
		Node* devuelto2;
		Edge *arista_devuelta;
		int pos;
		if(find(a,devuelto) && find(b,devuelto2) && find_edge(devuelto,devuelto2,dato,arista_devuelta,pos)){
			devuelto->m_edges.erase(devuelto->m_edges.begin()+pos);
		}
	}
	
=======
	bool borrarEdgeByDato(N a, N b, bool dir, E dato){
		Node *devuelto;
		Node* devuelto2;
		Edge * Edge_aux;
		int  pos;
		if(find(a,devuelto) && find(b,devuelto2) && find_edge(devuelto,devuelto2, dato, Edge_aux, pos)){
			borrarEdge(devuelto,Edge_aux);
			borrarEdge(devuelto2,Edge_aux);
			if(dir!=1){
				find_edge(devuelto2,devuelto, dato, Edge_aux, pos);
				borrarEdge(devuelto,Edge_aux);
				borrarEdge(devuelto2,Edge_aux);
			}
			return 1;
		}
		return 0;
	}
	
	
>>>>>>> origin/master
	bool borrarEdge(Node* nodo1, Edge* Edge_){
		
		for(int i=0;i<nodo1->m_edges.size();i++)
		{
			if(nodo1->m_edges[i]==Edge_ )
			{
				nodo1->m_edges.erase( nodo1->m_edges.begin()+i);
				cout<<"se borro del nodo \""<<nodo1->m_data<<"\" la arita "<<Edge_->m_nodes[0]->m_data<<" -- "<<Edge_->m_data<<" -> "<<Edge_->m_nodes[1]->m_data<<endl;
				return 1;
			}
		}
		return 0;
	}
	
	bool borrarNodo(N x)
	{
		Node *aux;
		if(find(x,aux))
		{
			int j=aux->m_edges.size();
			Edge * Edge_aux;
			for(int i=0;i<j;i++)
			{//cout<<aux->m_edges[0]->m_nodes[1]->m_data<<endl;		
				Edge_aux = aux->m_edges[0];//SE HACE UNA COPIA DE LA ARISTA PORQUE DESPUES DE BORRARLA EN EL PRIMERO, SE USA EN EL SEGUNDO
				borrarEdge(Edge_aux->m_nodes[0],Edge_aux);//cout<<aux->m_edges[0]->m_nodes[1]->m_data<<" aaaaaaaaaa"<<endl;
				borrarEdge(Edge_aux->m_nodes[1],Edge_aux);
			}
			return 1;
		}
		return 0;
	}
	
	void imprimir()
	{
		vector<Edge*> aux;
		for(int i=0;i<m_nodes.size();i++)
		{
			aux = m_nodes[i]->m_edges;
			cout<<"Nodo "<<m_nodes[i]->m_data<<endl;
			cout<<"-------------------"<<endl;
			for(int j=0;j<aux.size();j++)
			{
				cout<<aux[j]->m_nodes[0]->m_data<<" -- "<<aux[j]->m_data<<" -> "<<aux[j]->m_nodes[1]->m_data<<endl;
			}
			cout<<endl;
		}
		cout<<"_______________________________________"<<endl;
	}
<<<<<<< HEAD
=======
	
	void DIJKSTRA(Node a, Node b){
		
		
	}
	
>>>>>>> origin/master
};

int main(int argc, char *argv[]) {
	CGraph <char,int> g;
	g.InsertNode('a');
	g.InsertNode('b');
	g.InsertNode('c');
	g.InsertNode('d');
	
	g.InsertEdge('a','b',0,2);
	g.InsertEdge('b','c',1,3);
	g.InsertEdge('d','b',0,4);
<<<<<<< HEAD
	
	
	//g.borrarEdgeByDato('d','b',4);
	g.imprimir();
	g.borrarNodo('b');
=======
	
	g.InsertEdge('a','c',0,2);
	
	g.imprimir();
	g.borrarEdgeByDato('d','b',0,4);
	//g.borrarNodo('b');
>>>>>>> origin/master
	g.imprimir();
	return 0;
}
