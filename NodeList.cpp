#include "NodeList.h"
#include <iostream>

NodeList::NodeList(){

    this->length=0;
    
}

NodeList::~NodeList(){

    std::cout<<"NodeList deleted!"<<std::endl;

}

NodeList::NodeList(NodeList& other){
    // TODO
}

int NodeList::getLength(){
    
    return this->length;
}

void NodeList::addElement(Node* newPos){
    
    this->nodes[this->length] = newPos;
    this->length = this->length + 1;

}

bool NodeList::checkForNode(Node* node){

    for(int i = 0; i< this->getLength();i++){
        
        if(this->getNode(i)->getCol() == node->getCol() && 
                this->getNode(i)->getRow() == node->getRow())
            {
                return true;
            }
    }

    return false;

}

Node* NodeList::getNode(int i){

    return this->nodes[i];
    
}