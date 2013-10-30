#ifndef NETWORK_H
#define NETWORK_H

#include <vector>


using namespace std;



/*! \brief Creates a Regular Ring
 *
 *  \param int iSize: Number of nodes.
 *  \param int iAverageDegree: Number of neighbors of each node.
 *
 *  A ring is a network where each numbered node is conected to iAverageDegree
 *  of its numbered neighbors in a click-like way, for example, node 0
 *  is conected to node 1, 2, ..., k/2 and iSize-1, iSize-2, ..., iSize-k/2.
 *
 *  \returns std::vector<std::vector<int>> Avector with the adjacency lists.
*/
vector< vector<int> > ring( int iSize, int iAverageDegree );




/*! \brief Creates a Watts-Strogatz model based network from a ring.
 *
 *  \param int iSize: Number of nodes.
 *  \param int iAverageDegree: Initial number of neighbors of each node.
 *  \param double dProbability: Probability of rewiring an edge.
 *
 *  Creates a ring and rewire its edges with probability dProbability.
 *
 *  \returns A Watts-Strogats model based network.
*/
vector< vector<int> > wattsStrogatzModel(int iSize, int iAverageDegree, double dProbability);




/*! \brief Creates a Barabasi-Albert model based network.
 *
 *  \param std::vector<vector<int>> ivvNetwork: Initial network.
 *  \param int iSteps: Number of new nodes.
 *
 *  Given an initial network ivvNetwork, it creates a single new node each step iStep
 *  and there's a probability of wiring it equal to the node's degree.
 *
 *  \returns A barabasi-Albert model based network.
*/
vector< vector<int> > barabasiAlbertModel( vector< vector<int> > ivvNetwork, int iSteps );

#endif
