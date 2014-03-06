#ifndef NETWORKSIS_HPP
#define NETWORKSIS_HPP

#include<Network.hpp>
#include<random>

#include<iostream>

using namespace std;

template<class node>
class NetworkSIS : public Network<node>
{
  public:
    NetworkSIS();

	void markovStep();
	void montecarloStep();
	void setProbabilityOfTransmission(double dProbabilityOfInfection);
	void setInitialInfectedDensity(double dInitialDensity);
	void setInitialProbabilityOfInfection(double dInitialProbability);
	void printNetwork();

	double getDensity(){return _dDensity;}

  private:
    double _dDensity;
	double _dProbabilityOfTransmission;//Beta
};




template<class node>
NetworkSIS<node>::NetworkSIS()
{
}

template<class node>
void NetworkSIS<node>::printNetwork()
{
    for( int i = 0; i < this->getSize(); i++ ) {
	    cout<<"NODE_"<<i;
		if(this->getNetwork().at(i).getStatus()==1)
		    cout<<" is infected.";
		else if (this->getNetwork().at(i).getStatus()==0)
		    cout<<" is susceptible.";
		else 
		    cout<<", it's crazy!";
		cout<<endl;
	    this->getNetwork().at(i).printNeighbors(); 
	}
}

template<class node>
void NetworkSIS<node>::setInitialInfectedDensity(double dInitialDensity) {
    random_device rd;
	double ran_max=double(rd.max());
	for( int i = 0; i < this->getSize(); i++ ) {
		if( double(rd())/ran_max < dInitialDensity )
			this->_vnNetwork.at(i).setStatus(1);
		else
			this->_vnNetwork.at(i).setStatus(0);
	}
}

template<class node>
void NetworkSIS<node>::setInitialProbabilityOfInfection(double dProbabilityOfInfection)
{
	for( int i = 0; i < this->getSize(); i++ ) {
	    this->_vnNetwork.at(i).setInitialProbabilityOfInfection(dProbabilityOfInfection);
	}
}

template<class node>
void NetworkSIS<node>::setProbabilityOfTransmission(double dProbabilityOfTransmission) {
    _dProbabilityOfTransmission=dProbabilityOfTransmission;
}

template<class node>
void NetworkSIS<node>::markovStep()
{
    //Temporal copy of the network to read the data while changing the original
    vector<node> vnNewNetwork;
	vnNewNetwork=this->getNetwork();

    int iSize=this->getSize();

	vector<int> viNeighbors;

	//The density is going to be recalculated then is set to 0
	_dDensity=0;

	double dPONBI;//ProbabilityOfNotBeingInfected
	double dPOI;//ProbabilityOfInfection
	for( int i = 0; i < iSize; i++ ) {//For each node in the network
	    dPONBI=1.0;
	    viNeighbors=vnNewNetwork.at(i).getNeighbors();
		for( vector<int>::iterator it = viNeighbors.begin(); it != viNeighbors.end(); it++ ) {//For each neighbor
			dPOI=vnNewNetwork.at(*it).getProbabilityOfInfection();
		    dPONBI=dPONBI*(1-_dProbabilityOfTransmission*dPOI);
		}
		this->_vnNetwork.at(i).setProbabilityOfNotBeingInfected(dPONBI);
		this->_vnNetwork.at(i).setProbabilityOfInfection();
		_dDensity+=this->_vnNetwork.at(i).getProbabilityOfInfection()/iSize;
	}
}

template <class node>
void NetworkSIS<node>::montecarloStep()
{
    //Temporal copy of the network to read the data while changing the original
    vector<node> vnNewNetwork;
	vnNewNetwork=this->getNetwork();

    int iSize=this->getSize();

	vector<int> viNeighbors;

    random_device rd;
	double ran_max=double(rd.max()),ran;

	//The density is going to be recalculated then is set to 0
	_dDensity=0;

	for( int i = 0; i < iSize; i++ ) {//For each node in the network
	    if( vnNewNetwork.at(i).getStatus() == 0 ){ //If the node is susceptible
			viNeighbors=vnNewNetwork.at(i).getNeighbors();
            //For each neighbor
			for( vector<int>::iterator it = viNeighbors.begin(); it != viNeighbors.end(); it++ ) {
			    if( vnNewNetwork.at(*it).getStatus()==1 &&
				    double(rd())/ran_max < _dProbabilityOfTransmission ) {
				    this->_vnNetwork.at(i).setStatus(1);
					//_dDensity+=1.0/iSize;
					break;
				}
			}
		} /*else {//mu=1
		    this->_vnNetwork.at(i).setStatus(0);
		}*/
	}
	for( int i = 0; i < iSize; i++ ) {//For each node in the network
	    if( vnNewNetwork.at(i).getStatus() == 1 ) {//If it is infected
		    this->_vnNetwork.at(i).setStatus(0);//Recovers with probability mu=1
		}
	}
	

	for( int i = 0; i < iSize; i++ )
		_dDensity+=double(this->_vnNetwork.at(i).getStatus())/iSize;
}

#endif
