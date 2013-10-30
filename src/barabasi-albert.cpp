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

    vector< vector<int> > BANetwork,initialNetwork;

	initialNetwork = ring(4,2);
	//cout<<initialNetwork.size()<<endl;

	printGraph(initialNetwork);

	//cout<<endl;
	

	BANetwork = barabasiAlbertModel(initialNetwork,4);

	cout<<endl;

	printGraph(BANetwork);
   
	
	int* iDistance;iDistance = new int[8];
	for( int s = 0; s < 8; s++){
	    iDistance = BFS(BANetwork,s);
		cout<<"Distances from vertex "<<s<<" to the rest"<<endl;
	    for( int i = 0; i < 8; i++ ) {
	        cout<<iDistance[i]<<" ";
	    }
		cout<<endl;
	}

    return 0;
}
