#include "Node.h"
#include <iostream>


Node::Node(int row, int col, int dist_traveled)
{
    this->row = row;
    this->col = col;
    this->dist_traveled = dist_traveled;
    this->invalid = false;
}

Node::~Node(){

}

Node::Node(Node &n){

    row=n.getRow();
    col=n.getCol();
    this->setDistanceTraveled(n.getDistanceTraveled());
    this->invalid = n.invalid; 


};

int Node::getRow(){
    
    return this->row;

}

int Node::getCol(){
    return this->col;
}

int Node::getDistanceTraveled(){
    return this->dist_traveled;
}

void Node::setDistanceTraveled(int dist_traveled)
{
    this->dist_traveled = dist_traveled;
}

int Node::getEstimatedDist2Goal(Node* goal){
    // Here is where I should put the estimated distance to goal
    // using estimated closest difference == 
    // distance_travelled of selected node p + Manhattan distance from p to Goal


    //Manhattan distance = where p(1) is at location x(1),y(1) => dist traveled of p + (x(1) - x(2)) + (y(1) - y(2))

    // x(1), y(1) = this->getColumn, this->getRow

    // x(2), y(2) = goal->getColumn, goal->getRow

    // therefore

    int manhattanDistance = (this->getCol() - goal->getCol()) + (this->getRow()- goal->getRow());

    int estimatedDistance = this->dist_traveled + manhattanDistance;

    if(estimatedDistance<0){
        estimatedDistance=-estimatedDistance;
    }

    return estimatedDistance;

}
    
//--------------------------------                             