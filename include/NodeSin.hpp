#ifndef NODESIN_HPP
#define NODESIN_HPP

#include<Node.hpp>

class NodeSin: public Node
{
  public:
    NodeSin(int iIndex);

	int getStatus(){return _iStatus;}
	void setStatus(int iStatus){_iStatus=iStatus;}

	void setDegreeOfSinergy(char cType);
	void setElapsedInfectedTime(unsigned int uiElapsedInfectedTime);
	unsigned int getElapsedInfectedTime(){ return _uiElapsedInfectedTime;};

  private:
    unsigned int _iStatus;//0 for recovered 1 for succeptible 2 for infected
	unsigned int _uiElapsedInfectedTime;
	double _dDegreeOfSinergy;
};


#endif
