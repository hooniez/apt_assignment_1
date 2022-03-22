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
//
//Test::Test(const std::string & loc): envFile(loc + ".env"), expOutputFile(loc + ".expout"), actualOutputFile(loc + ".actualout")  {
//    env = readEnvFile(envFile);
//}
//
//Test::~Test() {
//    delete env;
//}
//
//void compOutputs(const std::string &expOut, const std::string& actualOut) {
//    if (expOut == actualOut)
//        std::cout << "Passed" << std::endl;
//    else
//        std::cout << "FAILED, Please debug by running diff <testName>.actualout <testName>.expout" << std::endl;
//    std::cout << std::endl;
//}
//
//void testFullOpenList() {
//    Test* test = new Test("Tests/testFullOpenList");
//
//    // Create pathPlanner for testing
//    PathPlanner* pathPlanner = new PathPlanner(*test->env, test->env->getRows(), test->env->getCols());
//
//    std::cout << "Running testFullOpenList" << std::endl;
////    std::cout << "Testing env:" << std::endl;
////     printEnv(test.env);
//
//    // getReachableNodes() algorithm returns a deep copy of closedList
//    // which is irrelevant to the current testing, so will free up the associated memory straight away.
//    NodeListPtr deepCopyClosedList = pathPlanner->getReachableNodes();
//    delete deepCopyClosedList;
//    deepCopyClosedList = nullptr;
//
//    // Now we check whether its openList contains exactly the same nodes as noted previously in testFullOpenList.expout
//    std::string actualOut = pathPlanner->getOpenList()->stringify();
//
//    // For instant feedback, compare whether the expected output is the same as the actual output.
//    std::string expOut = ReadFileToString(test->expOutputFile);
//    compOutputs(actualOut, expOut);
//
//    // Write the test result to a file for further analysis via diff command.
//    stringToFile(actualOut, test->actualOutputFile);
//
//    delete pathPlanner;
//    pathPlanner= nullptr;
//    delete test;
//}
//
///*
// * This test checks whether a deep copy of closedList is returned
// * as a returned NodeList of getReachableNodes()
// * This test in addition implicitly checks the validity of PathPlanner::isReachable()
// */
//void testDeepCopyClosedList() {
//    Test test("Tests/testDeepCopyClosedList");
//    std::cout << "Running testDeepCopyClosedList" << std::endl;
////    std::cout << "Testing env:" << std::endl;
////     printEnv(test.env);
//
//    PathPlanner* pathPlanner = new PathPlanner(test.env, ENV_DIM, ENV_DIM);
//
//    // getReachableNodes() algorithm returns a deep copy of closedList
//    NodeListPtr deepCopyClosedList = pathPlanner->getReachableNodes();
//    // Access closedList to make a comparison.
//    NodeListPtr closedList = pathPlanner->getClosedList();
//
//    // Access the node at the specified index below
//    // Change its distance property
//    // See the change is reflected in the other list.
//    // use ostringstream to build actualOut to compare to expOut
//    std::ostringstream os;
//    size_t idx = deepCopyClosedList->getLength() - 1;
//    os << "a deep copy of ClosedList's first node's distance: " << deepCopyClosedList->get(idx)->getDistanceToS() << std::endl;
//    os << "ClosedList's first node's distance: " << closedList->get(idx)->getDistanceToS() << std::endl;
//    // Set newDis to -1, a value never to be found unless specifically set
//    int newDis = -1;
//    deepCopyClosedList->get(idx)->setDistanceToS(newDis);
//    os << "-----After the distance change----" << std::endl;
//    os << "a deep copy of ClosedList's first node's distance: " << deepCopyClosedList->get(idx)->getDistanceToS() << std::endl;
//    os << "ClosedList's first node's distance: " << closedList->get(idx)->getDistanceToS() << std::endl;
//
//    std::string actualOut = os.str();
//    std::string expOut = ReadFileToString(test.expOutputFile);
//    compOutputs(expOut, actualOut);
//
//    // Write the test result to a file for further analysis via diff command.
//    stringToFile(actualOut, test.actualOutputFile);
//
//    delete pathPlanner;
//    delete deepCopyClosedList;
//}
//
//void testGetPath() {
//    Test test("Tests/testGetPath");
//    std::cout << "Running testGetPath" << std::endl;
//
////    std::cout << "Testing env:" << std::endl;
////    printEnv(test.env);
//
//    PathPlanner* pathPlanner = new PathPlanner(test.env, ENV_DIM, ENV_DIM);
//    NodeListPtr closedList = pathPlanner->getReachableNodes();
//    NodeListPtr pathList = pathPlanner->getPath();
//
//    std::string actualOut = pathList->stringify();
//    std::string expOut = ReadFileToString(test.expOutputFile);
//    compOutputs(expOut, actualOut);
//
//    stringToFile(actualOut, test.actualOutputFile);
//
//    delete pathPlanner;
//    delete pathList;
//    delete closedList;
//
//}
//
//// Blackbox testing
//void testPrintPath() {
//    // In order to run blackbox testing, please upload your env and expected files in Tests folder.
//    Test test("Tests/testPrintPath");
//    std::cout << "Running testPrintPath" << std::endl;
//
//    PathPlanner* pathPlanner = new PathPlanner(test.env, ENV_DIM, ENV_DIM);
//    NodeListPtr closedList = pathPlanner->getReachableNodes();
//    NodeListPtr pathList = pathPlanner->getPath();
//    printEnv(test.env);
//    printPath(test.env, pathList);
//
//    // Represent env in string for ease of comparison to expOut
//    std::string actualOut = stringifyEnv(test.env);
//    std::string expOut = ReadFileToString(test.expOutputFile);
//    compOutputs(expOut, actualOut);
//
//    stringToFile(actualOut, test.actualOutputFile);
//
//    delete pathPlanner;
//    delete pathList;
//    delete closedList;
//
//}