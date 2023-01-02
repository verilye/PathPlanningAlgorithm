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
    bool runLoop = true;
    while(runLoop){

    //     select node in the open list with the estimated closest distance that isnt in the closed list
    //     this node is p

        Node node = selectNode();

        if(node.invalid == true){
            runLoop = false;
            break;
        }

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

    // TODO
    // Keep track of shortest distance because later entries will most likely be closer

    // Iterate backwards over array?

    Node* minEstDist;

    for(int i = openList->getLength(); i > 0 ;i--){

        //Check if in closed list
        minEstDist = openList->getNode(i);

        if(!checkClosedList(minEstDist)){
            return *minEstDist;
        };

    }

    Node* invalid = new Node(-1,-1,-1);
    invalid->invalid = true;
    
    return *invalid;

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

        // Check if x and y exists in open list

        for(int i = 0; i< openList->getLength();i++){
            
            if(openList->getNode(i)->getCol() == x && 
                 openList->getNode(i)->getRow() == y)
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