
#include "PathPlanner.h"

#include <iostream>
#include <sstream>

PathPlanner::PathPlanner(Env env, int rows, int cols): env(env), rows(rows), cols(cols) {
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

    // Milestone 4: Make sure the max length is dynamically generated
    nodeListMaxLength = rows * cols;

    openList = new NodeList(nodeListMaxLength);
    closedList = new NodeList(nodeListMaxLength);
    pathList = new NodeList(nodeListMaxLength);

    // Add startNode to openList
    openList->addBack(new Node(*startNode));
    // Point pointerNode to startNode
    pointerNode = startNode;
}

PathPlanner::~PathPlanner() {
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
NodeList* PathPlanner::getPath(){
    // Iterate in reverse order to find goalNode
    NodePtr currNode;
    bool isGoalNodeFound = false;
    closedList->stringify();
    // currDisToSearch is used to add all the nodes with the equal distance traversable from the previous node
    int currDisToSearch = 0;
    // A stack to contain all traversable equidistant nodes
    NodeListPtr stack = new NodeList(nodeListMaxLength);
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
                // The distance of the next node to look for
                currDisToSearch = goalNode->getDistanceToS() - 1;
//                std::cout << "goalNode is added" << std::endl;
//                pathList->stringify();
            }
        } else {
            if (currNode->getDistanceToS() < currDisToSearch) {
                // Add a node from the top of the stack to pathList
                // decrement currDisToSearch
                // Empty stack
                NodePtr topNode = stack->get(stack->getLength() - 1);
                NodePtr newNode = new Node(topNode->getRow(), topNode->getCol(), topNode->getDistanceToS());
                topNode = nullptr;
                pathList->addPathNode(newNode);
                pointerNode = newNode;
                --currDisToSearch;
                delete stack;
                stack = nullptr;
                stack = new NodeList(nodeListMaxLength);

            }
            // If the node in question has the same distance as currDisToSearch and is traversable from the last node added to pathList
            // Add it to a stack for further processing.
            if (currNode->isTraversable(*pointerNode)) {
                if (currNode->getDistanceToS() == 0)
                    pathList->addPathNode(new Node(currNode->getRow(), currNode->getCol(), currNode->getDistanceToS()));
                else
                    stack->addBack(new Node(currNode->getRow(), currNode->getCol(), currNode->getDistanceToS()));

//                // Deepcopy currNode into nodes[currNode->getDistanceToS()]
//                pathList->addPathNode(new Node(currNode->getRow(), currNode->getCol(), currNode->getDistanceToS()));
//                pointerNode = currNode;
//                std::cout << "currNode is traversable to pointerNode" << std::endl;
//                pathList->stringify();
            }
//            else if () { // Make sure the two cells are
//                // The number of paths of the same length from goal to start cannot exceed 2.
//                // If currNode's distance is the same as the pointer's and currNode is traversable to the second last node in pathList
//                // replace pointerNode with currNode since currNode is added before pointerNode in closedList
//                /*
//                 *  ====S..=======
//                    ====...=======
//                    ====......====
//                    =======...====
//                    =======..G====
//                    ==============
//                    This check is necessary for an edge case like the above.
//                 */
//                if (currNode->getDistanceToS() == pointerNode->getDistanceToS()) {
//                    std::cout << "Check whether the node immediately after pointerNode shares the equal distance" << std::endl;
//                    pathList->stringify();
//                    // Check if currNode is traversable to the node after pointerNode in pathList
//                    NodePtr secondLastNode = pathList->get(pointerNode->getDistanceToS() + 1);
//                    if (secondLastNode->isTraversable(*currNode)) {
//                        NodePtr lastNode = pathList->get(pointerNode->getDistanceToS());
//                        delete lastNode;
//                        lastNode = new Node(currNode->getRow(), currNode->getCol(), currNode->getDistanceToS());
//                        pointerNode = currNode;
//                    }
//                }
//            }
        }
    }

    delete stack;
    stack = nullptr;

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

