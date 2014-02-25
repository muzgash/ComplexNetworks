#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <iterator>
#include <iostream>

using namespace std;



/*!\brief Mother node class. Contains the basic information of an agent in a network
 */
class Node {

    public:

	    Node(int iIndex);

		vector<int>::iterator begin(){return _viNeighbors.begin();}
		vector<int>::iterator end(){return _viNeighbors.end();}

		//void printDistances();
		void printNeighbors();

        //void setDistances(vector< Node > &vnNetwork);

        //Accesor methods
        int getIndex(){return _iIndex;}
		vector< int > getNeighbors(){return _viNeighbors;}
		int getSize(){return _viNeighbors.size();}
		//vector<int> getDistances(){return _viDistances;}
		
		//Mutator methods
		void pushBackNeighbor(int iNewNeighbor){_viNeighbors.push_back(iNewNeighbor);}

	private:
		vector<int> _viNeighbors; //Adjacency list

        int _iIndex;

		vector<int>::iterator _it;
		//vector<int> _viDistances;
};



#endif
