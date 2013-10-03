#include <iostream>
#include <list>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

//Correct implementation of the module function
int mod(int a, int b){return (a>=0) ? a%b : a%b+abs(b); }

list<int>* regularRing(int N, int k) {
    list<int> *graph;
	graph = new list<int>[N];
	for( int i = 0; i < N; i++ ) {
        int nodes[k];
		for( int j = -k/2; j <= k/2 ; j++ ) {
		    if( j < 0 ) nodes[j+(k/2)] = mod(i+j,N);
			else if( j > 0 ) nodes[j+(k/2)-1] = mod(i+j,N);
		}
		list<int> tmp(nodes, nodes + sizeof(nodes) / sizeof(int));
		graph[i]=tmp;
	}

	return graph;
}

list<int>* WSModel(int N,int k,double p) {

	srand48(time(NULL));
	srand(time(NULL));

	list<int> *wsGraph;
	wsGraph = new list<int>[N];
	for( int i = 0; i < N; i++ ) {
        int nodes[k];
		for( int j = -k/2; j <= k/2 ; j++ ) {
		    if( j < 0 ) nodes[j+(k/2)] = mod(i+j,N);
			if( j > 0 ) {
			    if( drand48() < p ) { //If P -> rewire with a normal distribution
			        nodes[j+(k/2)-1] = mod(random()%(k+1)+(i+1),7);
			    }
			    else nodes[j+(k/2)-1] = mod(i+j,N);
			}
		}
		list<int> tmp(nodes, nodes + sizeof(nodes) / sizeof(int));
		wsGraph[i]=tmp;
	}
    return wsGraph;
}

void printGraph(list<int> *graph, int N) {
	for( int i = 0; i < N;i++ ) {
	    for( list<int>::iterator it = graph[i].begin(); it != graph[i].end(); it++){
		    cout<<*it<<' ';
		}
		cout<<endl;
	}
}

int main ( int argc, char* argv[] ) {
    
	int NN = 8, kk = 4;
	double pp = 0.2;

	list<int> *ws;

	ws = WSModel(NN,kk,pp);
	

	//#ifdef DEBUG
	printGraph(ws,NN);
	//#endif
    return 0;
}
