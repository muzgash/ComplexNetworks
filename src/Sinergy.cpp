#include<Node.hpp>
#include<Network.hpp>

using namespace std;

int main(int argc, char **argv)
{
    Network <Node> ba;
	ba.setSize(6);
	ba.setAverageDegree(4);
	//ba.setRing();
	//ba.setBarabasiAlbert(3,2);
	//ba.setWattsStrogatz(0.4);
	ba.printNetwork();
    return 0;
}

