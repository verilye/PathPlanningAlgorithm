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
    while(1){

    //     select node in the open list with the estimated closest distance that isnt in the closed list
    //     this node is p

        Node node = selectNode();

    //      Check for valid nodes to add to the open list
    //      add each node that p can reach to the open list 
    //          if not already there
    //          add 1 distance travelled

        scanCardinalDirections(env, node);

    //      add p to closed list (the closed list is full of valid travel nodes)

        closedList->addElement(&node);

    }

    // either the Goal will be reach or all connected open spaces will be added to the closed list

}

NodeList* PathSolver::getNodesExplored(){
    //TODO
}

NodeList* PathSolver::getPath(Env env){
    // TODO
}

Node PathSolver::selectNode(){

    //TODO
    //A exit condition on this method should be that if no valid node
    //is found not in the closed list then there is no valid path


    //Pick smallest estimated difference node in open list

    //TODO
    //Remember the smallest option in the open list
    //Remove the if condition, replace it with a counter that keeps track of the shortest distance
    //return the node that matches up with the counter

    Node* minEstDist;

    for(int i = 0; i < openList->getLength() ;i++){

        //Check if in closed list
        minEstDist = openList->getNode(i);

        // if(!checkClosedList(minEstDist)){
        //     return *minEstDist;
        // };

    }
}

bool PathSolver::checkClosedList(Node* node){

    for(int i = 0; i< closedList->getLength(); i++){

        if(node == closedList->getNode(i)){
            
            return true;

        }
            
    }

    return false;

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


    //TODO
    //ADD EXIT CONDITION TO THE ALGORITHM IF SYMBOL_GOAL

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