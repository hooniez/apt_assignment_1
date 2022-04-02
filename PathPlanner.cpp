#include "PathPlanner.h"
constexpr int PathPlanner::searchingOrder[NUM_ADJACENT_CELLS][NUM_POINTS];

PathPlanner::PathPlanner(Env env, int rows, int cols): env(env),
                                                       rows(rows),
                                                       cols(cols) {
    char currChar;
    for (int currRow = 0; currRow < rows; ++currRow) {
        for (int currCol = 0; currCol < cols; ++currCol) {
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
        // While there's a node in openList absent in closedList
    } while (isPointerNodeAssigned());
    return new NodeList(*closedList);
}

/*
 * getPath() iterates closedList in reverse order to find goalNode.
 *
 * The nodes added after goalNode in closedList are either nodes
 * the same distance away from startNode or those with a longer distance
 * away from startNode. Therefore, they can be disregarded in selecting nodes
 * for pathList.
 *
 * Once goalNode is found, stack stores all the traversable nodes of the same
 * distance from pointerNode. The node that gets added at last is the one
 * searched and added first to closedList. That node makes it into pathList.
 *
 * The above addition goes on until the valid node adjacent to startNode
 * is added. It is only then that startNode is added to render pathList complete.
 *
 * A deepcopy of pathList is returned.
 */
NodeList* PathPlanner::getPath(){
    NodePtr currNode = nullptr;
    int currNodeDis = 0;
    bool isGoalNodeFound = false;
    // currDisToSearch to ensure nodes of a certain distance are added to stack
    int currDisToSearch = 0;

    // A stack to contain all traversable equidistant nodes
    NodeListPtr stack = new NodeList(nodeListMaxLength);

    for (int i = closedList->getLength() - 1; i >= 0; --i) {
        currNode = closedList->get(i);
        currNodeDis = currNode->getDistanceToS();

        if (!isGoalNodeFound) {
            if (currNode->equals(*goalNode)) {
                // Update goalNode's distance to the correct value
                goalNode->setDistanceToS(currNodeDis);

                // Add a deep copy of goalNode at pathList's nodes[goalNode's distance]
                pathList->addPathNode(new Node(*goalNode));
                isGoalNodeFound = true;
                pointerNode = currNode;
                // The distance of the next node to look for
                currDisToSearch = currNodeDis - 1;
            }
        } else { // If goalNode is found
            /*
             * If all the valid nodes of the same distance as currDisToSearch
             * (also traversable from pointerNode) have been added to stack,
             * pop the node from the top of the stack and add it to pathList.
             * Decrement currDisToSearch by 1 and destruct the stack and
             * create another one on heap.
             */
            if (currNodeDis < currDisToSearch) {
                NodePtr topNode = stack->get(stack->getLength() - 1);
                NodePtr newNode = new Node(*topNode);
                topNode = nullptr;
                pathList->addPathNode(newNode);
                pointerNode = newNode;
                --currDisToSearch;
                delete stack;
                stack = nullptr;
                stack = new NodeList(nodeListMaxLength);
            }
            /*
             * If the node in question has the same distance as currDisToSearch
             * and is traversable from the last node added to pathList
             * Add it to a stack for further processing.
             */
            if (currNode->isTraversable(*pointerNode)) {
                // if currNode is startNode
                if (currNodeDis == 0)
                    pathList->addPathNode(new Node(*currNode));
                else
                    stack->addBack(new Node(*currNode));
            }
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
 * (In this assessment, we assume the environment is always surrounded by walls)
 * and it has to contains 'S', 'G', or '.'.
 */
bool PathPlanner::isReachable(int row, int col) {
    bool res = false;
    // If row or column is inside the boundaries of env
    if ((row >= 0) && (row < rows) && (col >= 0) && (col < cols))
        // If the value of the cell in question is not equal to '='
        if ( (env[row][col] == SYMBOL_EMPTY) ||
             (env[row][col] == SYMBOL_START) ||
             (env[row][col] == SYMBOL_GOAL) )
            res = true;
    return res;
}

// Add traversable nodes absent in openList in the following order:
// Up, Right, Down, Left
void PathPlanner::addToOpenList() {
    int currRow = pointerNode->getRow();
    int currCol = pointerNode->getCol();
    int currDis = pointerNode->getDistanceToS();

    NodePtr tempNode;
    // Add a node if it is within the boundaries of env
    // and is not already contained in openList
    for (size_t i = 0; i < NUM_ADJACENT_CELLS; ++i) {
        int searchRow = currRow + searchingOrder[i][0];
        int searchCol = currCol + searchingOrder[i][1];
        int searchDis=currDis + 1;
        if (isReachable(searchRow, searchCol)) {
            tempNode = new Node(searchRow, searchCol, searchDis);
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
    int currRow = pointerNode->getRow();
    int currCol = pointerNode->getCol();
    int currDis = pointerNode->getDistanceToS();
    closedList->addBack(new Node(currRow, currCol, currDis));
}

/*
 * Assign pointerNode with a node from openList, that's not in the closedList.
 * If pointerNode is successfully assigned, the function returns true.
 * Otherwise, it returns false.
 */
bool PathPlanner::isPointerNodeAssigned() {
    pointerNode = nullptr;
    bool isAssigned = false;
    bool isMatched = true;

    // Start from the first node in openList
    // and compare it to the node at the same index in closedList.
    size_t openListLength = openList->getLength();
    size_t closedListLength = closedList->getLength();

    // Compare each node upto the length of closedList.
    // This check is redundant as the condition for inserting a node
    // into closedList ensures that closeList will contain the same nodes
    // upto its last index in the same order as the elements in openList
    // (required by the assessment spec).
    for (size_t i = 0; i < closedListLength; ++i) {
        NodePtr nodeInOpenList = openList->get(i);
        NodePtr nodeInClosedList = closedList->get(i);
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

NodePtr PathPlanner::getGoalNode() {
    return goalNode;
}

