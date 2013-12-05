#include<Degree.h>
#include<Node.hpp>
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




double averageDegree( vector< Node > ivvNetwork ) {
    double dSum=0.0;
	int iSize=ivvNetwork.size();
    for( int i = 0; i < iSize ; i++) {
	    dSum += ivvNetwork[i]._viNeighbors.size();
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
		//This is because if the degree of a vertex is 1 iDegree-1 is zero and
		//it produces a nan so the clustering coefficient for that node is zero
		if (iEdgesCount == 0) dClusteringCoefficient+=0;
		else dClusteringCoefficient += 2.0*iEdgesCount/(double(iDegree*(iDegree-1.0)));
	}
    return dClusteringCoefficient/double(N);
}




int BFS( vector< vector<int> >ivvNetwork, int iVertex ) {

   int N = ivvNetwork.size();
   int u;//Current last vertex on the queue

   //int NIL = -1;

   char pcColor[N]; //w for white, g for gray and b for black
   //black if a vertex is visited
   //gray if a vertex has a visited neighbor
   //white if the vertex is unvisited

   //int piPredecesor[N];//We're summing the distances and don0t need the resultant tree
   int *piDistance;piDistance = new int[N];
   queue<int> qiGrayVertex;//queue of unvisited (gray) vertices
   int iSPLSum=0;

   //I don't think this is necessary but for the sake of clarity
   //We fill the color array with white vertices and
   //the Distance array with 0 dintance "to itself"
   for(int i = 0; i<N; i++) {
       if( i == iVertex ) continue; //Taking out the vertex from which we calculate the distances
	   pcColor[i] = 'w';
	   piDistance[i] = 0;
	   //piPredecesor[i] = NIL;
   }

   pcColor[iVertex] = 'g';
   piDistance[iVertex] = 0;
   //piPredecesor[iVertex] = NIL;
   qiGrayVertex.push(iVertex);

   while( !qiGrayVertex.empty() ) {
       u=qiGrayVertex.front();//Take the last element
	   qiGrayVertex.pop();//and dequeue it

       //Iteration over the neighbors of the u vertex
	   for( vector<int>::iterator it = ivvNetwork[u].begin(); it != ivvNetwork[u].end(); it++ ) {
	       if( pcColor[*it] == 'w' ) {//If it isn't visited
		       pcColor[*it] = 'g'; //mark it as visited but not fully analized
			   piDistance[*it] = piDistance[u]+1;//Sum 1 to the distance of its predecesor
			   //piPredecesor[*it] = u;
			   qiGrayVertex.push(*it);//put it in the queue since is reached bi a neighbor but not visited yet
			   iSPLSum+=piDistance[*it];//Add to the sum of distances
		   }
	   }
	   pcColor[u]='b';//I thik this isn't needed since the condition only spects white vertices

   }
   delete[] piDistance;
   //return piDistance;
   return iSPLSum;
}




double averageShortestPathLength( vector< vector<int> > ivvNetwork ) {
    double dSum=0;
	int iSize = ivvNetwork.size();
	//Loop to calculate the sum of the dinstances from every vertex, to every other.
	for(int i = 0; i < iSize; i++ ) {
	    dSum+=BFS(ivvNetwork,i);
	}
    //It is divided by two, because BFS the algorithm sums twice
	//the shortest path beetwen two nodes
	return dSum/(2*(iSize)*(iSize-1));
}
