#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <iterator>
#include <map>

using namespace std;



/*!\brief Node class which will contain the agents to opine
 */
class Node {

    public:

	    Node(int iIndex);

		vector<int>::iterator begin(){return _viNeighbors.begin();}
		vector<int>::iterator end(){return _viNeighbors.end();}

		vector<int> _viNeighbors; //Adjacency list

        void pushDistance(int iNode, int iDistance);
		void setDistances(vector< Node > vnNetwork, int iVertex);
		map<int,int> getDistances(){return _miiDistances;}

		void setOpinion(bool bOpinion){_bOpinion=bOpinion;}
		bool getOpinion(){return _bOpinion;}
		double getPersuasiveness(){return _dPersuasiveness;}
		double getSupportiveness(){return _dSupportiveness;}

	private:

        int _iIndex;
	    bool _bOpinion;
		double _dSupportiveness,_dPersuasiveness; //suportiveness and presuasiveness

		vector<int>::iterator _it;
		map<int,int> _miiDistances;
};


#endif
