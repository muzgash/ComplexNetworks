#ifndef NETWORKSIN_HPP
#define NETWORKSIN_HPP

#include<Network.hpp>
#include<random>

#include<iostream>

using namespace std;

template<class node>
class NetworkSin : public Network<node>
{
  public:
    NetworkSin();

	void montecarloStep(char cTypeOfSinergy);
	void setInitialInfectedDensity(double dInitialDensity);
	void setElementaryRateOfInfection(double dElementaryRateOfInvfection);
	void setEffectiveStrengthOfSinergy(double dEffectiveStrengthOfSinergy);
	void setTimeOfRecovery(unsigned int uiTimeOfRecovery);

	void printNetwork();

	double getSucceptibleDensity(){return _dSucceptibleDensity;}
	double getInfectedDensity(){return _dInfectedDensity;}
	double getRecoveredDensity(){return _dRecoveredDensity;}

  private:
    double _dSucceptibleDensity;
    double _dInfectedDensity;
    double _dRecoveredDensity;
	double _dElementaryRateOfInfection; //alpha
	double _dEffectiveStrengthOfSinergy; //beta
	unsigned int _uiTimeOfRecovery;
};




template<class node>
NetworkSin<node>::NetworkSin()
{
}

template<class node>
void NetworkSin<node>::printNetwork()
{
    for( int i = 0; i < this->getSize(); i++ ) {
	    cout<<"NODE_"<<i;
		if(this->getNetwork().at(i).getStatus()==1)
		    cout<<" is infected.";
		else if (this->getNetwork().at(i).getStatus()==0)
		    cout<<" is susceptible.";
		else 
		    cout<<", it's super effective!";
		cout<<endl;
	    this->getNetwork().at(i).printNeighbors(); 
	}
}

template<class node>
void NetworkSin<node>::setInitialInfectedDensity(double dInitialDensity) {
    random_device rd;
	double ran_max=double(rd.max());
	for( int i = 0; i < this->getSize(); i++ ) {
		if( double(rd())/ran_max < dInitialDensity ) {
			this->_vnNetwork.at(i).setStatus(1);
			this->_vnNetwork.at(i).setElapsedInfectedTime(rd()%_uiTimeOfRecovery);
		}
		else {
			this->_vnNetwork.at(i).setStatus(0);
			this->_vnNetwork.at(i).setElapsedInfectedTime(0);
		}
	}
}

template<class node>
void NetworkSin<node>::setElementaryRateOfInfection(double dElementaryRateOfInfection) {
    _dElementaryRateOfInfection=dElementaryRateOfInfection;
}

template<class node>
void NetworkSin<node>::setEffectiveStrengthOfSinergy(double dEffectiveStrengthOfSinergy) {
    _dEffectiveStrengthOfSinergy = dEffectiveStrengthOfSinergy;
}

template<class node>
void NetworkSin<node>::setTimeOfRecovery(unsigned int uiTimeOfRecovery) {
    _uiTimeOfRecovery=uiTimeOfRecovery;
}

template <class node>
void NetworkSin<node>::montecarloStep(char cTypeOfSinergy)
{
    //Temporal copy of the network to read the data while changing the original
    vector<node> vnNewNetwork;
	vnNewNetwork=this->getNetwork();
	int salida;

    int iSize=this->getSize();

	vector<int> viNeighbors;

    random_device rd;
	double ran_max=double(rd.max()),ran;

	//The density is going to be recalculated then is set to 0
	_dSucceptibleDensity=0;
	_dInfectedDensity=0;
	_dRecoveredDensity=0;

    //Checks times of the nodes and recovers them
	for( int i = 0; i < iSize; i++ ) {//For each node in the network
	    if( vnNewNetwork.at(i).getStatus()==1 ) {
		    if( vnNewNetwork.at(i).getElapsedInfectedTime()>=_uiTimeOfRecovery )
		        this->_vnNetwork.at(i).setStatus(2);
			else {
			    int t = this->_vnNetwork.at(i).getElapsedInfectedTime();
			    this->_vnNetwork.at(i).setElapsedInfectedTime(t+1);
			}
		}
    }

    //Calculates the degree of sinergy
	switch(cTypeOfSinergy){
	  case 'r':
		for( int i = 0; i < iSize; i++ ) {//For each node in the network
			if( vnNewNetwork.at(i).getStatus() == 0 ){ //If the node is susceptible
				viNeighbors=vnNewNetwork.at(i).getNeighbors();
				double dStrengthOfSinergy=-1*_dEffectiveStrengthOfSinergy;
				//For each neighbor
				for( vector<int>::iterator it = viNeighbors.begin(); it != viNeighbors.end(); it++ ) {
				    if( vnNewNetwork.at(*it).getStatus() == 1 ) {
					    dStrengthOfSinergy+=_dEffectiveStrengthOfSinergy;
					}
					
				}
				double dTransmissionRate=_dElementaryRateOfInfection+dStrengthOfSinergy;
				if( dTransmissionRate > 0 && double(rd())/ran_max < dTransmissionRate ) {
				    this->_vnNetwork.at(i).setStatus(1);
				    this->_vnNetwork.at(i).setElapsedInfectedTime(0);
				}
             }
		}
		break;
	  case 'd':
		for( int i = 0; i < iSize; i++ ) {//For each node in the network
			if( vnNewNetwork.at(i).getStatus() == 1 ){ //If the node is infected
				viNeighbors=vnNewNetwork.at(i).getNeighbors();
				double dStrengthOfSinergy=0;
				//For each neighbor we get the infected and calculate the strength of sinergy
				for( vector<int>::iterator it = viNeighbors.begin(); it != viNeighbors.end(); it++ ) {
				    if( vnNewNetwork.at(*it).getStatus() == 1 ) {
					    dStrengthOfSinergy+=_dEffectiveStrengthOfSinergy;
					}
				}
				double dTransmissionRate=_dElementaryRateOfInfection+dStrengthOfSinergy;
				for( vector<int>::iterator it = viNeighbors.begin(); it != viNeighbors.end(); it++ ) {
				    if( vnNewNetwork.at(*it).getStatus() == 0 ) {
				        if( dTransmissionRate > 0 && double(rd())/ran_max < dTransmissionRate ) {
				            this->_vnNetwork.at(*it).setStatus(1);
				            this->_vnNetwork.at(*it).setElapsedInfectedTime(0);
				        }
				    }
                }
		    }
		}
	    break;
	  default:
	    cout<<"Error during sinergy"<<endl;
	    break;
	}
	/*cout<<endl<<"The new infected nodes are: "<<endl;
	for( int i = 0; i < iSize; i++ ) {//For each node in the network
	    if( this->_vnNetwork.at(i).getStatus() == 1 ) {//If it is infected
		    cout<<i<<" ";
		    //this->_vnNetwork.at(i).setStatus(0);//Recovers with probability mu=1
		}
	}
	cout<<endl;*/

	for( int i = 0; i < iSize; i++ ) {
		if(this->_vnNetwork.at(i).getStatus()==0)
		    _dSucceptibleDensity+=1.0/iSize;
		if(this->_vnNetwork.at(i).getStatus()==1)
		    _dInfectedDensity+=1.0/iSize;
		if(this->_vnNetwork.at(i).getStatus()==2)
		    _dRecoveredDensity+=1.0/iSize;
	}
}

#endif
