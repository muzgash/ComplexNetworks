#include<NodeSIS.hpp>

NodeSIS::NodeSIS(int iIndex):Node(iIndex)
{
}

void NodeSIS::setInitialProbabilityOfInfection(double dProbabilityOfInfection)
{
    _dProbabilityOfInfection=dProbabilityOfInfection;
}
void NodeSIS::setProbabilityOfInfection()
{
    double q=_dProbabilityOfNotBeingInfected;
	double p=_dProbabilityOfInfection;
    _dProbabilityOfInfection=1-q;//mu=1
}

void NodeSIS::setProbabilityOfNotBeingInfected(double dProbabilityOfNotBeingInfected)
{
    _dProbabilityOfNotBeingInfected=dProbabilityOfNotBeingInfected;
}
