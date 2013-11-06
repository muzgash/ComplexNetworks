#include<degree.h>
#include<network.h>
#include<iostream>
#include<fstream>

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
	ofstream time("ba-times.dat");

	initialNetwork = ring(4,2);
	//cout<<initialNetwork.size()<<endl;

	//printGraph(initialNetwork);

	//cout<<endl;
	clock_t begin,end;
	time<<"Size\tConstruction\tClustering Coefficient\nSPL"<<endl;
	for( int i = 10; i<1000; i++ ) {
	    begin=clock();
	    BANetwork = barabasiAlbertModel(initialNetwork,i,4);
	    end=clock();
		time<<4+i<<"\t"<<double(end-begin)/CLOCKS_PER_SEC<<"\t";
	    begin=clock();
	    averageClusteringCoefficient(BANetwork);
	    end=clock();
		time<<double(end-begin)/CLOCKS_PER_SEC<<"\t";
	    begin=clock();
	    averageShortestPathLength(BANetwork);
	    end=clock();
		time<<double(end-begin)/CLOCKS_PER_SEC<<"\t"<<endl;
	}

	cout<<"Time of construction "<<double(end-begin)/CLOCKS_PER_SEC<<endl;

	//printGraph(BANetwork);
	begin=clock();
    cout<<"The average clustering coefficient is: "<<averageClusteringCoefficient(BANetwork)<<endl;
	end=clock();
	cout<<"Time of clustering coefficient calculus "<<double(end-begin)/CLOCKS_PER_SEC<<endl;
	begin=clock();
	cout<<"The average shortest path is: "<<averageShortestPathLength(BANetwork)<<endl;
	end=clock();
	cout<<"Time of SPL calculus "<<double(end-begin)/CLOCKS_PER_SEC<<endl;
	

    return 0;
}
