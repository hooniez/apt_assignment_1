
#include "Node.h"

Node::Node() = default;

Node::Node(int row, int col, int distanceToS): row(row), col(col), distanceToS(distanceToS) {}
    
Node::~Node() {
   //TODO
}

int Node::getRow() {
   return row;
}

void Node::setRow(int row) {
    this->row = row;
}

int Node::getCol() {
   return col;
}

void Node::setCol(int col) {
    this->col = col;
}

int Node::getDistanceToS() {
   return distanceToS;
}

void Node::setDistanceToS(int distanceToS) {
    this->distanceToS = distanceToS;
}

bool Node::equals(Node &other) {
    bool isEqual = false;
    if ((this->getRow() == other.getRow()) && (this->getCol() == other.getCol()))
        isEqual = true;
    return isEqual;

}

/* Make sure these conditions meet for the next node to be eligible to be added to pathList.
 * (1. The next node's row differs by 1 from pointerNode's row
 * EXCLUSIVE OR
 * 2. The next node's column differs by 1 from pointerNode's column)
 * AND
 * 3. The next node's distance should be smaller by 1.
 */
bool Node::isPathable(Node &other) {

}