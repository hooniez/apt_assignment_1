//
// Created by Myeonghoon Sun on 17/3/2022.
//


#include <iostream>
#include <fstream>

#include "IO.h"

//
// Created by Myeonghoon Sun on 21/3/2022.
//

// Make a 2d Dynamic array given the number of rows and columns and return a pointer to an array of pointers




// TODO make it work with milestone 4 implementation


//// Read an environment from file and create an env dynamically on the heap
//EnvPtr readEnvFile(std::string fileName){
//    std::ifstream envFile(fileName);
//
//    std::string line;
//    size_t numRows = 0, numCols = 0;
//    if (envFile.is_open()) {
//        // Find out the number of rows and columns, with which to create env, in runtime
//        while (std::getline(envFile, line)) {
//            ++numRows;
//        }
//        // Record the number of characters in the last row, which is the same as every other row preceding it.
//        numCols = line.length();
//        // Create an array of pointers to an array of char on the heap
//    } else {
//        std::cout << "Unable to open file: ";
//
//    EnvPtr env = new Env(numRows, numCols);
//
//    // Re-read the file again by resetting eofbit and changing the position of the cursor
//    envFile.clear();
//    envFile.seekg(0, envFile.beg);
//
//    // Actually assign each cell with the value read from the file
//    for (size_t row = 0; row < numRows; ++row)
//        for (size_t col = 0; col < numCols; ++col)
//            envFile >> env->getMap()[row][col];
//
//    envFile.close();
//    return env;
//}
//

//
//std::string stringifyEnv(Env env) {
//    std::ostringstream os;
//    std::string res;
//
//    for (size_t i = 0; i < env.getRows(); ++i) {
//        for (size_t j = 0; j < env.getCols(); ++j) {
//            os << env.getMap()[i][j];
//        }
//        // All rows execpt the last row
//        if (i != env.getRows() - 1)
//            os << std::endl;
//    }
//
//    res = os.str();
//    return res;
//}
//
//std::string ReadFileToString(const std::string &fileName) {
//    std::ifstream in(fileName);
//    std::stringstream buffer;
//    buffer << in.rdbuf();
//    return buffer.str();
//}
//
//void stringToFile(const std::string &str, const std::string &fileName) {
//    std::ofstream out(fileName);
//    out << str;
//    out.close();
//}
//

//
