#include<Network.h>
#include<Node.hpp>
#include<queue>



#include<iostream>



using namespace std;





void printGraph( vector< Node > graph ) {
    int iIndex=0;
	for( vector< Node >::iterator it = graph.begin(); it != graph.end(); it++ ) {
	    cout<<graph.at(iIndex).getOpinion()<<" ";
	    for( vector<int>::iterator it2 = (*it).begin(); it2 != (*it).end(); it2++){
		    cout<<*it2<<' ';
		}
		cout<<endl;
	}
}




double impact(vector< Node > vnNetwork, int iVertex) {
   }

int main(int argc, char **argv) {

    vector< Node > vnInitialRing,vnSocialImpact;

    vnInitialRing=ring(6,3);

	vnSocialImpact=barabasiAlbertModel(vnInitialRing,8,4);

    printGraph(vnSocialImpact);

	for(int i=0; i<vnSocialImpact.size(); i++) {
	    cout<<"Total impact: "<<impact(vnSocialImpact,i)<<endl;
	}

    return 0;
}
