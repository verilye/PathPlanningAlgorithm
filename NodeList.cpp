#include "NodeList.h"
#include <iostream>

NodeList::NodeList(){

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

Node* NodeList::getNode(int i){

    return this->nodes[i];
    
}