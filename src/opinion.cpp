#include<Node.hpp>
#include<Network.h>




#include<iostream>




using namespace std;




//Useful function for small networks
void printGraph( vector< Node > graph ) {
    int iIndex=0;
	for( vector< Node >::iterator it = graph.begin(); it != graph.end(); it++ ) {
	    cout<<graph.at(iIndex).getOpinion()<<" ";
	    for( vector<int>::iterator it2 = (*it).begin(); it2 != (*it).end(); it2++){
		    cout<<*it2<<' ';
		}
		cout<<endl;
	}
}




int main(int argc, char** argv) {

    vector< Node > initialRing,ws;

    initialRing=ring(6,3);

	ws=barabasiAlbertModel(initialRing,20,4);	

    return 0;
}
