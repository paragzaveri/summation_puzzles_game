#include <cstdlib>
#include <iostream>
#include <string>

#include "summation_puzzles_class.h"

using namespace std;

//Main Program
int main(void)
{
	/* Variable to store the proposed two words and its
	proposed sum.  Values will be used in a construction call
	to later check if there exists a solution*/
	string first_word = "";
	string second_word = "";
	string summation = "";

	// Prompt and input values from user for the words
	cout << "Enter the first word: " << flush;
	cin >> first_word;
	cout << "Enter the second word: " << flush;
	cin >> second_word;
	cout << "Enter the proposed solution: " << flush;
	cin >> summation;
	cout << endl;

	//Construct a summation puzzle object using the inputted values
	Summation_Puzzle<int> temp(first_word, second_word, summation);
	//use the class member function to test
	//if a solution exists with those words
	temp.find_solution();
	return EXIT_SUCCESS;
}

