#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathSolver.h"

// My approach:
// As the C++ development process is pretty new to me I took this assignment
// slow made sure to compile often throughout. I tried to follow object oriented
// principles as closely as possible, while still maintaining coherency so that
// I can understand what Im trying to achieve with blocks of code. In some areas
// I could have condesed some verbose and repetitive code, but for ease of personal 
// reference and learning, I kept these areas more segmented and clearly labelled 
// so that I dont get logically lost while trying to understand new concepts.

// For milestone 3, I worked my way back down the visited nodes list reducing
// distance travelled by one every time. After ensuring that the node is 1 less
// distance travelled than the current node I checked that one of the axis was
// the same as the current node and the other axis +1 or -1 difference.
// This ensures that the next node is next to the current node. 

// Issues I ran into:
// I had some trouble with accessing member variables of nodes that were in 
// my open and closed lists and even after thourough troubleshooting dont 
// completely understand why. When trying to implement milestone 4 I also 
// ran into a lot of unexpected behaviour when trying to implement dynamically allocated
// arrays. I found it very frustrating that the course restricted the ways in 
// which I'm allowed to solve these types of problems, being forced to use cin.get()
// and not being allowed to use things not covered in the course was extremely limiting.
// Arbitrary restrictions like this make the obfuscate a solution and teach me little
// about dynamic array allocation, the testing of which was the purpose of the milestone.

// Use the recommended command to compile the file:
// g++ -Wall -Werror -std=c++14 -O -o assign1 Node.cpp NodeList.cpp PathSolver.cpp main.cpp
//
// Then:
//
// ./assign1 <tests/testName.env> output.txt
// to view the results of the test in the output.txt file.

// Helper test functions
void testNode();
void testNodeList();
void testEstDist();

// Read a environment from standard input.
void readEnvStdin(Env env, PathSolver* pathsolver);

// Print out a Environment to standard output with path.
void printEnvStdout(Env env, NodeList* solution);
void printEnv(Env env);


int main(int argc, char** argv){
    

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
    // printEnv(env);
    
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

    Node* start = nullptr;
    Node* goal = nullptr;

    for(int i =0 ; i<ENV_DIM;i++){

        for(int j = 0; j<ENV_DIM;j++){

            char input;

            std::cin >> input;
        
        // Save the start and end markers for later so I
        // know where to start and the estimated distance
            if(input==SYMBOL_START){
                start = new Node(i,j,0);
            }
            if(input==SYMBOL_GOAL){
                goal = new Node(i,j,0);
            }

            env[i][j] = input;
        }
    }

    if(start == nullptr || goal == nullptr){

        std::cout<<"Invalid Map";

        exit(EXIT_FAILURE);

    }

    pathsolver->startingLocation = start;
    pathsolver->goal = goal;

    return;

}

void printEnvStdout(Env env, NodeList* solution) {
    
    // Print edited env with arrows instead of empty places along the rout

    // row +1 or -1, is east and west;
    // col -1 or +1 is north and south;

    char north = '^';
    char south = 'v';
    char east = '>';
    char west = '<';

    for(int i=1; i<solution->getLength()-1;i++){

        Node* robo = new Node(*solution->getNode(i));
        Node* next = new Node(*solution->getNode(i+1));

            if(robo->getCol() < next->getCol()){
                 env[solution->getNode(i)->getRow()][solution->getNode(i)->getCol()] = east;
            }
            if(robo->getCol() > next->getCol()){
                 env[solution->getNode(i)->getRow()][solution->getNode(i)->getCol()] = west;
            }
            if(robo->getRow() > next->getRow()){
                 env[solution->getNode(i)->getRow()][solution->getNode(i)->getCol()] = north;
            }
             if(robo->getRow() < next->getRow()){
                 env[solution->getNode(i)->getRow()][solution->getNode(i)->getCol()] = south;
            }

    }

    printEnv(env);
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

void printEnv(Env env){

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