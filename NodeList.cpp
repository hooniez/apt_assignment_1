
#include "NodeList.h"
#include <iostream>
#include <sstream>


NodeList::NodeList() {

}


NodeList::~NodeList() {
    for (size_t i = 0; i < length; ++i) {
        delete nodes[i];
        nodes[i] = nullptr;
    }
    length = 0;
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

void NodeList::addPathNode(NodePtr newNode) {
    nodes[newNode->getDistanceToS()] = newNode;
    ++length;
}

std::string NodeList::stringify() {
    std::ostringstream os;
    std::string res;

    int x, y, dis;
    for (int i = 0; i < this->getLength(); ++i) {
        x = this->get(i)->getCol();
        y = this->get(i)->getRow();
        dis = this->get(i)->getDistanceToS();

        os << "(" << x << "," << y << "," << dis << ")\n";
    }
    res = os.str();
    return res;
}

