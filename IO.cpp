//
// Created by Myeonghoon Sun on 17/3/2022.
//


#include <iostream>
#include <fstream>
#include <sstream>
#include "IO.h"


void readEnvStdin(Env env) {
    for (size_t row = 0; row < ENV_DIM; ++row)
        for (size_t col = 0; col < ENV_DIM; ++col)
            std::cin >> env[row][col];
}

void readEnvFile(Env env, std::string fileName){
    std::ifstream myFile(fileName);
    if (myFile.is_open()) {
        for (size_t row = 0; row < ENV_DIM; ++row)
            for (size_t col = 0; col < ENV_DIM; ++col)
                myFile >> env[row][col];
        myFile.close();
    } else {
        std::cout << "Unable to open file: ";
    }
}

void printEnv(Env env) {
    for (size_t row = 0; row < ENV_DIM; ++row) {
        for (size_t col = 0; col < ENV_DIM; ++col)
            std::cout << env[row][col];
        std::cout << std::endl;
    }
}

std::string ReadFileToString(const std::string &fileName) {
    std::ifstream in(fileName);
    std::stringstream buffer;
    buffer << in.rdbuf();
    return buffer.str();
}

void stringToFile(const std::string &str, const std::string &fileName) {
    std::ofstream out(fileName);
    out << str;
    out.close();
}


