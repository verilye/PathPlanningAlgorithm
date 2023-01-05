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

    NodeList* nodelist = getPath(env);

    // TEST that the lists are filled with correct inputs
    // std::cout<<std::endl<<"------"<<std::endl;
    // std::cout<< "Open List: ";
    // for(int i = 0; i<openList->getLength();i++){
    //     std::cout<< "("<< openList->getNode(i)->getCol() <<","<< openList->getNode(i)->getRow() <<")";
    // }
    // std::cout<<std::endl<<"------"<<std::endl;
    // std::cout<< "Closed List: ";
    // for(int i = 0; i<closedList->getLength();i++){
    //     // std::cout<< "("<< closedList->getNode(i)->getCol() <<","<< closedList->getNode(i)->getRow() <<")";
    //     std::cout<< closedList->getNode(i)->getDistanceTraveled() << ", ";
    // }
    // std::cout<<std::endl<<"------"<<std::endl;
    

}

NodeList* PathSolver::getNodesExplored(){
    
    NodeList* deepCopy = new NodeList(*closedList);

    return deepCopy;

}

NodeList* PathSolver::getPath(Env env){

    NodeList* nodesExplored = getNodesExplored();
    Node* reverseRobo = nodesExplored->getNode(nodesExplored->getLength());
    NodeList* path = new NodeList;

    // Start from the goal node in the list nodesExplored. This would be your final element of the path.
    
    int distance = goal->getDistanceTraveled();

    path->addAtIndex(reverseRobo, distance);

    // Then search for the the four neighbours of the goal node in nodesExplored.     
    // check if they are -1 distance travelled, 
    // then check all nodes that have either the same col or row
    // then check that the other axis is + or - 1 

    std::cout<<"BIG CHUNGUS"<<std::endl;

    for(int i = 0; i< goal->getDistanceTraveled(); i++){

        Node* options[goal->getDistanceTraveled()];

        int counter = 0;

        for(int j =0;j<nodesExplored->getLength();j++){
            
            if(nodesExplored->getNode(j)->getDistanceTraveled() == distance - 1){
                if(nodesExplored->getNode(j)->getCol() == reverseRobo->getCol() || 
                    nodesExplored->getNode(j)->getRow() == reverseRobo->getRow()){
                    if(nodesExplored->getNode(j)->getCol() == reverseRobo->getCol() + 1|| 
                      nodesExplored->getNode(j)->getRow() == reverseRobo->getRow() + 1||
                      nodesExplored->getNode(j)->getCol() == reverseRobo->getCol() -1|| 
                      nodesExplored->getNode(j)->getRow() == reverseRobo->getRow()-1){

                            path->addAtIndex(nodesExplored->getNode(j), distance);
                            reverseRobo = nodesExplored->getNode(j);
                            distance --;

                        }
                }
            }
        }

    }


    

    std::cout<< "Path List: ";
    for(int i = 0; i<path->getLength();i++){
        // std::cout<< "("<< path->getNode(i)->getCol() <<","<< path->getNode(i)->getRow() <<")";
        std::cout<< path->getNode(i)->getDistanceTraveled() << ", ";
    }
    std::cout<<std::endl<<"------"<<std::endl;
    

    return path;

    // return an edited ENV with arrows pointing from the beginning to the end

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