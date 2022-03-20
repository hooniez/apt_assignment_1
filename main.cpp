#include <iostream>
#include <stdexcept> // part of the error handling library
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathPlanner.h"
#include "Tests.h"
#include "IO.h"

int main(int argc, char** argv) {
    std::cout << "TESTING - COMMENT THEM OUT TESTING BEFORE YOU SUBMIT!!!\n" << std::endl;
    readEnvFile("Tests/testGetPath.env");
//    testFullOpenList();
//    testDeepCopyClosedList();
//    testGetPath();
//    testPrintPath();
    std::cout << "\nDONE TESTING" << std::endl << std::endl;
}

// For Milestone 4, consider using a string to read the first line with getline to find out the column length
// for the size of an array.







