#ifndef DEGREE_H
#define DEGREE_H

#include<cstdlib>
#include<vector>

using namespace std;


//Correct implementation of the modulo function
/*! \brief Right Implementation of the module function
 *
 *  \param int iNumberA 
 *  \param int iNumberB
 *
 *  The function is improved to calculate correctly the module function for negative numbers
 *  since mod(a,b) is defined strictly positive.
 *
 *  \returns mod(a,b)
*/
int mod(int iNumberA, int iNumberB);





/*! \brief checks if a value is already in a vector
 *
 *  \param std::vector<int> ivVertex 
 *  \param int iNumber
 *
 *  Actually is made to check if a node is already listed in a adjacency list of another node
 *
 *  \returns iNumber if the number is found, or -1 if not. 
*/
int isIn(vector<int> ivVertex, int iNumber);




/*! \brief Calculates the average clustering coefficient of a given network
 *
 *  \param std::vector<std::vector<int>> ivvNetwork 
 *
 *  \returns int: The average clustering coefficient
*/
double averageClusteringCoefficient( vector< vector<int> > ivvNetwork );




/*! \brief calculates the average degree of a given network
 *
 *  \param std::vector<std::vector<int>> ivvNetwork 
 *
 *  Sums the degrees over the nodes of the network and divides by the total number of nodes.
 *
 *  \returns The average degree
*/
double averageDegree( vector< vector<int> > ivvNetwork );



int* BFS( vector< vector<int> >ivvNetwork, int iVertex);




/*! \brief Calculates the average shotest path length of a given network
 *
 *  \param std::vector<std::vector<int>> ivvNetwork 
 *
 *  Sums over the shortests paths and divides by its total
 *
 *  \returns The average shortest path length
*/
double averageShortestPathLength( vector< vector<int> > ivvNetwork );


#endif
