
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
 */
bool Node::isPathable(Node &other) {
    bool res = false;
    int rowDiff = this->getRow() - other.getRow();
    int colDiff = this->getCol() - other.getCol();
    if ( ((rowDiff == -1) || (rowDiff == 1)) && (colDiff == 0) )
        res = true;
    else if ( ((colDiff == -1) || (colDiff == 1)) && (rowDiff == 0) )
        res = true;
    return res;
}


Direction Node::getDirectionTo(Node &other) {
    Direction dir = UP;
    int rowDiff = this->getRow() - other.getRow();
    int colDiff = this->getCol() - other.getCol();
    if (rowDiff == -1)
        dir = DOWN;
    else if (rowDiff == 1)
        dir = UP;
    else if (colDiff == 1)
        dir = LEFT;
    else if (colDiff == -1)
        dir = RIGHT;
    return dir;
}