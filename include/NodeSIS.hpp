#ifndef NODESIS_HPP
#define NODESIS_HPP

#include<Node.hpp>

class NodeSIS: public Node
{
  public:
    NodeSIS(int iIndex);

	int getStatus(){return _iStatus;}
	double getProbabilityOfInfection(){return _dProbabilityOfInfection;}
	double getProbabilityOfNotBeingInfected(){return _dProbabilityOfNotBeingInfected;}

	void setStatus(int iStatus){_iStatus=iStatus;}
	void setProbabilityOfInfection();
	void setProbabilityOfNotBeingInfected(double dProbabilityOfNotBeingInfected);
	void setInitialProbabilityOfInfection(double dProbabilityOfInfection);

  private:
    int _iStatus;//0 for susceptible 1 for infected
	double _dProbabilityOfInfection;
	double _dProbabilityOfNotBeingInfected;
};


#endif
