#include<degree.h>
#include<vector>
#include<queue>
#include<iostream>

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

int* BFS( vector< vector<int> >ivvNetwork, int iVertex ) {

   int N = ivvNetwork.size();
   int u;

   int NIL = -1;

   char cColor[N]; //w for white, g for gray and b for black
   int iPredecesor[N];
   int *iDistance;iDistance = new int[N];
   queue<int> qiGrayVertex;

   for(int i = 0; i<N; i++) {
       if( i == iVertex ) continue; //Taking out the vertex from which we calculate the distances
	   cColor[i] = 'w';
	   iDistance[i] = 0;
	   iPredecesor[i] = NIL;
   }

   cColor[iVertex] = 'g';
   iDistance[iVertex] = 0;
   iPredecesor[iVertex] = NIL;
   qiGrayVertex.push(iVertex);

   while( !qiGrayVertex.empty() ) {
       u=qiGrayVertex.front();//Take the last element
	   qiGrayVertex.pop();//and dequeue it

	   for( vector<int>::iterator it = ivvNetwork[u].begin(); it != ivvNetwork[u].end(); it++ ) {
	       if( cColor[*it] == 'w' ) {
		       cColor[*it] = 'g';
			   iDistance[*it] = iDistance[u]+1;
			   iPredecesor[*it] = u;
			   qiGrayVertex.push(*it);
		   }
	   }
	   cColor[u]='b';

   }
   return iDistance;
}
