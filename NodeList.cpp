
#include "NodeList.h"
#include <iostream>
#include <sstream>

NodeList::NodeList() {}

NodeList::NodeList(int max_length): length(0), max_length(max_length) {
    nodes = new Node*[max_length];
}

NodeList::~NodeList() {
    clear();
}

NodeList:: NodeList(NodeList& other): length(0),
                                      max_length(other.getMaxLength()) {
    nodes = new Node*[max_length];
    // Deep copy the contents of other.nodes into this->nodes
    NodePtr currOtherNode;
    for (size_t i = 0; i < other.getLength(); ++i) {
        currOtherNode = other.get(i);
        addBack(new Node(*currOtherNode));
    }
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
    NodePtr currNode = nullptr;
    for (size_t i = 0; i < length; ++i) {
        currNode = this->nodes[i];
        if (currNode->equals(*node)) {
            res = true;
        }
    }
    return res;
}

void NodeList::clear(){
    // Delete each Node
    for (size_t i = 0; i < length; ++i) {
        delete nodes[i];
        nodes[i] = nullptr;
    }
    length = 0;
    // Delete nodes
    delete[] nodes;
    nodes = nullptr;
}

/*
 * For Milestone 3, rather than adding Nodes from nodes[0] to nodes[x]
 * where x is 'G's distance from 'S' and sorting it in reverse order,
 * straight from the beginning add goalNode at the rightmost index
 * and subsequent nodes to the left until startNode is added at nodes[0]
 */
void NodeList::addPathNode(NodePtr newNode) {
    nodes[newNode->getDistanceToS()] = newNode;
    ++length;
}

/*
 * Return a string in the format below
 * 0: (x1,y1,d1)
 * 1: (x2,y2,d2)
 * 2: (x3,y3,d3)
 *        .
 *        .
 * i - 1: (xi, yi, di)
 *
 * where i is the length of the list, x the row, y the column, d the distance.
 */
std::string NodeList::stringify() {
    std::ostringstream os;
    std::string res = "";

    int x, y, dis;
    for (int i = 0; i < this->getLength(); ++i) {
        x = this->get(i)->getCol();
        y = this->get(i)->getRow();
        dis = this->get(i)->getDistanceToS();

        os << i << ": (" << x << "," << y << "," << dis << ")\n";
    }
    res = os.str();
    return res;
}

/*
 * For Milestone 4, getMaxLength method is needed
 */
int NodeList::getMaxLength() {
    return max_length;
}

/*
 * While the function above containsNode checks whether NodeList contains
 * a node at the given row and column, getTheSameNode returns
 * nullptr if no such node is not found; a pointer to the node if found.
 */
NodePtr NodeList::getTheSameNode(NodePtr node) {
    // Based on coordinates, check whether node is present in this->nodes
    NodePtr currNode = nullptr;
    NodePtr returnNode = nullptr;
    for (size_t i = 0; i < length; ++i) {
        currNode = this->nodes[i];
        if (currNode->equals(*node)) {
            returnNode = currNode;
        }
    }
    return returnNode;
}
