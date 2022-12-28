#include "PathSolver.h"
#include <iostream>

PathSolver::PathSolver(){

}

PathSolver::~PathSolver(){

}

void PathSolver::forwardSearch(Env env){
    
    // Forward Search Algorithm
    // To visualise how this algorithm works, imagine water flooding in from 
    // the entry point with a bias that pulls it toward the probable correct
    // route that finds the Goal

    // Store 2 lists:
    // Open - One which stores valid positions with distances from start

    NodeList* open = new NodeList[ENV_DIM*ENV_DIM];

    //OPEN LIST starts with the starting node (S) , add it to the array
    //TODO
    //Add a helper function to find S
    // open->addElement(S);

    // Closed - One which stores invalid positions with distances from start

    NodeList* closed = new NodeList[ENV_DIM*ENV_DIM];


    // repeat
    //      select node in the open list with the estimated closest distance
    //      this node is p
    //      estimated closest difference == distance_travelled of selected node p + Manhattan distance from p to Goal
    //      add each node that the closest node can reach to the open list 
    //          if not already there
    //          add 1 distance travelled             
    //      add p to closed list

    // either the Goal will be reach or all connected open spaces will be added to the closed list

}

NodeList* PathSolver::getNodesExplored(){
    //TODO
}

NodeList* PathSolver::getPath(Env env){
    // TODO
}

//-----------------------------