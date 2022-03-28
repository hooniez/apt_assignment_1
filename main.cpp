#include <iostream>
#include <stdexcept> // part of the error handling library
#include <string>
#include <sstream>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathPlanner.h"
//#include "Tests.h"

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

int main(int argc, char** argv) {
    std::cout << "TESTING - COMMENT THEM OUT TESTING BEFORE YOU SUBMIT!!!\n" << std::endl;
    Env env = nullptr;
    readEnvStdin(env);
    printEnv(env);
    size_t numRows = getEnvRows(env);
    size_t numCols = getEnvCols(env);

    PathPlanner* pathPlanner = new PathPlanner(env, numRows, numCols);
    NodeListPtr closedList = pathPlanner->getReachableNodes();
    std::cout << closedList->stringify() << std::endl;
    NodeListPtr pathList = pathPlanner->getPath();

    pathList->stringify();


    printPath(env, pathList);

    delete_env(env, numRows, numCols);
    delete pathPlanner;
    delete closedList;
    delete pathList;



//    EnvPtr env = readEnvFile("Tests/testFullOpenList.env");

//    env->print()
//    delete env;
//    env = nullptr;
//    testFullOpenList();
//    testDeepCopyClosedList();
//    testGetPath();
//    testPrintPath();
    std::cout << "\nDONE TESTING" << std::endl << std::endl;

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
//    const char* chars = s.c_str();

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
    std::cout << "Printing env" << std::endl;
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
        for (size_t i = 0; i != rows; ++i) {
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

// First update the environment with direction symbols and print it
void printPath(Env env, NodeList* solution) {
    NodePtr currNode = nullptr;
    NodePtr nextNode = nullptr;
    Direction dir = UP;
    size_t row = 0, col =0;
    char directionSymbols[4] = {'^','>','v','<'};

    for (size_t i = 1; i < solution->getLength() - 1; ++i) {
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




