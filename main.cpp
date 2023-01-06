#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <queue>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathSolver.h"


// Helper test functions
void testNode();
void testNodeList();
void testEstDist();

// Read a environment from standard input.
Env readEnvStdin(PathSolver* pathsolver);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printEnvStdout(Env env, NodeList* solution);
void printEnv(Env env);

Env make_env(const int rows, const int cols);
void delete_env(Env env, int rows, int cols);

int ROWS = 0;
int COLUMNS = 0;

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


    // Pass starting node to Pathsolver and read in ENV
    PathSolver* pathSolver = new PathSolver();
    Env env = readEnvStdin(pathSolver);
    printEnv(env);
    // std::cout<< std::endl<<" ------- "<<std::endl;
    
    // // Solve using forwardSearch
    // // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
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

Env readEnvStdin(PathSolver* pathsolver){

    Node* start = nullptr;
    Node* goal = nullptr;

    char c = 'a';
    int COLUMNS = 0, ROWS = 0;
    bool firstLine = true;
    std::queue<char> firstChars;
    // Read input to determine env dimensions, push each character to a queue
    while (!std::cin.eof()) {
        std::cin.get(c);
        if(c == '\n') {
            ROWS++;
            firstLine = false;
        } else {
            firstChars.push(c);
        }
        if(firstLine) {
            COLUMNS++;
        }
    }  
    
    ROWS++;
    
    Env env = make_env(ROWS, COLUMNS);
    // Assign each character in queue to appropriate position within env
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLUMNS; col++) {
            c = firstChars.front();
            firstChars.pop();
            env[row][col] = c;
            // We assign our start and goal positions to nodes
            if(c == SYMBOL_START) {
                 start= new Node(row, col, 0);
            } else if (c == SYMBOL_GOAL) {
                 goal = new Node(row, col, 0);
            }
        }
    }

    if(start==nullptr ||goal == nullptr){

        exit(EXIT_FAILURE);
        
    }

    pathsolver->startingLocation = start;
    pathsolver->goal = goal;

    return env;

}

void printEnvStdout(Env env, NodeList* solution) {
    
    // TODO
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


/*
 * This function is to help you dynamically allocate
 *  memory for a generic 2D Environemnt.
 */
Env make_env(const int rows, const int cols) {
   Env env = nullptr;

   if (rows >= 0 && cols >= 0) {
      env = new char*[rows];
      for (int i = 0; i != rows; ++i) {
         env[i] = new char[cols];
      }
   }

   return env;
}

/*
 * This function is to help you delete a 
 * dynamically allocated 2D Environment.
 */

void delete_env(Env env, int rows, int cols) {
   if (rows >= 0 && cols >= 0) {
      for (int i = 0; i != rows; ++i) {
         delete env[i];
      }
      delete env;
   }

   return;
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

     for(int i =0 ; i<ROWS;i++){

        for(int j =0; j<COLUMNS;j++){

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