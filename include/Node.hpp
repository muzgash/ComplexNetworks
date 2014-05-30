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

		void printNeighbors();

        //Accesor methods
        int getIndex(){return _iIndex;}
		int getSize(){return _viNeighbors.size();}
		vector< int > getNeighbors(){return _viNeighbors;}
		
		//Mutator methods
		/*!\brief Append nighbors to the back of the adjacency listt
		 * @param int iNewNeighbor: Index of the new neighbor
		 */
		void pushBackNeighbor(int iNewNeighbor){_viNeighbors.push_back(iNewNeighbor);}

	private:
	    ///Adjacency list
		vector<int> _viNeighbors;

        int _iIndex;

		vector<int>::iterator _it;
};



#endif
