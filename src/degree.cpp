#include<degree.h>
#include<vector>

int mod(int a, int b){
    return (a>=0) ? a%b : a%b+abs(b);
}


int isIn(vector<int> ivVertex, int iNumber) {
    for( vector<int>::iterator it = ivVertex.begin(); it != ivVertex.end(); it++){
		    if ( iNumber == *it ) return iNumber;
	}
	return -1;
}

double averageDegree( vector< vector<int> > ivvNetwork ) {
    double dSum=0.0;
	int iSize=ivvNetwork.size();
    for( int i = 0; i < iSize ; i++) {
	    dSum += ivvNetwork[i].size();
	}
	return dSum/double(iSize);

}

double averageClusteringCoefficient( vector< vector<int> > ivvNetwork ) {
    int iEdgesCount;
	int N = ivvNetwork.size();
	double dClusteringCoefficient=0.0;
	int iDegree;
	for( int i = 0; i < N; i++ ) {
	    iEdgesCount = 0;
		iDegree = ivvNetwork[i].size();
		//First we run through the i-th node
	    for( vector<int>::iterator it = ivvNetwork[i].begin(); it != ivvNetwork[i].end(); it++){
		    // searching if a neightbor vertex is connecteed with another by
			// comparing the i-th's neightbors with the neighbors of its neightbors, got it?
		    for( vector<int>::iterator it2 = it; it2 != ivvNetwork[i].end(); it2++ ) {
			    if( isIn(ivvNetwork[*it],*it2) != -1 && *it2 != i ) iEdgesCount++;
			}
		}
		dClusteringCoefficient += 2.0*iEdgesCount/(double(iDegree*(iDegree-1.0)));
	}
    return dClusteringCoefficient/N;
}


