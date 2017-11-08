#include <iostream>
#include <vector>
using namespace std;

template<class G>
struct CEdge{
	typedef typename G::Node_ Node;
	typedef typename G::E_ E;
	
	Node * m_nodes[2];
	E m_data;
	bool m_dir;//0 bidireccional, 1 va de 0 a 1 (0->1)
};

template<class G>
struct CNode{
	typedef typename G::Edge_ Edge;
	typedef typename G::N_ N;
	
	N m_data;
	vector <Edge*> m_edges;
};

template <class N, class E>
class CGraph{
public:
	typedef CGraph<N,E> self;
	typedef CNode<self> Node_;
	typedef CEdge<self> Edge_;
	typedef N N_;
	typedef E E_;
	
	vector<Node_*> m_node;
	insert_Node();
	remove_edge();
	remove_node();
};

int main(int argc, char *argv[]) {
	CGraph <char,int> g;
	
	return 0;
}

