#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathSolver.h"

// Helper test functions
void testNode();
void testNodeList();
void testEnv(Env env);
void testEstDist();

// Read a environment from standard input.
void readEnvStdin(Env env, PathSolver* pathsolver);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printEnvStdout(Env env, NodeList* solution);


int main(int argc, char** argv){
    // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    // AS YOU GO ALONG.
    // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
    // std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    // testNode();
    // testNodeList();
    // testEstDist();
    // std::cout << "DONE TESTING" << std::endl << std::endl;

    // Load Environment and get start node
    Env env;

    // Pass starting node to Pathsolver and read in ENV
    PathSolver* pathSolver = new PathSolver();
    readEnvStdin(env, pathSolver);
    // testEnv(env);

    std::cout<< std::endl<<" ------- "<<std::endl;
    
    // Solve using forwardSearch
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
    pathSolver->forwardSearch(env);

    NodeList* exploredPositions = nullptr;
    exploredPositions = pathSolver->getNodesExplored();

    // Get the path
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
    NodeList* solution = pathSolver->getPath(env);

    printEnvStdout(env, solution);

    delete pathSolver;
    delete exploredPositions;
    delete solution;

}

void readEnvStdin(Env env, PathSolver* pathsolver){

    Node* start;
    Node* goal;

    for(int i =0 ; i<ENV_DIM;i++){

        for(int j = 0; j<ENV_DIM;j++){

            char input;

            std::cin >> input;

            if(input==SYMBOL_START){
                start = new Node(i,j,0);
            }
            if(input==SYMBOL_GOAL){
                goal = new Node(i,j,0);
            }

            env[i][j] = input;
        }
    }

    pathsolver->startingLocation = start;
    pathsolver->goal = goal;

    return;

}

void printEnvStdout(Env env, NodeList* solution) {
    
    // TODO
    // Print edited env with arrows instead of empty places along the rout

    // row +1 or -1, is east and west;
    // col -1 or +1 is north and sout;

    char north = '^';
    char south = 'v';
    char east = '>';
    char west = '<';





}

void testNode() {
    std::cout << "TESTING Node" << std::endl;

    // Make a Node and print out the contents
    Node* node = new Node(1, 1, 2);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;

    // Change Node and print again
    node = new Node(4, 2, 3);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;
}

void testNodeList() {
    std::cout << "TESTING NodeList" << std::endl;

    // Make a simple NodeList, should be empty size
    NodeList* nodeList = new NodeList();
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add a Node to the NodeList, print size
    Node* b1 = new Node(1, 1, 1);
    nodeList->addElement(b1);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add second Nodetest
    Node* b2 = new Node(0, 0, 1);
    nodeList->addElement(b2);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Test Get-ith - should be 0,0,1
    Node* getB = nodeList->getNode(1);
    std::cout << getB->getRow() << ",";
    std::cout << getB->getCol() << ",";
    std::cout << getB->getDistanceTraveled() << std::endl;

    // Print out the NodeList
    std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO" << std::endl;
}

void testEnv(Env env){

     for(int i =0 ; i<20;i++){

        for(int j =0; j<20;j++){

            std::cout<< env[i][j];

        }
        
        std::cout<<std::endl;

    }
}

void testEstDist(){

    Node* p = new Node(1,1,0);

    Node* goal = new Node(5,5,0);

    std::cout<< p->getEstimatedDist2Goal(goal)<<std::endl;

    return; 


}