
#include "NodeList.h"
#include <iostream>



NodeList::NodeList() = default;


NodeList::~NodeList(){
   for (size_t i = 0; i < length; ++i) {
       delete nodes[i];
       nodes[i] = nullptr;
   }


}

NodeList:: NodeList(NodeList& other){
    // Deep copy the contents of other.nodes into this->nodes
    NodePtr currOtherNode;
    for (size_t i = 0; i < other.getLength(); ++i) {
        currOtherNode = other.get(i);
        this->addBack(new Node(currOtherNode->getRow(), currOtherNode->getCol(), currOtherNode->getDistanceToS()));
    }
    // No need to copy length as it is incremented by addBack
}


int NodeList::getLength(){
   return length;
}


NodePtr NodeList::get(int i){
   return nodes[i];
}

void NodeList::addBack(NodePtr newNode){
   nodes[length++] = newNode;
}

bool NodeList::containsNode(NodePtr node){
    bool res = false;
    // Based on coordinates, check whether node is present in this->nodes
    NodePtr currNode;
    for (size_t i = 0; i < length; ++i) {
        currNode = this->nodes[i];
        if (currNode->equals(*node)) {
            res = true;
        }
    }
    return res;

}

void NodeList::clear(){
   
}

void NodeList::addAt(int i, NodePtr newNode) {
    nodes[i] = newNode;
    ++length;
}

