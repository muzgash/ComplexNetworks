#include<Network.h>
#include<Node.hpp>
#include<queue>
#include<map>
#include<omp.h>



#include<iostream>



using namespace std;





void printGraph( vector< Node > graph ) {
    int iIndex=0;
	for( vector< Node >::iterator it = graph.begin(); it != graph.end(); it++ ) {
	    //cout<<graph.at(iIndex).getOpinion()<<" ";
	    for( vector<int>::iterator it2 = (*it).begin(); it2 != (*it).end(); it2++){
		    cout<<*it2<<' ';
		}
		cout<<endl;
	}
}





int main(int argc, char **argv) {

    vector< Node > vnInitialRing,vnSocialImpact;

    vnInitialRing=ring(6,3);

	vnSocialImpact=barabasiAlbertModel(vnInitialRing,1000,4);

    //printGraph(vnSocialImpact);
	
	omp_set_num_threads(3);
	#pragma omp parallel for
	for( int i = 0; i < vnSocialImpact.size(); i++) {
	    vnSocialImpact.at(i).setDistances(vnSocialImpact);
		//vnSocialImpact.at(i).printDistances();
	}

    int iPositiveOpinionSum;
	for( int time = 0; time < 200; time++ ) {
	    iPositiveOpinionSum=0;
	    for( int i = 0; i < vnSocialImpact.size(); i++) {
		    vnSocialImpact.at(i).setImpact(vnSocialImpact);
		    if( vnSocialImpact.at(i).timeStep(0) == 1 ) iPositiveOpinionSum+=1;
		}
		//if( time > 20 ) 
		cout<<time<<" "<<iPositiveOpinionSum<<endl;
	}

	

    return 0;
}
