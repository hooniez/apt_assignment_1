
#include "PathPlanner.h"

#include <iostream>
#include <sstream>

PathPlanner::PathPlanner(Env env, int rows, int cols): rows(rows), cols(cols) {
    // Create an array of pointers to char on the heap
    this->env = new char*[ENV_DIM];
    for (size_t i = 0; i < ENV_DIM; ++i)
        // env is a pointer to an array of char
        // env[i] decays to the memory address of the first element in env[i], which is a char
        this->env[i] = env[i];

    char currChar;
    for (size_t currRow = 0; currRow < rows; ++currRow) {
        for (size_t currCol = 0; currCol < cols; ++currCol) {
            currChar = env[currRow][currCol];
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
   openList->addBack(new Node(startNode->getRow(), startNode->getCol(), startNode->getDistanceToS()));
   // Point pointerNode to startNode
   pointerNode = startNode;
}

PathPlanner::~PathPlanner() {
    delete env;
    delete openList;
    openList = nullptr;
    delete closedList;
    closedList = nullptr;
    delete pathList;
    pathList = nullptr;
    pointerNode = nullptr;
    delete startNode;
    startNode = nullptr;
    delete goalNode;
    goalNode = nullptr;

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
// TODO: the search order will determine the path selected.
NodeList* PathPlanner::getPath(){
    // Iterate in reverse order to find goalNode
    NodePtr currNode;
    bool isGoalNodeFound = false;
    for (int i = closedList->getLength() - 1; i >= 0; --i) {
        currNode = closedList->get(i);

        if (!isGoalNodeFound) {
            if (currNode->equals(*goalNode)) {
                // Update goalNode's distance to the correct value
                goalNode->setDistanceToS(currNode->getDistanceToS());
                // Add a deep copy of goalNode at pathList's nodes[goalNode's distance]
                pathList->addPathNode(new Node(goalNode->getRow(), goalNode->getCol(), goalNode->getDistanceToS()));
                isGoalNodeFound = true;
                pointerNode = currNode;
            }
        } else {
            if (currNode->isPathable(*pointerNode)) {
                pathList->addPathNode(new Node(currNode->getRow(), currNode->getCol(), currNode->getDistanceToS()));
                pointerNode = currNode;

            }
        }
    }

    return new NodeList(*pathList);
}

void PathPlanner::goalPosition(int row, int col) {
    // Assign goalNode's distanceToS with -1, which is to be updated in getPath();
    goalNode = new Node(row, col, -1);
}

/*
 * Check whether the cell in question is reachable.
 * For the cell to be reachable, it has to be within the boundaries of env
 * (In this assessment, we assume the environment is surrounded by walls)
 * and it has to contains 'S', 'G', or '.'.
 */
bool PathPlanner::isReachable(int row, int col) {
    bool res = false;
    // If row or column is inside the boundaries of env
    if ((row >= 0) && (row < rows) && (col >= 0) && (col < cols))
        // If the value of the cell in question is not equal to '='
        if ((env[row][col] == SYMBOL_EMPTY) || (env[row][col] == SYMBOL_START) || (env[row][col] == SYMBOL_GOAL))
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

