#include<Network.h>
#include<Degree.h>
#include<Node.hpp>
#include<cstdlib>
#include<ctime>
#include<iostream>
#include<random>

using namespace std;

vector< Node > ring( int iSize, int iAverageDegree ) {
    vector< Node > ivvGraph;
	for( int i = 0; i < iSize; i++ ) {
	  Node nTmp(i);
	  ivvGraph.push_back(nTmp);
	}
	for( int i = 0; i < iSize; i++ ) {
        int iEdge;

		for( int j = 1; j <= iAverageDegree/2 ; j++ ) {
		    iEdge = mod(i+j,iSize);
			ivvGraph.at(i)._viNeighbors.push_back(iEdge);
			ivvGraph.at(iEdge)._viNeighbors.push_back(i);
		}
	}

	return ivvGraph;
}

vector< Node > wattsStrogatzModel(int iSize, int iAverageDegree, double dProbability) {
    random_device rd;
	double ran_max=double(rd.max()),ran;

	vector< Node > ivvWSNetwork;
	for ( int i = 0; i < iSize; i++ ) {
	    Node ivNode(i);
		ivvWSNetwork.push_back(ivNode);
	}
	for( int i = 0; i < iSize; i++ ) {//runs trhough every node
		int iNeighbor;
		for( int j = 1; j <= iAverageDegree/2 ; j++ ) { //runs through the k/2 neighbors to the "right"
		        ran=double(rd())/ran_max;
			    if( ran < dProbability ) { //If P -> rewire with a normal distribution
				    ran=rd();
					cout<<ran<<endl;
				    iNeighbor = mod(int(ran)%(iAverageDegree+1)+(i+1),iSize);

			    }
			    else iNeighbor = mod(i+j,iSize);
				
				if(  isIn(ivvWSNetwork[i]._viNeighbors,iNeighbor) == -1 ) ivvWSNetwork[i]._viNeighbors.push_back(iNeighbor);
				if(  isIn(ivvWSNetwork[iNeighbor]._viNeighbors,i) == -1 ) ivvWSNetwork[iNeighbor]._viNeighbors.push_back(i);
		}
	}
    return ivvWSNetwork;
}

vector< Node > barabasiAlbertModel( vector< Node > ivvNetwork,
                                           int iSteps, int iConectivity ) {

	srand48(time(NULL));
	double r;
	int iSize;
	int iInitialSize=ivvNetwork.size();
	double dProbSum;//Sums the probabilities to obtain the next interval
	vector<int>::iterator eraseNodeIt,eraseDegreeIt;//iterator to erase the wired node
    for( int t = 0; t < iSteps; t++ ) {
	    iSize=ivvNetwork.size();
	    double dDegreeSum = iSize*averageDegree(ivvNetwork);
	    Node ivTmp(iInitialSize+t);
	    ivvNetwork.push_back(ivTmp);


		//Create two vectors one with the degrees and the other with the number of the vertex
		vector<int> viDegree;
		vector<int> viVertex;
		for(int iVertex = 0; iVertex < iSize; iVertex++) {
		    viDegree.push_back(ivvNetwork[iVertex]._viNeighbors.size());
			viVertex.push_back(iVertex);
		}
		
		
		for(int m = 0; m < iConectivity; m++ ){
		//Sum of the values to calculate the interval equal zero,
		//throw a random number, and search for the vertex, conect it and erase it from the map
			vector<int>::iterator itDegree = viDegree.begin();
			vector<int>::iterator itVertex = viVertex.begin();
		    r=drand48();
			dProbSum=0;
			//Since both vectors have the same number of items we use a while on viDegree
			while( itDegree != viDegree.end() ) {
			    //If the random number fall in the interval
	
			    if( r>dProbSum && r<=dProbSum+(*itDegree)/dDegreeSum ){
				    //Save the iterators for later removal
				    eraseNodeIt=itVertex;
					eraseDegreeIt=itDegree;
					//Connect the nodes
					ivvNetwork.at(*itVertex)._viNeighbors.push_back(iSize);
					ivvNetwork.at(iSize)._viNeighbors.push_back(*itVertex);
				}
				//Update the lower bound of the probability
				dProbSum+=(*itDegree)/dDegreeSum;
				//IOncrement both iterators
				itDegree++;
				itVertex++;
			}//end of nodes loop
			//Since a node is going to be removed, we update the sum of the degrees
			dDegreeSum=(dDegreeSum-(*eraseDegreeIt))*dProbSum;
			//Erase the node from both vectors
			viDegree.erase(eraseDegreeIt);
			viVertex.erase(eraseNodeIt);
	
		}//end of m loop

	}//end of steps loop
	return ivvNetwork;
}
