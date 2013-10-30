#include<network.h>
#include<degree.h>
#include<cstdlib>
#include<ctime>

using namespace std;

vector< vector<int> > ring( int iSize, int iAverageDegree ) {
    vector<int> ivTmp;
    vector< vector<int> > ivvGraph(iSize,ivTmp);
	for( int i = 0; i < iSize; i++ ) {
        int iEdge;

		for( int j = 1; j <= iAverageDegree/2 ; j++ ) {
		    iEdge = mod(i+j,iSize);
			ivvGraph.at(i).push_back(iEdge);
			ivvGraph.at(iEdge).push_back(i);
		}
	}

	return ivvGraph;
}

vector< vector<int> > wattsStrogatzModel(int iSize, int iAverageDegree, double dProbability) {
	srand48(time(NULL));
	srand(time(NULL));

	vector< vector<int> > ivvWSNetwork;
	for ( int i = 0; i < iSize; i++ ) {
	    vector<int> ivNode;
		ivvWSNetwork.push_back(ivNode);
	}
	for( int i = 0; i < iSize; i++ ) {//runs trhough every node
		int iNeighbor;
		for( int j = 1; j <= iAverageDegree/2 ; j++ ) { //runs through the k/2 neighbors to the "right"
			    if( drand48() < dProbability ) { //If P -> rewire with a normal distribution
				    iNeighbor = mod(random()%(iAverageDegree+1)+(i+1),iSize);

			    }
			    else iNeighbor = mod(i+j,iSize);
				
				if(  isIn(ivvWSNetwork[i],iNeighbor) == -1 ) ivvWSNetwork[i].push_back(iNeighbor);
				if(  isIn(ivvWSNetwork[iNeighbor],i) == -1 ) ivvWSNetwork[iNeighbor].push_back(i);
		}
	}
    return ivvWSNetwork;
}

vector< vector<int> > barabasiAlbertModel( vector< vector<int> > ivvNetwork, int iSteps ) {

	srand48(time(NULL));
	double r;
	int iSize;
    for( int t = 0; t < iSteps; t++ ) {
	    iSize=ivvNetwork.size();
	    double dAverageDegree = iSize*averageDegree(ivvNetwork);
	    vector<int> ivTmp;
	    ivvNetwork.push_back(ivTmp);

	    for( int n = 0; n < iSize; n++ ) {
	        r=drand48();
	        if( r < ivvNetwork.at(n).size()/dAverageDegree ) {
		        ivvNetwork.at(n).push_back(iSize);
			    ivvNetwork.at(iSize).push_back(n);
		    }
	    }
	}
	return ivvNetwork;
}
