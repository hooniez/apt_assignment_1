//
// Created by Myeonghoon Sun on 17/3/2022.
//

#ifndef COSC_ASS_ONE_IO_H
#define COSC_ASS_ONE_IO_H

#include "Types.h"
#include <string>
#include "NodeList.h"

// Read an environment from standard input.
void readEnvStdin(Env);

// Read an environment from file.
void readEnvFile(Env, std::string);

// Print out an environment as it is read
void printEnv(Env);

std::string stringifyEnv(Env);

std::string ReadFileToString(const std::string &);

void stringToFile(const std::string &, const std::string &);

// Print out an Environment to standard output with path.
// To be implemented for Milestone 3
void printPath(Env env, NodeList* solution);

#endif //COSC_ASS_ONE_IO_H
