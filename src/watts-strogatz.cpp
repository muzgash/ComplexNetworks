#include<degree.h>
#include<network.h>
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

void printGraph( vector< vector<int> > graph ) {
    ofstream wsCSV("ws.csv");
	int node=0;
	for( vector< vector<int> >::iterator it = graph.begin(); it != graph.end(); it++ ) {
	    wsCSV<<node<<";";
	    for( vector<int>::iterator it2 = (*it).begin(); it2 != (*it).end(); it2++){
		    wsCSV<<*it2<<";";
		}
		node++;
		wsCSV<<endl;
	}
}

int main(int argc, char *argv[]) {
    
	int NN=atoi(argv[1]), kk=atoi(argv[2]),totalProcs=atoi(argv[3]),actualProc=atoi(argv[4]);
	string procId=argv[5];
	string name;
	name="ws-spl.dat."+procId;
	ofstream spl(name.c_str());
	name="ws-acc.dat."+procId;
	ofstream acc(name.c_str());
	//ofstream time("ws-spl-time.dat");

	vector< vector<int> > ws;

	//clock_t begin,end,begin_cc,end_cc,begin_spl,end_spl;

	//begin=clock();
	ws=ring(NN,kk);

	double Lo=averageShortestPathLength(ws);//Average shortest path length of a ring;
	double Co=double(3.0*((kk/2.0)-1)/(2.0*(kk-1)));//Clusterign coefficient of a ring.

    double dPart=1.0/totalProcs;
	double min=actualProc*dPart,max=min+dPart;

	//end=clock();
	//time<<"Tiempo de contrucción y cálculo del anillo: "<<double(end-begin)/CLOCKS_PER_SEC<<endl;
	//time<<"Probability\tConstruction\tClustering Coefficient\tSPL"<<endl;
	for(double i = min; i < max; i+=0.001){
		//begin=clock();
		ws = wattsStrogatzModel(NN,kk,i);
		//end=clock();
		//begin_cc=clock();
		acc<<i<<" "<<averageClusteringCoefficient(ws)/Co<<endl;
		//end_cc=clock();
		//begin_spl=clock();
		spl<<i<<" "<<averageShortestPathLength(ws)/Lo<<endl;
		//end_spl=clock();
	    //time<<i<<"\t"<<double(end-begin)/CLOCKS_PER_SEC;
		//time<<"\t"<<double(end_cc-begin_cc)/CLOCKS_PER_SEC;
		//time<<"\t"<<double(end_spl-begin_spl)/CLOCKS_PER_SEC<<endl;

	}
	printGraph(ws);
	spl.close();
	acc.close();
	//time.close();



	return 0;
}
