#include <fstream>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <windows.h>

#include "debug.h"

bool pathValid(std::string path)
{
	std::fstream checker(path);
	bool t = checker.is_open();
	checker.close();
	return t;
}

void print_colored_text(std::string text, TEXT_COLORS color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	std::cout << text << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void printError(std::string text) // Prints bright red text to the CLI
{
	print_colored_text(text, TEXT_COLORS::BAD);
}

void printWarning(std::string text) // Prints yellow text to the CLI
{
	print_colored_text(text, TEXT_COLORS::OKAY);
}

void printSuccess(std::string text) // Prints bright green text to the CLI
{
	print_colored_text(text, TEXT_COLORS::GOOD);
}

int random(int min, int max)
{
	srand((int)time(NULL));
	return(rand() % (max - min + 1) + min);
}