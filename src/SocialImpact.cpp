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
   int N = vnNetwork.size();
   int u;//Current last vertex on the queue
   double dImpact=0;
   double dSupportiveness, dPersuasiveness;
   bool bOpinion;
   int iOpinion,iSelfOpinion;
   if(vnNetwork.at(iVertex).getOpinion()==true) iSelfOpinion=1;
   else iSelfOpinion=-1;

   char pcColor[N]; //w for white, g for gray and b for black
   //black if a vertex is visited
   //gray if a vertex has a visited neighbor
   //white if the vertex is unvisited

   int *piDistance;piDistance = new int[N];
   queue<int> qiGrayVertex;//queue of unvisited (gray) vertices

   pcColor[iVertex] = 'g';
   piDistance[iVertex] = 0;
   qiGrayVertex.push(iVertex);

   while( !qiGrayVertex.empty() ) {
       u=qiGrayVertex.front();//Take the last element
	   //cout<<"Node "<<u<<" "<<vnNetwork[u].getOpinion()<<" "<<vnNetwork[u].getPersuasiveness()<<" ";
	   //cout<<vnNetwork[u].getSupportiveness()<<" ";
	   qiGrayVertex.pop();//and dequeue it

       //Iteration over the neighbors of the u vertex
	   for( vector<int>::iterator it = vnNetwork[u].begin(); it != vnNetwork[u].end(); it++ ) {
	       if( pcColor[*it] != 'g' || pcColor[*it] !='b' ) {//If it isn't visited
		       pcColor[*it] = 'g'; //mark it as reached but not visited
			   piDistance[*it] = piDistance[u]+1;//Sum 1 to the distance of its predecesor
			   qiGrayVertex.push(*it);//put it in the queue since is reached by a neighbor but not visited yet

			   dSupportiveness=vnNetwork.at(*it).getSupportiveness();
			   dPersuasiveness=vnNetwork.at(*it).getPersuasiveness();
			   bOpinion=vnNetwork.at(*it).getOpinion();
			   if(bOpinion==true) iOpinion=1;
			   else iOpinion=-1;
			   dImpact+=dPersuasiveness*(1-iOpinion*iSelfOpinion)/double(piDistance[*it]*piDistance[*it]);
			   dImpact+=dSupportiveness*(1+iOpinion*iSelfOpinion)/double(piDistance[*it]*piDistance[*it]);
		   }
	   }
	   pcColor[u]='b';//I thik this isn't needed since the condition only expects white vertices
	   cout<<endl;
   }
   delete[] piDistance;
   return dImpact;
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
