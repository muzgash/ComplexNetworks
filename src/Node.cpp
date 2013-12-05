#include<Node.hpp>



#include<random>
#include<iostream>
#include<ctime>
#include<cstdlib>




using namespace std;




Node::Node() {
    _it=_viNeighbors.begin();

	random_device rd;

	double max=double(rd.max()),ran=double(rd())/max;

	//srand48(time(NULL));
	double dOpinionProbability=0.5;
	if ( ran < dOpinionProbability ) setOpinion(true);
	else setOpinion(false);

}
