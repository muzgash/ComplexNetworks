#include<Node.hpp>




#include<random>
#include<iostream>
#include<chrono>




using namespace std;




Node::Node() {
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

}
