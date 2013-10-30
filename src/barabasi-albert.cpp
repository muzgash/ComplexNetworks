#include<degree.h>
#include<network.h>
#include<iostream>

using namespace std;

//Useful function for small networks
void printGraph( vector< vector<int> > graph ) {
	for( vector< vector<int> >::iterator it = graph.begin(); it != graph.end(); it++ ) {
	    for( vector<int>::iterator it2 = (*it).begin(); it2 != (*it).end(); it2++){
		    cout<<*it2<<' ';
		}
		cout<<endl;
	}
}

int main(int argc, char *argv[]) {

    vector< vector<int> > BANetwork,initial_network;

	initial_network = ring(6,4);
	//cout<<initial_network.size()<<endl;

	printGraph(initial_network);

	BANetwork = barabasiAlbertModel(initial_network,6);

	cout<<endl;

	printGraph(BANetwork);
   
	

    return 0;
}
