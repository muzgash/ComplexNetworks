#ifndef NODE_HPP
#define NODE_HPP

#include<vector>
#include <iterator>

using namespace std;



/*!\brief Node class which will contain the agents to opine
 */
class Node {

    public:

	    Node();

		vector<int>::iterator begin(){return _viNeighbors.begin();}
		vector<int>::iterator end(){return _viNeighbors.end();}

		vector<int> _viNeighbors; //Adjacency list

		void setOpinion(bool bOpinion){_bOpinion=bOpinion;}
		bool getOpinion(){return _bOpinion;}

	private:

	    bool _bOpinion;

		vector<int>::iterator _it;
};


#endif
