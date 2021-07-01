#pragma once

#include <string>

const enum TEXT_COLORS { BAD = 12, OKAY = 14, GOOD = 10 };

bool pathValid(std::string path);
void printError(std::string text);
void printWarning(std::string text);
void printSuccess(std::string text);
int random(int min, int max);