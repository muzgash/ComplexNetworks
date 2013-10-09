#include <iostream>
#include <list>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

//Correct implementation of the module function
int mod(int a, int b){return (a>=0) ? a%b : a%b+abs(b); }

//Checks if the number is already on a list
int is(list<int> vertex, int number) {
    for( list<int>::iterator it = vertex.begin(); it != vertex.end(); it++){
		    if ( number == *it ) return number;
	}
	return -1;
}

double averageDegree( list<int>* network, int N ) {
    double sum=0.0;
    for( int i = 0; i < N; i++) {
	    sum += network[i].size();
	}
	return sum/double(N);
}

double averageClusteringCoefficient( list<int> *network, int N ) {
    int edgesCount;
	double clusteringCoefficient=0.0;
	int degree;
	for( int i = 0; i < N; i++ ) {
	    edgesCount = 0;
		degree = network[i].size();
		//First we run through the i-th node
	    for( list<int>::iterator it = network[i].begin(); it != network[i].end(); it++){
		    // searching if a neightbor vertex is connecteed with another by
			// comparing the i-th's neightbors with the neighbors of its neightbors.
		    for( list<int>::iterator it2 = it; it2 != network[i].end(); it2++ ) {
			    if( is(network[*it],*it2) != -1 && *it2 != i ) edgesCount++;
			}
		}
		clusteringCoefficient += 2.0*edgesCount/(double(degree*(degree-1.0)));
	}
    return clusteringCoefficient/N;
}

list<int>* regularRing(int N, int k) {
    list<int> *graph;
	graph = new list<int>[N];
	for( int i = 0; i < N; i++ ) {
        int node;
		for( int j = 1; j <= k/2 ; j++ ) {
		    node = mod(i+j,N);
			graph[i].push_back(node);
			graph[node].push_back(i);
		}
	}

	return graph;
}

list<int>* WSModel(int N,int k,double p) {

	srand48(time(NULL));
	srand(time(NULL));

	list<int> *wsNetwork;
	wsNetwork = new list<int>[N];
	for( int i = 0; i < N; i++ ) {//runs trhough every node
        int node;
		for( int j = 1; j <= k/2 ; j++ ) { //runs through the k/2 neighbors to the "right"
			    if( drand48() < p ) { //If P -> rewire with a normal distribution
				    node = mod(random()%(k+1)+(i+1),N);
			    }
			    else node = mod(i+j,N);
				
				if(  is(wsNetwork[i],node) == -1 ) wsNetwork[i].push_back(node);
				if(  is(wsNetwork[node],i) == -1 ) wsNetwork[node].push_back(i);
		}
	}
    return wsNetwork;
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

	if( argc > 4 || argc < 2) {
		cout<<"Not enough,too many or invalid arguments:.\n";
		cout<<"Use: ws Vertices Conectivity Probability\n";
		//cout<<"OPTIONS:\n\t-d\t debugging flag\n";
		return 1;
	}

	int NN=atoi(argv[1]), kk=atoi(argv[2]);
	double pp=atof(argv[3]);
    
	list<int> *ws;

	
	#ifdef DEBUG
	printGraph(ws,NN);
	#endif

	cout<<"The average degree is =  "<<averageDegree(ws,NN)<<endl;
	cout<<"The clustering coefficient is = "<<averageClusteringCoefficient(ws,NN)<<endl;
	double Co=double(3.0*((kk/2.0)-1)/(2.0*(kk-1)));
	for(double i = 0.0; i <= 1.0; i+=0.001){
		ws = WSModel(NN,kk,i);
		cout<<i<<" "<<averageClusteringCoefficient(ws,NN)/Co<<endl;
	}

    return 0;
}
