#ifndef NETWORK_HPP
#define NETWORK_HPP

#include<vector>
#include<random>
#include<iostream>

using namespace std;



/*!\brief Mother class for networks, it needs a node to operate.
 */
template<class node>
class Network
{
  public:
    Network();

	//Accesor Methods
	vector<node> getNetwork(){return _vnNetwork;}
	int getSize(){return _iSize;}
	char* getType(){return _pcType;}
	double getAverageDegree(){return _dAverageDegree;}
	//Not yet implemented
	double getAvereageClusteringCoefficient(){return _dAverageClusteringCoefficient;}
	//Not yet implemented
	double getAverageShortestPathLength(){return _dAverageShortestPathLength;}

	//Mutator Methods
	void setNetwork(vector<node> vnNetwork);
	void setSize(int iSize);
	void setAverageDegree(double dAverageDegree);
	void setAverageClusteringCoefficient();
	void setAverageShortestPathlength();

	//Network types creators
	/*!\brief sets a regular ring from a size and degree previously set.
	 */
	void setRing();

	/*!\brief Fills _vnNetwork with a Watts-Strogatz model network from a ring
	 * @param double dProbability:  
	 */
	void setWattsStrogatz(double dProbability);

	/*!\brief Fills _vnNetwork with a Barabási-Albert model network from a ring
	 * @param int iSteps: Additional nodes for the network.
	 * @param int iConnectivity: Degree of the new node for each iStep.
	 */
	void setBarabasiAlbert(int iSteps, int iConnectivity);

	//Adding Methods
	/*!\brief Append a node.
	 * @param node nNode:
	 */
	void addNode(node nNode);

	//Printing Functions
	/*!\brief Print the adjacency lists of every node.
	 */
	void printNetwork();

  private:
    int _iSize;
    char* _pcType;
	double _dAverageDegree;
	double _dAverageClusteringCoefficient;
	double _dAverageShortestPathLength;

  protected:
	vector<node> _vnNetwork;
};




//UTILITY FUNCTIONS

int mod(int a, int b){
    return (a>=0) ? a%b : a%b+abs(b);
}

int isIn(vector<int> ivVertex, int iNumber) {
    for( vector<int>::iterator it = ivVertex.begin(); it != ivVertex.end(); it++){
		    if ( iNumber == *it ) return iNumber;
	}
	return -1;
}

template <class node>
double averageDegree( vector<node> vnNetwork ) {
    double dSum=0.0;
	int iSize=vnNetwork.size();
    for( int i = 0; i < iSize ; i++) {
	    dSum += vnNetwork.at(i).getSize();
	}
	return dSum/double(iSize);

}

//CLASS CONSTRUCTOR
template <class node>
Network<node>::Network(){}

//PRINTING FUNCTIONS
template <class node>
void Network<node>::printNetwork(){
    for( int i = 0; i < _iSize; i++ ) {
	    cout<<"NODE_"<<i<<endl;
	    _vnNetwork.at(i).printNeighbors(); 
	}
}

//NETWORK SETUP METHODS
template<class node>
void Network<node>::setNetwork(vector<node> vnNetwork) {
    _vnNetwork=vnNetwork;
}

template<class node>
void Network<node>::setSize(int iSize) {
    _iSize=iSize;
}

template<class node>
void Network<node>::setAverageDegree(double dAverageDegree) {
    _dAverageDegree=dAverageDegree;
}

//NETWORK CREATORS

template <class node>
void Network<node>::setRing() {
	for( int i = 0; i < _iSize; i++ ) {
	  node nTmp(i);
	  _vnNetwork.push_back(nTmp);
	}
	for( int i = 0; i < _iSize; i++ ) {
        int iEdge;

		for( int j = 1; j <= _dAverageDegree/2 ; j++ ) {
		    iEdge = mod(i+j,_iSize);
			_vnNetwork.at(i).pushBackNeighbor(iEdge);
			_vnNetwork.at(iEdge).pushBackNeighbor(i);
		}
	}
}



template<class node>
void Network<node>::setWattsStrogatz(double dProbability) {
    random_device rd;
	double ran_max=double(rd.max()),ran;

	for ( int i = 0; i < _iSize; i++ ) {
	    node ivNode(i);
		_vnNetwork.push_back(ivNode);
	}
	for( int i = 0; i < _iSize; i++ ) {//runs trhough every node
		int iNeighbor;
		for( int j = 1; j <= _dAverageDegree/2 ; j++ ) { //runs through the k/2 neighbors to the "right"
		        ran=double(rd())/ran_max;
			    if( ran < dProbability ) { //If P -> rewire with a normal distribution
				    ran=rd();
					//cout<<ran<<endl;
				    iNeighbor = mod(int(ran)%((int)_dAverageDegree+1)+(i+1),_iSize);

			    }
			    else iNeighbor = mod(i+j,_iSize);
				
				if(  isIn(_vnNetwork.at(i).getNeighbors(),iNeighbor) == -1 )
				    _vnNetwork.at(i).pushBackNeighbor(iNeighbor);
				if(  isIn(_vnNetwork.at(iNeighbor).getNeighbors(),i) == -1 )
				    _vnNetwork.at(iNeighbor).pushBackNeighbor(i);
		}
	}
}

template<class node>
void Network<node>::setBarabasiAlbert(int iSteps, int iConnectivity) {
    setRing();//Initial Ring
	srand48(time(NULL));
	double r; //random number
	int iSize; //Changing size of the network
	int iInitialSize=_vnNetwork.size(); //Size of the initial network
	double dProbSum;//Sums the probabilities to obtain the next interval
	double dDegreeSum;//The changing degree of the network

	vector<int>::iterator eraseNodeIt,eraseDegreeIt;//iterator to erase the wired node
    for( int t = 0; t < iSteps; t++ ) {
	    iSize=_vnNetwork.size();
	    dDegreeSum = iSize*averageDegree(_vnNetwork);
	    node nTmp(iInitialSize+t);
	    _vnNetwork.push_back(nTmp);

		//Create two vectors one with the degrees and the other with the number of the vertex
		vector<int> viDegree;
		vector<int> viVertex;
		for(int iVertex = 0; iVertex < iSize; iVertex++) {
		    viDegree.push_back(_vnNetwork.at(iVertex).getSize());
			viVertex.push_back(iVertex);
		}
		
		
		for(int m = 0; m < iConnectivity; m++ ){
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
					_vnNetwork.at(*itVertex).pushBackNeighbor(iSize);
					_vnNetwork.at(iSize).pushBackNeighbor(*itVertex);
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
	_iSize=_vnNetwork.size();
}

#endif
