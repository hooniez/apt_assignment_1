#include <iostream>
#include <stdexcept> // part of the error handling library
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathPlanner.h"
#include "Tests.h"
#include "IO.h"

// Print out an Environment to standard output with path.
// To be implemented for Milestone 3
//void printPath(Env env, NodeList* solution);

int main(int argc, char** argv) {
    std::cout << "TESTING - COMMENT THEM OUT TESTING BEFORE YOU SUBMIT!!!\n" << std::endl;
    testFullOpenList();
    testDeepCopyClosedList();
    testGetPath();
    std::cout << "\nDONE TESTING" << std::endl << std::endl;

//    NodeList* reachablePositions = nullptr;
//    reachablePositions = pathplanner->getReachableNodes();
//
//    // Get the path
//    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
//    NodeList* solution = pathplanner->getPath();
//
//    //print the path
//    printPath(env, solution);
//
//    delete pathplanner;
//    delete reachablePositions;
//    delete solution;

}

// For Milestone 4, consider using a string to read the first line with getline to find out the column length
// for the size of an array.



//void printPath(Env env, NodeList* solution) {
//    //TODO
//}
//
//void printReachablePositions(Env env, NodeList* reachablePositions){
//    //TODO
//}
//







