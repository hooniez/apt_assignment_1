//
// Created by Myeonghoon Sun on 17/3/2022.
//

#ifndef COSC_ASS_ONE_TESTS_H
#define COSC_ASS_ONE_TESTS_H

#include "PathPlanner.h"

struct Test {
    Test(const std::string &);
    std::string envFile;
    std::string expOutputFile;
    std::string actualOutputFile;
    Env env;
};

// Compare the actual output to the expected output for a quick comparison
void compOutputs(const std::string &, const std::string&);

// Test whether getReachableNodes() adds nodes in the right order
void testFullOpenList();

// Test whether the Nodelist returned from getReachableNodes() is a deep-copy of closedList.
void testDeepCopyClosedList();

// Test whether openList contains the expected number of nodes
void testGetPath();




#endif //COSC_ASS_ONE_TESTS_H
