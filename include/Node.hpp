#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <iterator>
#include <iostream>

using namespace std;



/*!\brief Node class which will contain the agents to opine
 */
class Node {

    public:

	    Node(int iIndex);

		vector<int> _viNeighbors; //Adjacency list

		vector<int>::iterator begin(){return _viNeighbors.begin();}
		vector<int>::iterator end(){return _viNeighbors.end();}

		void printDistances();

		void setOpinion(bool bOpinion){_bOpinion=bOpinion;}
        void setDistances(vector< Node > &vnNetwork);
		void setImpact(vector< Node > &vnNetwork);

		int timeStep(double dNoise);

        int getIndex(){return _iIndex;}
		bool getOpinion(){return _bOpinion;}
		double getPersuasiveness(){return _dPersuasiveness;}
		double getSupportiveness(){return _dSupportiveness;}
		vector<int> getDistances(){return _viDistances;}

	private:


        int _iIndex;
	    bool _bOpinion;
		double _dSupportiveness,_dPersuasiveness;
		double _dImpact;

		vector<int>::iterator _it;
		vector<int> _viDistances;
};









#endif
