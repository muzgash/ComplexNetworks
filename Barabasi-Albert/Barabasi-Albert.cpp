#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

//Correct implementation of the module function
int mod(int a, int b){return (a>=0) ? a%b : a%b+abs(b); }

//Checks if the number is already on a vector
int is(vector<int> vertex, int number) {
    for( vector<int>::iterator it = vertex.begin(); it != vertex.end(); it++){
		    if ( number == *it ) return number;
	}
	return -1;
}

double averageDegree( vector< vector<int> > network ) {
    double sum=0.0;
    for( vector< vector<int> >::iterator it=network.begin(); it != network.end(); it++) {
	    sum += (*it).size();
	}
	return sum/network.size();
}

double averageClusteringCoefficient( vector< vector<int> > network ) {
    int edgesCount;
	int N=network.size();
	double clusteringCoefficient=0.0;
	int degree;
	for( vector< vector<int> >::iterator nit = network.begin(); nit != network.end(); nit++ ) {
	    edgesCount = 0;
		degree = (*nit).size();
		//First we run through the i-th node
	    for( vector<int>::iterator it = (*nit).begin(); it != (*nit).end(); it++){
		    // searching if a neightbor vertex is connecteed with another by
			// comparing the i-th's neightbors with the neighbors of its neightbors.
		    for( vector<int>::iterator it2 = it; it2 != (*nit).end(); it2++ ) {
			    if( is(network[*it],*it2) != -1 ) edgesCount++;
			}
		}
		clusteringCoefficient += 2.0*edgesCount/(double(degree*(degree-1.0)));
	}
    return clusteringCoefficient/N;
}

vector< vector<int> > BAModel( vector< vector<int> > network, int steps ) {
    //params
	//    m_0: initial condition.
    //    steps: the number of "time" steps.
	srand48(time(NULL));
	double r=0;
	int N;
    for( int t = 0; t < steps; t++ ) {
	    N=network.size();
	    double AD = N*averageDegree(network);
	    vector<int> tmp;
	    network.push_back(tmp);

	    for( int n = 0; n < N; n++ ) {
	        r=drand48();
			cout<<r<<" "<<network.at(n).size()/AD<<endl;
	        if( r < network.at(n).size()/AD ) {
		        network.at(n).push_back(N);
			    network.at(N).push_back(n);
		    }
	    }
	}
	return network;
}

vector< vector<int> > regularRing( int N, int k ) {
    vector<int> tmp;
    vector< vector<int> > graph(N,tmp);
	for( int i = 0; i < N; i++ ) {
	    vector<int> node;
        int edge;

		for( int j = 1; j <= k/2 ; j++ ) {
		    edge = mod(i+j,N);
			graph.at(i).push_back(edge);
			graph.at(edge).push_back(i);
		}
	}

	return graph;
}

void printGraph( vector< vector<int> > graph ) {
	for( vector< vector<int> >::iterator it = graph.begin(); it != graph.end(); it++ ) {
	    for( vector<int>::iterator it2 = (*it).begin(); it2 != (*it).end(); it2++){
		    cout<<*it2<<' ';
		}
		cout<<endl;
	}
}




int main(int argc, char *argv[]) {
	//int NN=atoi(argv[1]), kk=atoi(argv[2]);
    vector< vector<int> > BANetwork,initial_network;

	initial_network = regularRing(6,4);
	cout<<initial_network.size()<<endl;

	printGraph(initial_network);

	BANetwork = BAModel(initial_network,6);

	cout<<endl;

	printGraph(BANetwork);

    return 0;
}
