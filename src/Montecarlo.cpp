#include<NodeSIS.hpp>
#include<NetworkSIS.hpp>

int main(int argc, char **argv){
    int iCpuNumber, iCpuActual;
	iCpuNumber=atoi(argv[1]);
	iCpuActual=atoi(argv[2]);

	double density[3],average;

    //Variables for pbs
    double dPart,dBetaMin,dBetaMax;
    dPart=1.0/iCpuNumber;
	dBetaMin=iCpuActual*dPart;
	dBetaMax=dBetaMin+dPart;


	for(double beta = dBetaMin; beta < dBetaMax; beta+=0.001){
		NetworkSIS <NodeSIS> ba;
		ba.setSize(4);
		ba.setAverageDegree(2);
		ba.setBarabasiAlbert(200,4);
	    ba.setProbabilityOfTransmission(beta);
		ba.setInitialInfectedDensity(0.05);
		//ba.printNetwork();
		for(int time=0; time<50; time++) {
			average=0;
			for(int d=0; d<3; d++) {
				density[d]=ba.getDensity();
				ba.montecarloStep();
				average+=density[d]/3.0;
			}
			if(average-density[2] < 0.0001) {
				cout<<beta<<" "<<density[2]<<endl;
				break;
			}
		}
		
	}
    return 0;
}
