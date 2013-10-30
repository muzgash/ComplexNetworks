#include<degree.h>
#include<network.h>
#include<iostream>

using namespace std;

void printGraph( vector< vector<int> > graph ) {
	for( vector< vector<int> >::iterator it = graph.begin(); it != graph.end(); it++ ) {
	    for( vector<int>::iterator it2 = (*it).begin(); it2 != (*it).end(); it2++){
		    cout<<*it2<<' ';
		}
		cout<<endl;
	}
}

int main(int argc, char *argv[]) {
    
	int NN=atoi(argv[1]), kk=atoi(argv[2]);

	vector< vector<int> > ws;

	ws=ring(NN,kk);
	
	double Co=double(3.0*((kk/2.0)-1)/(2.0*(kk-1)));
	for(double i = 0.0; i <= 1.0; i+=0.001){
		ws = wattsStrogatzModel(NN,kk,i);
		cout<<i<<" "<<averageClusteringCoefficient(ws)/Co<<endl;
	}



	return 0;
}
