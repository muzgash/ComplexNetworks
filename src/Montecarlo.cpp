#include<NodeSin.hpp>
#include<NetworkSin.hpp>
#include<fstream>
#include<sstream>

using namespace std;

int main(int argc, char **argv){
    int iCpuNumber, iCpuActual;
	iCpuNumber=atoi(argv[1]);
	iCpuActual=atoi(argv[2]);

	double density[100],average;
    ofstream montecarlo;
	stringstream filename;

    //Variables for pbs
    double dPart,dBetaMin,dBetaMax;
    dPart=1.0/iCpuNumber;
	dBetaMin=iCpuActual*dPart;
	dBetaMax=dBetaMin+dPart;

	double dBeta=1.0, dAlpha=1.;
	unsigned int uiRecoveryTime=2;

	NetworkSin <NodeSin> ba;
	ba.setSize(4);
	ba.setAverageDegree(2);
	ba.setBarabasiAlbert(5000,4);
	ba.setInitialInfectedDensity(0.05);
	ba.setElementaryRateOfInfection(dAlpha);
	ba.setEffectiveStrengthOfSinergy(dBeta);
	ba.setTimeOfRecovery(uiRecoveryTime);
    /*for(int time=0; time<20; time++) {
		cout<<"TIME "<<time<<endl;
		average=0;
		for(int d=0; d<100; d++) {
			ba.montecarloStep('r');
			density[d]=ba.getDensity();
			average+=density[d]/100.0;
		}
		if(average-density[99] < 0.0001) {
			montecarlo<<beta<<" "<<average<<endl;
			break;
		}
	}*/
		
	filename<<"r-montecarlo_a"<<dAlpha<<"_b"<<dBeta<<"_rt"<<uiRecoveryTime<<".dat";
    montecarlo.open(filename.str().c_str());
	for(int time=0; time<25; time++) {
		ba.montecarloStep('r');
		montecarlo<<time<<" "<<ba.getSucceptibleDensity()
		        <<" "<<ba.getInfectedDensity()
				<<" "<<ba.getRecoveredDensity()<<endl;
	}
    montecarlo.close();
	filename.str("");
	filename<<"d-montecarlo_a"<<dAlpha<<"_b"<<dBeta<<"_rt"<<uiRecoveryTime<<".dat";
    montecarlo.open(filename.str().c_str());
	ba.setInitialInfectedDensity(0.05);
	for(int time=0; time<70; time++) {
		ba.montecarloStep('d');
		montecarlo<<time<<" "<<ba.getSucceptibleDensity()
		        <<" "<<ba.getInfectedDensity()
				<<" "<<ba.getRecoveredDensity()<<endl;
	}
		
    montecarlo.close();
    return 0;
}
