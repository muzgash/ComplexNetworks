#include<Network.h>
#include<Node.hpp>



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





int main(int argc, char **argv) {

    vector< Node > vnInitialRing,vnSocialImpact;

    vnInitialRing=ring(6,3);

	vnSocialImpact=barabasiAlbertModel(vnInitialRing,20,4);	

    return 0;
}
