#include <iostream>
#include <list>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;


//Put this in error handling
#define N 8
//k must be even
#define k 4
#define p 0.5

//Correct implementation of the module function
int mod(int a, int b){return (a>=0) ? a%b : a%b+abs(b); }

int main ( int argc, char* argv[] ) {

    //Initialize the random number generators' seeds
	srand48(time(NULL));
	srand(time(NULL));

    //Creating a regular ring
    /*list<int> *graph;
	graph = new list<int>[N];
	for( int i = 0; i < N; i++ ) {
        int nodes[k];
		for( int j = -k/2; j <= k/2 ; j++ ) {
		    if( j < 0 ) nodes[j+(k/2)] = mod(i+j,N);
			else if( j > 0 ) nodes[j+(k/2)-1] = mod(i+j,N);
		}
		list<int> tmp(nodes, nodes + sizeof(nodes) / sizeof(int));
		graph[i]=tmp;
	}*/

	//The ring creation is not necessary since we know it's gonna change
	//so to save a whole run through the graph we set the probabilities
	//and create the WS graph from the beginning.
	list<int> *wsGraph;
	wsGraph = new list<int>[N];
	for( int i = 0; i < N; i++ ) {
        int nodes[k];
		for( int j = -k/2; j <= k/2 ; j++ ) {
		    if( j < 0 ) nodes[j+(k/2)] = mod(i+j,N);
			else if( j > 0 ) {
			    if( drand48() < p ) { //If P -> rewire with a normal distribution
			        nodes[j+(k/2)-1] = mod(random()%(k+1)+(i+1),7);
			    }
			    else nodes[j+(k/2)-1] = mod(i+j,N);
			}
		}
		list<int> tmp(nodes, nodes + sizeof(nodes) / sizeof(int));
		wsGraph[i]=tmp;
	}
	

	//Displaying the ring
	//#ifdef DEBUG
	for( int i = 0; i < N;i++ ) {
	    for( list<int>::iterator it = wsGraph[i].begin(); it != wsGraph[i].end(); it++){
		    cout<<*it<<' ';
		}
		cout<<endl;
	}
	//#endif
    return 0;
}
