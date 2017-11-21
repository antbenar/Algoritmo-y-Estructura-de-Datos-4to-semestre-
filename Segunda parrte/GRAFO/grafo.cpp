#include <iostream>
#include <vector>
#define INFINITE 1000000
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
				//cout<<"se inserto la arista con peso "<<dato<<" de "<<aux2->m_data<<" a "<<aux->m_data<<endl;
			}
			Edge *nuevo = new Edge(aux,aux2,dir,dato);
			aux->m_edges.push_back(nuevo);
			aux2->m_edges.push_back(nuevo);
			//cout<<"se inserto la arista con peso "<<dato<<" de "<<aux->m_data<<" a "<<aux2->m_data<<endl;
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
	
	bool borrarEdgeByDato(N a, N b, E dato){
		Node *devuelto;
		Node* devuelto2;
		Edge * Edge_aux;
		int  pos;
		if(find(a,devuelto) && find(b,devuelto2) && find_edge(devuelto,devuelto2, dato, Edge_aux, pos)){
			borrarEdge(devuelto,Edge_aux);
			borrarEdge(devuelto2,Edge_aux);
			if(Edge_aux->m_dir!=1){
				find_edge(devuelto2,devuelto, dato, Edge_aux, pos);
				borrarEdge(devuelto,Edge_aux);
				borrarEdge(devuelto2,Edge_aux);
			}
			return 1;
		}
		return 0;
	}
	
	
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
	
	bool findNodePos(Node* a, int& pos){
		if(a==0){
			return 0;
		}
		int i;
		for(i=0;i<m_nodes.size();i++){
			if(m_nodes[i]==a){
				pos=i;
				return 1;
			}
		}
		return 0;
	}
	void DIJKSTRA(Node* a, Node* b, vector<E> &dist, vector<Node*>&previous){
		//vector<E> dist(m_nodes.size(),INFINITE);
		//vector<Node*> previous(m_nodes.size(),NULL);
		dist.clear();
		dist.resize(m_nodes.size(),INFINITE);
		previous.clear();
		previous.resize(m_nodes.size(),nullptr);
		
		int i,j,v,pos;
		vector<Node*>Q = m_nodes;
		int Q_size = Q.size();
		findNodePos(a,i);
		Node* u=Q[i];
		dist[i]=0;
		E aux=0;
		while (Q_size != 0){
			for(j=0;j < dist.size();j++){//BUSCO LA MENOR DISTANCIA
				if( Q[j] )aux=dist[j];
			}
			
			for(j=0;j < dist.size();j++){//BUSCO LA MENOR DISTANCIA
				//cout<<i<<" dist: "<<dist[j]<<" aux: "<<aux<<endl;
				if(Q[j] && dist[j]<=aux){
					aux=dist[j];//cout<<"cccccccccccccccccccccccccccc"<<endl;
					u = Q[j];//cout<<Q[j]->m_data<<endl;
					Q[j]=nullptr;//LA EXTRAIGO DE Q Y LA USO PARA EL CALCULO DE DISTANCIAS
					--Q_size;
					i=j;
				}
			}
			
			if (dist[i] == INFINITE or Q[i]==b){
				break;
			}
			//cout << i;break;
			for(v=0 ; v < u->m_edges.size() ; v++){			//cout<<u->m_data;break;
				if(u->m_edges[v]->m_nodes[0]==u){
					aux = dist[i] + u->m_edges[v]->m_data;//cout<<"i "<<dist[i]<<" aux: "<<u->m_edges[v]->m_data<<endl;
					findNodePos(u->m_edges[v]->m_nodes[1], pos);
					if(aux < dist[pos] ) {//cout<<"cccccccc"<<endl;
						dist[pos] = aux;
						previous[pos] = u;
					}
				}
			}
		}
		
		vector<Node*> previous_result;
		vector<E> dist_result;
		findNodePos(b, pos);
		previous_result.push_back(b);
		while (previous[pos]!=0){
			//cout<<previous[pos]->m_data<<endl;
			//cout<<dist[pos]<<endl;
			//cout<<pos<<endl;
			dist_result.push_back(dist[pos]);
			previous_result.push_back(previous[pos]);
			findNodePos(previous[pos], pos);
		}
		
		imprimirDijkstra(dist_result,previous_result);
	}

	void imprimirDijkstra(vector<E> dist, vector<Node*> previous){
		for(int i = 0; i<dist.size() ; i++){
			cout<<"previo de "<< previous[i]->m_data <<" es: " << previous[i+1]->m_data << " con peso: "<< dist[i] <<endl;
		};
	}
};

int main(int argc, char *argv[]) {
	CGraph <char,int> g;
	g.InsertNode('1');
	g.InsertNode('2');
	g.InsertNode('3');
	g.InsertNode('4');
	g.InsertNode('5');
	g.InsertNode('6');
	
	g.InsertEdge('1','2',0,7);
	g.InsertEdge('1','3',0,9);
	g.InsertEdge('1','6',0,14);
	g.InsertEdge('6','3',0,2);
	g.InsertEdge('2','3',0,10);
	g.InsertEdge('2','4',0,15);
	g.InsertEdge('3','4',0,11);
	g.InsertEdge('6','5',0,9);
	g.InsertEdge('4','5',0,6);
	
	vector<int>dist;
	vector< CNode < CGraph<char,int> >* > previous;
	g.DIJKSTRA(g.m_nodes[0],g.m_nodes[4],dist,previous);
	
	return 0;
}
