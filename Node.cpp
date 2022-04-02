
#include "Node.h"

Node::Node() {}

Node::Node(int row, int col, int dis): row(row), col(col), distanceToS(dis) {}

Node::Node(Node &other): row(other.getRow()),
                         col(other.getCol()),
                         distanceToS(other.getDistanceToS()) {}

Node::~Node() {
}

int Node::getRow() {
   return row;
}

int Node::getCol() {
   return col;
}

int Node::getDistanceToS() {
   return distanceToS;
}

void Node::setDistanceToS(int distanceToS) {
    this->distanceToS = distanceToS;
}

/*
 * Check whether this node equals other node
 * in terms of their absolute positions in the environment.
 */
bool Node::equals(Node &other) {
    bool isEqual = false;
    int thisRow = this->getRow(), otherRow = other.getRow();
    int thisCol = this->getCol(), otherCol = other.getCol();

    if ((thisRow == otherRow) && (thisCol == otherCol))
        isEqual = true;

    return isEqual;
}

/*
 * Make sure these conditions are met for adding nodes, barring goalNode,
 * to pathList from closedList, a complete list of nodes the robot has explored.
 *
 * ((The row of the node to add differs by 1 from that of pointerNode)
 *                                  AND
 *  (The column of the node to add should be identical to that of pointerNode))
 *                                  OR
 * ((The column of the node to add differs by 1 from that of pointerNode)
 *                                  AND
 *  (The row of the node to add should be identical to that of pointerNode))
 */
bool Node::isTraversable(Node &other) {
    bool res = false;
    int rowDiff = this->getRow() - other.getRow();
    int colDiff = this->getCol() - other.getCol();

    if ( (colDiff == 0) && ((rowDiff == -1) || (rowDiff == 1)) )
        res = true;
    else if ( (rowDiff == 0) && ((colDiff == -1) || (colDiff == 1)) )
        res = true;

    return res;
}

/*
 * After pathList contains all the nodes that make up a path,
 * compare each node, barring startNode, to its adjacent node
 * and determine what symbol of direction can replace the period corresponding
 * to the former node.
 */
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