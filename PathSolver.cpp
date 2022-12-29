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
    // Closed - One which stores invalid positions with distances from start
    
    //OPEN LIST starts with the starting node (S) , add it to the array
    
    openList->addElement(this->startingLocation);

    // repeat

    //      Check for valid nodes to add to the open list
    //      select node in the open list with the estimated closest distance
    //      this node is p

    //      add each node that p can reach to the open list 
    //          if not already there
    //          add 1 distance travelled

    //      add p to closed list (the closed list is full of valid travel nodes)

    // either the Goal will be reach or all connected open spaces will be added to the closed list

}

NodeList* PathSolver::getNodesExplored(){
    //TODO
}

NodeList* PathSolver::getPath(Env env){
    // TODO
}

void PathSolver::nodeScanner(Env env, Node node){

    // TODO separate cardinal directions into struct
    //Scan all 4 cardinal directions for valid spaces to add to the open list

    int x = node.getCol();
    int y = node.getRow();

    // Potentially map x, y modifiers to cardinal directions
    // This could support diagonals in the future as well as
    // cardinal directions

    if((x-1) >= 0 ){
        if(env[x-1][y] == SYMBOL_EMPTY || env[x-1][y] == SYMBOL_GOAL){

            // Create node, add it to the nodelist

            Node* addedNode = new Node(x-1,y,node.getDistanceTraveled()+1);
        
            openList->addElement(addedNode);
        }
    }

    if((x+1) <= ENV_DIM ){
       
        if( env[x+1][y] == SYMBOL_EMPTY ||  env[x+1][y] == SYMBOL_GOAL){

            // Create node, add it to the nodelist

            Node* addedNode = new Node(x+1,y,node.getDistanceTraveled()+1);
        
            openList->addElement(addedNode);
        }
    }
    if((y-1) >= 0 ){
       
        if( env[x][y-1] == SYMBOL_EMPTY ||  env[x][y-1] == SYMBOL_GOAL){

            // Create node, add it to the nodelist

            Node* addedNode = new Node(x,y-1,node.getDistanceTraveled()+1);
        
            openList->addElement(addedNode);
        } 
    }
    if( (y+1) <= ENV_DIM ){
        
        if(env[x][y+1] == SYMBOL_EMPTY || env[x][y+1] == SYMBOL_GOAL){

            // Create node, add it to the nodelist

            Node* addedNode = new Node(x,y+1,node.getDistanceTraveled()+1);
            openList->addElement(addedNode);
        } 
    }

}

//-----------------------------