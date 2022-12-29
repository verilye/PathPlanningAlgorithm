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

void PathSolver::scanCardinalDirections(Env env, Node node){

    // TODO   
    // check to see if node in closed or open list


    //Scan all 4 cardinal directions for valid spaces to add to the open list

    int x = node.getCol();
    int y = node.getRow(); 

    int north = y-1;
    int south = y+1;
    int east = x+1;
    int west = x-1;

    scanNode(env,node, x, north);
    scanNode(env,node, x, south);
    scanNode(env,node, east, y);
    scanNode(env,node, west, y);


   

}

void PathSolver::scanNode(Env env, Node node, int x, int y){

    // Check both x and y are in bounds

    if(x<0 || x>ENV_DIM){
        return ;
    }

    if(y<0 || y>ENV_DIM){
        return ;
    }

    // Check if symbol is valid

    if(env[x][y] == SYMBOL_EMPTY || env[x][y] == SYMBOL_GOAL){

        // Check if x and y exists in closed list

        for(int i = 0; i< closedList->getLength();i++){
            
            if(closedList->getNode(i)->getCol() == x && 
                 closedList->getNode(i)->getRow() == y)
                {
                    return;
                }
        }

         // Create node, add it to the nodelist

        Node* addedNode = new Node(x,y,node.getDistanceTraveled()+1);

        openList->addElement(addedNode);

        return;

    }

    return ;

}

//-----------------------------