//
// Created by Myeonghoon Sun on 17/3/2022.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "NodeList.h"
#include "Node.h"
#include "Tests.h"
#include "PathPlanner.h"
#include "IO.h"
#include "Types.h"


/*
 *  This test checks whether getReachableNodes() adds nodes to openList in accordance with the pseudocode.
 */

Test::Test(const std::string & loc): envFile(loc + ".env"), expOutputFile(loc + ".expout"), actualOutputFile(loc + ".actualout")  {
    readEnvFile(env, envFile);
}

void compOutputs(const std::string &expOut, const std::string& actualOut) {
    if (expOut == actualOut)
        std::cout << "Passed" << std::endl;
    else
        std::cout << "FAILED, Please debug by running diff <testName>.actualout <testName>.expout" << std::endl;
    std::cout << std::endl;
}

void testFullOpenList() {
    Test test("Tests/testFullOpenList");

    // Create pathPlanner for testing
    PathPlanner* pathPlanner = new PathPlanner(test.env, ENV_DIM, ENV_DIM);

    std::cout << "Running testFullOpenList" << std::endl;
    // getReachableNodes() algorithm returns a deep copy of closedList
    // which is irrelevant to the current testing, so will free up the associated memory straight away.
    NodeListPtr deepCopyClosedList = pathPlanner->getReachableNodes();
    delete deepCopyClosedList;
    deepCopyClosedList = nullptr;

    // Now we check whether its openList contains exactly the same nodes as noted previously in testFullOpenList.expout
    std::string actualOut = pathPlanner->stringifyNodeList("open");

    // For instant feedback, compare whether the expected output is the same as the actual output.
    std::string expOut = ReadFileToString(test.expOutputFile);
    compOutputs(actualOut, expOut);

    // Write the test result to a file for further analysis via diff command.
    stringToFile(actualOut, test.actualOutputFile);

    delete pathPlanner;
    pathPlanner= nullptr;
}

/*
 * This test checks whether a deep copy of closedList is returned
 * as a returned NodeList of getReachableNodes()
 * This test in addition implicitly checks the validity of PathPlanner::isReachable()
 */
void testDeepCopyClosedList() {
    Test test("Tests/testDeepCopyClosedList");
    std::cout << "Running testDeepCopyClosedList" << std::endl;

    PathPlanner* pathPlanner = new PathPlanner(test.env, ENV_DIM, ENV_DIM);

    // getReachableNodes() algorithm returns a deep copy of closedList
    NodeListPtr deepCopyClosedList = pathPlanner->getReachableNodes();
    // Access closedList to make a comparison.
    NodeListPtr closedList = pathPlanner->getClosedList();

    // Access the node at the specified index below
    // Change its distance property
    // See the change is reflected in the other list.
    // use ostringstream to build actualOut to compare to expOut
    std::ostringstream os;
    size_t idx = deepCopyClosedList->getLength() - 1;
    os << "a deep copy of ClosedList's first node's distance: " << deepCopyClosedList->get(idx)->getDistanceToS() << std::endl;
    os << "ClosedList's first node's distance: " << closedList->get(idx)->getDistanceToS() << std::endl;
    // Set newDis to -1, a value never to be found unless specifically set
    int newDis = -1;
    deepCopyClosedList->get(idx)->setDistanceToS(newDis);
    os << "-----After the distance change----" << std::endl;
    os << "a deep copy of ClosedList's first node's distance: " << deepCopyClosedList->get(idx)->getDistanceToS() << std::endl;
    os << "ClosedList's first node's distance: " << closedList->get(idx)->getDistanceToS() << std::endl;

    std::string actualOut = os.str();
    std::string expOut = ReadFileToString(test.expOutputFile);
    compOutputs(expOut, actualOut);

    // Write the test result to a file for further analysis via diff command.
    stringToFile(actualOut, test.actualOutputFile);

    delete pathPlanner;
    delete deepCopyClosedList;
}

//void testGetPath() {
//    Test test("Tests/testGetPath");
//    std::cout << "Running testGetPath" << std::endl;
//
//    PathPlanner* pathPlanner = new PathPlanner(test.env, ENV_DIM, ENV_DIM);
//
//}

///* This test ensures that nodes are inserted in openList in the expected order according to env
// * and getReachableNodes algorithm works as expected by checking whether the contents of openList are identical to those of closedList
// */
//void testGetReachableNodes(PathPlanner* pathPlanner) {
//    std::cout << "TESTING OpenList" << std::endl;
//
//    NodeListPtr returnedList = pathPlanner->getReachableNodes();
//    std::cout << "Expected value is 34" << std::endl;
//    std::cout << "Actual value is " << returnedList->getLength() << std::endl;
//
//}


//
//// Make a simple NodeList, should be empty size
//std::cout << "NodeList size: " << nodeList->getLength() << std::endl;
//
//// Add a Node to the NodeList, print size
//Node* b1 = new Node(1, 1, 1);
//nodeList->addBack(b1);
//std::cout << "NodeList size: " << nodeList->getLength() << std::endl;
//
//// Add second Nodetest
//Node* b2 = new Node(0, 0, 1);
//nodeList->addBack(b2);
//std::cout << "NodeList size: " << nodeList->getLength() << std::endl;
//
//// Test Get-ith - should be 0,0,1
//Node* getB = nodeList->get(1);
//std::cout << getB->getRow() << ",";
//std::cout << getB->getCol() << ",";
//std::cout << getB->getDistanceToS() << std::endl;
//
//// Print out the NodeList
//std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO" << std::endl;