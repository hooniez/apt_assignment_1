/*
 * Black-box Test Case Description
 *
 * test1.env tests whether the algorithm finds the right path from S to G
 * when S is presented with two equidistant paths towards the top and right.
 * (as required from Milestone 2)
 *
 * test2.env tests whether the algorithm finds the right path from S to G
 * when S is presented with two equidistant paths towards the right and bottom.
 * (as required from Milestone 2)
 *
 * test3.env tests whether the algorithm finds the right path from S to G
 * when S is presented with two equidistant paths towards the bottom and left.
 * (as required from Milestone 2)
 *
 * test4.env tests whether the algorithm finds the right path from S to G
 * when S is presented with two equidistant paths towards the left and top.
 * (as required from Milestone 2)
 *
 * test5.env is a spiral maze to check a basic capability of the pathfinder.
 * It validates the algorithm finds the shortest path when presented with another
 * longer path whose starting cell is searched before the starting cell of
 * the shorter path.
 *
 * test6.env involves multiple equidistant paths crossing paths multiple times,
 * switching directions time and again, more complex than the first 4 envs.
 *
 * test7.env contains the same env as test6.env except that S and G are swapped.
 *
 * test8.env is a mirror image of test6.env.
 *
 * test9.env contains the same env as test8.env except that S and G are swapped.
 *
 * test10.env factors in the case where the problems of equidistant paths and
 * zigzag movement coexist.
 *
 * test11.env contains the smallest map there can be with the minimum number
 * of rows (Optional black-box test for Milestone 4).
 *
 * test12.env contains the smallest map there can be with the minimum number
 * of columns (Optional black-box test for Milestone 4).
 *
 * test13.env contains a map of size 1000 * 3 (Optional black-box test for Milestone 4).
 *
 * test14.env contains a map of size 3 * 1000 (Optional black-box test for Milestone 4).
 *
 * test15.env contains a mpa of size 99 * 100 (It takes a few minutes to test it) (Optional black-box test for Milestone 4).
 */


#include <iostream>
#include <stdexcept> // part of the error handling library
#include <string>
#include <sstream>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathPlanner.h"

// Read an environment from standard input.
void readEnvStdin(Env &);

// Print out an environment as it is read
void printEnv(Env);

// Create on the heap an array of pointers given the number of rows and columns and return a pointer to it.
Env make_env(const size_t rows, const size_t cols);

// Delete the array of pointers created on the heap
void delete_env(Env env, size_t rows, size_t cols);

// Get the number of rows of Env
size_t getEnvRows(Env);

// Get the number of columns of Env
size_t getEnvCols(Env);

void printPath(Env env, NodeList* solution);

// Test whether getReachableNodes() adds nodes to openList in the right order
void testFullOpenList();

// Test whether getReachableNodes() returns a deep-copy of closedList.
void testDeepCopyClosedList();

int main(int argc, char** argv) {
//    std::cout << "TESTING - COMMENT THEM OUT TESTING BEFORE YOU SUBMIT!!!\n" << std::endl;
//    testFullOpenList();
//    testDeepCopyClosedList();

    Env env = nullptr;
    readEnvStdin(env);
    /*
     * As Ruwan has recommended maximising the use of provided functions,
     * readEnvStdin's function signature is kept as it was originally found.
     * Given this constraint, the below two methods are used to find out
     * the number of rows and columns of env.
     */
    size_t numRows = getEnvRows(env);
    size_t numCols = getEnvCols(env);

    PathPlanner* pathPlanner = new PathPlanner(env, numRows, numCols);
    NodeListPtr closedList = pathPlanner->getReachableNodes();
    NodeListPtr pathList = pathPlanner->getPath();

    printPath(env, pathList);

    delete_env(env, numRows, numCols);
    delete pathPlanner;
    delete closedList;
    delete pathList;

    return EXIT_SUCCESS;
}

void readEnvStdin(Env &env) {
    // Store the standard input stream's content so that it can be read twice
    std::ostringstream os;
    bool numColsFound = false;
    size_t numRows = 0, numCols = 0;

    char ch;
    // Read the first row to assign numCols with the correct value
    while (std::cin.get(ch)) {
        os << ch;
        if (!numColsFound) {
            ++numCols;
            // If the new line character is encountered, increment numRows by 1
            if (ch == '\n') {
                numColsFound = true;
            }
        }
        if (ch == '\n')
            ++numRows;
    }

    // Add another row for nullptr at the end of the array of pointers
    ++numRows;

    std::string s = os.str();

    // Create an array of pointers to an array of char on the heap
    env = make_env(numRows, numCols);

    size_t i = 0;
    for (size_t row = 0; row < numRows - 1; ++row) {
        for (size_t col = 0; col < numCols; ++col) {
            env[row][col] = s[i++];
        }
    }
    // Make sure the last row is a nullptr;
    env[numRows - 1] = nullptr;
}

void printEnv(Env env) {
    size_t row = 0, col = 0;
    // while env[row] is not nullptr
    while (env[row] != nullptr) {
        // while the character in the row is not '\0'
        while (env[row][col] != '\n') {
            std::cout << env[row][col++];
        }
        // Print out the new line character
        std::cout << env[row][col];
        ++row;
        col = 0;
    }
}

Env make_env(size_t rows, size_t cols) {
    Env env = nullptr;
    if (rows >= 0 && cols >= 0)  {
        env = new char*[rows];
        // Assign each pointer with an array of chars except the last nullptr.
        for (size_t i = 0; i != rows - 1; ++i) {
            env[i] = new char[cols];
        }
    }
    return env;
}

void delete_env(Env env, size_t rows, size_t cols) {
    if (env) { // if env is not nullptr
        if (rows >= 0 && cols >= 0) {
            for (size_t i = 0; i != rows; ++i) {
                delete[] env[i];
            }
            delete[] env;
            env = nullptr;
        }
    }
}

size_t getEnvRows(Env env) {
    size_t i = 0, numRows = 0;
    while (env[i] != nullptr)
        ++i;
    numRows = i;
    return numRows;
}

size_t getEnvCols(Env env) {
    size_t i = 0, numCols = 0;
    while (env[0][i] != '\n')
        ++i;
    numCols = i;
    return numCols;
}

// First update the environment with direction symbols and then print it.
void printPath(Env env, NodeList* solution) {
    NodePtr currNode = nullptr;
    NodePtr nextNode = nullptr;
    Direction dir = UP;
    size_t row = 0, col =0;
    char directionSymbols[4] = {'^','>','v','<'};

    for (int i = 1; i < solution->getLength() - 1; ++i) {
        currNode = solution->get(i);
        nextNode = solution->get(i + 1);
        // Find out a direction from currNode to the next node
        dir = currNode->getDirectionTo(*nextNode);

        row = currNode->getRow();
        col = currNode->getCol();

        if (dir == UP)
            env[row][col] = directionSymbols[UP];
        else if (dir == RIGHT)
            env[row][col] = directionSymbols[RIGHT];
        else if (dir == DOWN)
            env[row][col] = directionSymbols[DOWN];
        else if (dir == LEFT)
            env[row][col] = directionSymbols[LEFT];
    }
    printEnv(env);
}

/*
 *  testFullOpenList() checks whether getReachableNodes() adds nodes to openList
 *  in accordance with the pseudocode.
 *
 *  How to run this unit test:
 *  Step 1: Draw an environment best-suited for this test
 *  Step 2: In the expected file,
 *  Start writing nodes, in the given order, that will be put in openList
 *  in the form of i: (x,y,d), followed by the newline,
 *  where i = the index of the node, x = col, y = row, d = distance from S.
 *
 *  For example:
 *        0: (1,5,0)
 *        1: (2,5,1)
 *        2: (3,5,2)
 *           .
 *           .
 *           .
 *        63: (9,16,27)
 *        64: (7,16,27)
 *        65: (8,16,28)
 *  Step 3: Run the test and type in the environment or redirect a file of it
 *  to standard input to see whether its actual output
 *  matches the expected output drawn from Step 2.
 */
void testFullOpenList() {
    std::cout << "Running testFullOpenList" << std::endl;
    // Create pathPlanner for testing
    Env env = nullptr;
    readEnvStdin(env);
    size_t numRows = getEnvRows(env);
    size_t numCols = getEnvCols(env);
    PathPlanner* pathPlanner = new PathPlanner(env, numRows, numCols);

    // getReachableNodes() algorithm returns a deep copy of closedList
    // which is irrelevant to the current testing.
    // Therefore, free up the associated memory straight away.
    NodeListPtr deepCopyClosedList = pathPlanner->getReachableNodes();
    delete deepCopyClosedList;
    deepCopyClosedList = nullptr;

    // Check whether openList contains the expected nodes as specified in Step 2.
    std::string result = pathPlanner->getOpenList()->stringify();

    std::cout << result;

    delete_env(env, numRows, numCols);
    delete pathPlanner;
    pathPlanner= nullptr;
}

/*
 * testDeepCopyClosedList() test checks whether a deep copy of closedList
 * is returned from getReachableNodes().
 *
 * How to run this unit test:
 * Step 1: Draw an environment best-suited for this test
 * Step 2: Calculate the shortest distance between S and G, and write it in
 * the expected file followed by a newline, -1, and another newline.
 * For example:
 *      34
 *      -1
 *
 * (In the test's function body, the goalNode's distance from the deep copy of
 * closedList will be set to -1. The goalNode's distance from both the original
 * closedList and its deep copy will be then printed on the console)
 *
 * Step 3: Run the test and type in the environment or redirect a file of it
 *  to standard input to see whether its actual output
 *  matches the expected output drawn from Step 2.
 */
void testDeepCopyClosedList() {
    std::cout << "Running testDeepCopyClosedList" << std::endl;
    // Create pathPlanner for testing
    Env env = nullptr;
    readEnvStdin(env);
    size_t numRows = getEnvRows(env);
    size_t numCols = getEnvCols(env);
    PathPlanner* pathPlanner = new PathPlanner(env, numRows, numCols);

    // getReachableNodes() algorithm returns a deep copy of closedList
    NodeListPtr deepCopyClosedList = pathPlanner->getReachableNodes();

    // Get goalNode stored in the original closedList.
    NodePtr goalNode = pathPlanner->getGoalNode();
    // Get a deep copy of goalNode stored in deepCopyClosedList
    NodePtr goalNodeCopy = deepCopyClosedList->getTheSameNode(goalNode);

    // Change the distance of goalNode to -1 in goalNode
    // and output distances of both goalNode and goalNodeCopy
    goalNode->setDistanceToS(-1);

    std::cout << goalNodeCopy->getDistanceToS() << std::endl;
    std::cout << goalNode->getDistanceToS() << std::endl;

    delete_env(env, numRows, numCols);
    delete pathPlanner;
    delete deepCopyClosedList;
}




