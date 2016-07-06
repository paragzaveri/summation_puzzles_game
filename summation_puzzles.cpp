#include <cstdlib>
#include <iostream>

#include "summation_puzzles_class.h"

using namespace std;


int main(void)
{
	Summation_Puzzle<int> temp("pot", "pan", "bib");
	temp.find_solution();
	return EXIT_SUCCESS;
}

