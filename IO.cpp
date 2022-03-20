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

std::string stringifyEnv(Env env) {
    std::ostringstream os;
    std::string res;

    for (size_t i = 0; i < ENV_DIM; ++i) {
        for (size_t j = 0; j < ENV_DIM; ++j) {
            os << env[i][j];
        }
        if (i != ENV_DIM - 1)
            os << std::endl;
    }

    res = os.str();
    return res;
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

