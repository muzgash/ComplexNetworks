#include<Node.hpp>

#include<iostream>

using namespace std;

Node::Node(int iIndex) {
    _iIndex=iIndex;
    _it=_viNeighbors.begin();
}

void Node::printNeighbors() {
    for( int i = 0; i < _viNeighbors.size(); i++ ) {
	    cout<<_viNeighbors.at(i)<<" ";
	}
	cout<<endl;
	_it=_viNeighbors.begin();
}


