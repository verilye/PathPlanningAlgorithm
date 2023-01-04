#include "PathSolver.h"
#include <iostream>


PathSolver::PathSolver(){

}

PathSolver::~PathSolver(){

    
}

void PathSolver::forwardSearch(Env env){

    // TODO
    // Nodes explored will be a member variable that stores all variables that
    // pass through the selectNode() method
    // This will be the foundation of the backtracking algo in getPath();
    
    // Forward Search Algorithm
    // To visualise how this algorithm works, imagine water flooding in from 
    // the entry point with a bias that pulls it toward the probable correct
    // route that finds the Goal

    // Store 2 lists:
    // Open - One which stores valid positions with distances from start
    // Closed - One which stores invalid positions with distances from start
    
    //OPEN LIST starts with the starting node (S) , add it to the array
    
    openList->addElement(this->startingLocation);

    // std::cout<< "forward search initialised" << std::endl;
    // std::cout<< "Open List: "<< openList->getNode(0)->getCol() << openList->getNode(0)->getRow() << std::endl;
    // std::cout<< "Closed List: "<< closedList->getLength()<< std::endl;
    // std::cout<< openList->getLength() <<std::endl;    

    // repeat
    bool runLoop = true;
    while(runLoop){

    //  select node in the open list with the estimated closest distance that isnt in the closed list
    //  this node is p

    //  the node's invalid property is there for readability 

        Node node = selectNode();

        // std::cout<< "Selected node: "<< node.getCol() <<","<< node.getRow() << std::endl;


    //TODO
    //ADD EXIT CONDITION TO THE ALGORITHM IF SYMBOL_GOAL

        if(node.getRow() == this->goal->getRow() && node.getCol() == this->goal->getCol()){

            runLoop = false;
            closedList->addElement(new Node(node));
            break;

        }

        if(node.invalid == true){
            runLoop = false;
            break;
        }

    //      Check for valid nodes to add to the open list
    //      add each node that p can reach to the open list 
    //          if not already there
    //          add 1 distance travelled
        
        scanCardinalDirections(env, node);

    // std::cout<< "scanned all directions" << std::endl;

        


    //      add p to closed list (the closed list is full of valid travel nodes)

        closedList->addElement(new Node(node));
        
    }

    // TEST that the lists are filled with correct inputs
    // std::cout<<std::endl<<"------"<<std::endl;
    // std::cout<< "Open List: ";
    // for(int i = 0; i<openList->getLength();i++){
    //     std::cout<< "("<< openList->getNode(i)->getCol() <<","<< openList->getNode(i)->getRow() <<")";
    // }
    // std::cout<<std::endl<<"------"<<std::endl;
    // std::cout<< "Closed List: ";
    // for(int i = 0; i<closedList->getLength();i++){
    //     std::cout<< "("<< closedList->getNode(i)->getCol() <<","<< closedList->getNode(i)->getRow() <<")";
    // }
    // std::cout<<std::endl<<"------"<<std::endl;
    // either the Goal will be reach or all connected open spaces will be added to the closed list

}

NodeList* PathSolver::getNodesExplored(){
    //TODO
}

NodeList* PathSolver::getPath(Env env){
    // TODO
    // return an edited ENV with arrows pointing from the beginning to the end

    // backtracking algorithm goes here

    // Start from the goal node in the list nodesExplored. This would be your final element of the path.
    // Then search for the the four neighbours of the goal node in nodesExplored. 
    // If there is a neighbour that has distance_traveled one less than the goal node. 
    // Then that should be the node in the path before the goal node.
    // Repeat this backtracking process for each node you add to the path until you reach the start node.
}

Node PathSolver::selectNode(){

    // Select node with the shortest estmated distance

    Node* node;
    int closestDistance = ENV_DIM * ENV_DIM;
    int closestNode = -1;
    int iterator = openList->getLength();

    for(int i = 0; i<openList->getLength(); i++){

        node = openList->getNode(i);

        //compare to lowest distance

        if(node->getEstimatedDist2Goal(this->goal) < closestDistance && closedList->checkForNode(node) == false){

            //override with new node if not in closed list and lower than closest Distance
            closestNode = i;
            closestDistance = node->getEstimatedDist2Goal(this->goal); 

        }

    }


    if(closestNode == -1){
         Node* invalid = new Node(-1,-1,-1);
        invalid->invalid = true;
    
        return *invalid;
    }else{
        return *openList->getNode(closestNode);

    }
   

};



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

    Node* addedNode = new Node(y,x,node.getDistanceTraveled()+1);


    // Check if symbol is valid

    if(env[y][x] == SYMBOL_EMPTY || env[y][x] == SYMBOL_GOAL){

        // Check if node exists in open and closed lists

        if(openList->checkForNode(addedNode) == true||closedList->checkForNode(addedNode) == true){
            return; 
        };

        // Create node, add it to the openList 

        // ADD A COPY OF THE NODE TO THE CLOSED LIST

        openList->addElement(addedNode);

        return;

    }

    return ;

}

//-----------------------------