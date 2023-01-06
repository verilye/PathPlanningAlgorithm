#include "NodeList.h"
#include <iostream>

NodeList::NodeList(){

    this->length=0;
    nodes = new Node*[length];

    
}

NodeList::~NodeList(){
    for(int i = 0; i < length; i++) {
        delete nodes[i];
    }
    delete [] nodes;
}

NodeList::NodeList(NodeList& other){
    
    
    for(int i = 0; i< other.getLength();i++){

        addElement(new Node(*other.getNode(i)));

    }

    this->length = other.getLength();

}

int NodeList::getLength(){
    
    return this->length;
}

void NodeList::setLength(int l){

    this->length = l;
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

void NodeList::addAtIndex(Node* node, int index){
    
    this->nodes[index] = node;
    this->length = this->length + 1;

}