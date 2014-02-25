#include<Node.hpp>




#include<iostream>
//#include<queue>





using namespace std;




Node::Node(int iIndex) {
    _iIndex=iIndex;
    _it=_viNeighbors.begin();
}

void Node::printNeighbors() {
    for( int i = 0; i < _viNeighbors.size(); i++ ) {
	    cout<<_viNeighbors.at(i)<<" ";
	}
	cout<<endl;
	_it=_viNeighbors.begin();
}


/*
void Node::printDistances() {
    cout<<"size: "<<_viDistances.size()<<endl;
    for( int i = 0; i < _viDistances.size(); i++ ) {
	    cout<<i<<" => "<<_viDistances[i]<<endl;
	}
}*/


/*
void Node::setDistances(vector< Node > &vnNetwork) {
    int N = vnNetwork.size();
    //_viDistances.reserve(N);
    _viDistances.resize(N);
	int iVertex=_iIndex;
    int u;//Current last vertex on the queue

    char pcColor[N]; //w for white, g for gray and b for black
	//black if a vertex is visited
	//gray if a vertex has a visited neighbor
	//white if the vertex is unvisited

	int *piDistance;piDistance = new int[N];
	queue<int> qiGrayVertex;//queue of unvisited (gray) vertices

	pcColor[iVertex] = 'g';
	piDistance[iVertex] = 0;
	for(int i = 0; i<N; i++) {
		if( i == iVertex ) continue; //Taking out the vertex from which we calculate the distances
		pcColor[i] = 'w';
		piDistance[i] = 0;
	}

   qiGrayVertex.push(iVertex);

	while( !qiGrayVertex.empty() ) {
		u=qiGrayVertex.front();//Take the last element
		qiGrayVertex.pop();//and dequeue it

		//Iteration over the neighbors of the u vertex
		for( vector<int>::iterator it = vnNetwork[u].begin(); it != vnNetwork[u].end(); it++ ) {
			if( pcColor[*it] == 'w' ) {//If it isn't visited
				pcColor[*it] = 'g'; //mark it as reached but not visited
				piDistance[*it] = piDistance[u]+1;//Sum 1 to the distance of its predecesor
				qiGrayVertex.push(*it);//put it in the queue since is reached by a neighbor but not visited yet
				_viDistances[*it]=piDistance[*it];
			}
		}
		pcColor[u]='b';//I thik this isn't needed since the condition only expects white vertices
	}
	delete[] piDistance;


}*/
/*int Node::timeStep(double dNoise) {
    //The inequality reverses since the evolution rule has a minus sign outside the sign function
    ( _bOpinion*_dImpact+dNoise < 0) ? _bOpinion=true:_bOpinion=false;
    if( _bOpinion == true ) return 1;
	else return -1;
}*/

