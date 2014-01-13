#include<Node.hpp>




#include<random>
#include<iostream>
#include<chrono>
#include<queue>




using namespace std;




Node::Node(int iIndex) {
    _iIndex=iIndex;
    _it=_viNeighbors.begin();
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	random_device rd;

	double max=double(rd.max()),ran=double(rd())/max;

	//srand48(time(NULL));
	double dOpinionProbability=0.5;
	if ( ran < dOpinionProbability ) setOpinion(true);
	else setOpinion(false);

	//Normal distributed random number generation
	default_random_engine generator(seed);
	normal_distribution<double> distribution(0,31);//mean 0 and sd 31
	_dSupportiveness = distribution(generator);
	_dPersuasiveness = distribution(generator);
	cout<<_bOpinion<<" "<<_dSupportiveness<<" "<<_dPersuasiveness<<endl;

}




void Node::setDistances(vector< Node > vnNetwork, int iVertex) {
    int N = vnNetwork.size();
    int u;//Current last vertex on the queue

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
	    qiGrayVertex.pop();//and dequeue it

        //Iteration over the neighbors of the u vertex
	    for( vector<int>::iterator it = vnNetwork[u].begin(); it != vnNetwork[u].end(); it++ ) {
	        if( pcColor[*it] != 'g' || pcColor[*it] !='b' ) {//If it isn't visited
		        pcColor[*it] = 'g'; //mark it as reached but not visited
			    piDistance[*it] = piDistance[u]+1;//Sum 1 to the distance of its predecesor
			    qiGrayVertex.push(*it);//put it in the queue since is reached by a neighbor but not visited yet

	 	    }
	    }
	    pcColor[u]='b';//I thik this isn't needed since the condition only expects white vertices
	    cout<<endl;
    }
    delete[] piDistance;
}
