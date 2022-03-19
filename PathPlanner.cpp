
#include "PathPlanner.h"

#include <iostream>
#include <sstream>

PathPlanner::PathPlanner(Env env, int rows, int cols): rows(rows), cols(cols) {
    char currChar;
    for (size_t currRow = 0; currRow < rows; ++currRow) {
        for (size_t currCol = 0; currCol < cols; ++currCol) {
            currChar = env[currRow][currCol];
            this->env[currRow][currCol] = currChar;
            // Assign startNode with a cell that contains 'S'
            if (currChar == SYMBOL_START)
                initialPosition(currRow, currCol);
            if (currChar == SYMBOL_GOAL)
                goalPosition(currRow, currCol);
        }
    }

   openList = new NodeList();
   closedList = new NodeList();
   pathList = new NodeList();

   // Add startNode to openList
   openList->addBack(startNode);
   // Point pointerNode to startNode
   pointerNode = startNode;
}

PathPlanner::~PathPlanner(){
   delete openList;
   openList = nullptr;
   delete closedList;
   closedList = nullptr;
   pointerNode = nullptr;
   delete goalNode;
   goalNode = nullptr;
   delete pathList;
   pathList = nullptr;
}

// As required by the assessment, initialPosition is called to assign startNode.
void PathPlanner::initialPosition(int row, int col){
    startNode = new Node(row, col, 0);
}

NodeList* PathPlanner::getReachableNodes(){
    do { // In the first loop, startNode is in openList but not in closedList
        addToOpenList();
        addToClosedList();
    }
    while (isCurrNodeAssigned()); // While there's a node in openList absent in closedList
    return new NodeList(*closedList);
}

/*
 * This function needs to be called after separately calling getReachableNodes() as indicated by the main initial template.
 */
NodeList* PathPlanner::getPath(){
    // Iterate in reverse order to find goalNode
    NodePtr currNode;
    bool isGoalNodeFound = false;
    for (size_t i = closedList->getLength() - 1; i > 0; --i) {
        currNode = closedList->get(i);

        if (!isGoalNodeFound) {
            if (currNode->equals(*goalNode)) {
                // Update goalNode's distance to the correct value
                goalNode->setDistanceToS(currNode->getDistanceToS());
                // Add goalNode at pathList's nodes[goalNode's distance]
                pathList->addAt(goalNode->getDistanceToS(), goalNode);
                isGoalNodeFound = true;
                pointerNode = goalNode;
            }
        } else {
            if (currNode->isPathable(*pointerNode)) {

            }
        }
    }
}

void PathPlanner::goalPosition(int row, int col) {
    // Assign goalNode's distanceToS with -1, which is to be updated in getPath();
    goalNode = new Node(row, col, -1);
}

/*
 * Check whether the cell in question is reachable.
 * For the cell to be reachable, it has to be within the boundaries of env and contains 'S', 'G', or '.'
 */
bool PathPlanner::isReachable(int row, int col) {
    bool res = false;
    // If row or column is inside the boundaries of env
    if ((row >= 0) && (row < rows) && (col >= 0) && (col < cols))
        // If the value of the cell in question is not equal to '='
        if (env[row][col] != SYMBOL_WALL)
            res = true;
    return res;
}

// Add traversable nodes not present in openList in the following order: up, right, down, left
void PathPlanner::addToOpenList() {
    int currRow = pointerNode->getRow(), currCol = pointerNode->getCol(), currDis = pointerNode->getDistanceToS();

    NodePtr tempNode;
    // Add a node if it is within the boundaries of env and is not already contained in openList
    for (size_t i = 0; i < NUM_CELLS; ++i) {
        int row = currRow + addingOrder[i][0], col = currCol + addingOrder[i][1], dis=currDis + 1;
        if (isReachable(row, col)) {
            tempNode = new Node(row, col, dis);
            if (openList->containsNode(tempNode)) {
                // If the same coordinate already exists, clean up memory for tempNode
                delete tempNode;
                tempNode = nullptr;
            } else {
                openList->addBack(tempNode);
            }
        }
    }
}

// Add the node pointerNode is pointing to in closedList
void PathPlanner::addToClosedList() {
    int currRow = pointerNode->getRow(), currCol = pointerNode->getCol(), currDis = pointerNode->getDistanceToS();
    closedList->addBack(new Node(currRow, currCol, currDis));
}

/*
 * Assign pointerNode with a node from openList, that's not in the closedList.
 * If pointerNode is successfully assigned, the function returns true. Otherwise, it returns false.
 */
bool PathPlanner::isCurrNodeAssigned() {
    pointerNode = nullptr;
    bool isAssigned = false;
    bool isMatched = true;

    // Start from the first node in openList and compare it the node at the same index in closedList
    size_t openListLength = openList->getLength(), closedListLength = closedList->getLength();
    // Compare each node upto the length of closedList.
    // This check is redundant as the condition for inserting a node into closedList ensures that closeList will contain the same nodes upto its last index in the same order as the elements in openList.
    for (size_t i = 0; i < closedListLength; ++i) {
        NodePtr nodeInOpenList = openList->get(i), nodeInClosedList = closedList->get(i);
        if (!nodeInOpenList->equals(*nodeInClosedList))
            isMatched = false;
    }
    // Then check whether the length of openList is greater
    if (isMatched && openListLength > closedListLength) {
        // Assign pointerNode with openList[closedList->getLength()]
        pointerNode = openList->get(closedList->getLength());
        isAssigned = true;
    }
    return isAssigned;
}

NodeListPtr PathPlanner::getOpenList() {
    return openList;
}

NodeListPtr PathPlanner::getClosedList() {
    return closedList;
}

NodeListPtr PathPlanner::getDeepCopiedClosedList() {
    return new NodeList(*closedList);
}

/*
 * Return nodes in the forrmat below for testing purposes
 * (x1,y1,distance1)(x2,y2,distance2)(x3,y3,distance3)...(xi,yi,distancei)
 */
std::string PathPlanner::stringifyNodeList(const std::string &listType) {
    NodeListPtr list = nullptr;
    std::ostringstream os;
    std::string res;
    if (listType == "open")
        list = openList;
    else if (listType == "closed")
        list = closedList;
    else
        res = "Please specify which list type you would like to see the contents for";

    int x, y, dis;
    for (size_t i = 0; i < list->getLength(); ++i) {
        x = list->get(i)->getCol();
        y = list->get(i)->getRow();
        dis = list->get(i)->getDistanceToS();

        os << "(" << x << "," << y << "," << dis << ")\n";
    }
    res = os.str();
    return res;
}