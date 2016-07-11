#include <iostream>
#include <string>


using namespace std;
/* Default Constructor

Takes no arguments and used when none are specified.

Sets first_word, second_word, summation, and str_entry to the 
empty string default.

Sets the MAX_SIZE of the array to 26 characters and initializes
the S set counter to 0 and the U set counter to 10.

Creates two new arrays for the sets S and U by allocating
dynamic memory to the existing pointers from the class of 
type specified in main and to the MAX_SIZE (26).

Also fills out the U array with all the numbers from 0 to 9 for use
later in the program to calculate the permutation(s) of integers that
solve the puzzle.

Calls function calculate_k_value so that the new instantiation
has a k value upon creation.

*/
template <typename E>
Summation_Puzzle<E>::Summation_Puzzle()
//default values
: first_word(""), second_word(""), summation(""), str_entry(""),
 MAX_SIZE(26), s_counter(0), u_counter(10), k(0)
{
	//new arrays allocated of size 26
	S = new E [MAX_SIZE];
	U = new E [MAX_SIZE];
	for (size_t i = 0; i != 10; i++)
	{
		//E is not neccessarily size_t
		U[i] = static_cast<E>(i);
	}
	//call calculate_k_value for size of possible characters
	//will be zero for this case, but included in case used
	calculate_k_value();
}

/* Argument Constructor

More used than default.  Use this over default when possible.

Takes a name for each of the three strings as the three arguments.

Sets the first_word, second_word, and summation variables to those
three strings.  Also sets str_entry to the empty string.  Sets MAX_SIZE
to 26 and sets S and U counters to 0 and 10 respectively.  S counter
is supposed to start at 0 because its empty and U counter equals 10
because the max is 10 characters.

Dynamically allocates two new arrays of S and U to the MAX_SIZE and 
of type specified from main.

Also fills out the U array with all the numbers from 0 to 9 for use
later in the program to calculate the permutation(s) of integers that
solve the puzzle.

Calls function calculate_k_value so that the new instantiation
has a k value upon creation.

*/
template <typename E>
Summation_Puzzle<E>::Summation_Puzzle(const string & one, 
	const string & two, const string & three)
//initializes the three arguments and defaults values
: first_word(one), second_word(two), summation(three), str_entry(""),
 MAX_SIZE(26), s_counter(0), u_counter(10), k(0)
{
	//allocate new arrays to S and U
	S = new E [MAX_SIZE];
	U = new E [MAX_SIZE];
	//fills the U array from 0-9 to be used later for calculating
	//permutation of solution
	for (size_t i = 0; i != 10; i++)
	{
		//E is not necessarily size_t
		U[i] = static_cast<E>(i);
	}
	//calculate k value of number of distinct letters used in puzzle
	calculate_k_value();
}

/***********************NEEDS COPY CONSTRUCTOR************************/

/*Destructor

Deallocates memory for the S and U arrays used to solve the puzzle.

Called with delete is called on an object of this class

*/
template <typename E>
Summation_Puzzle<E>::~Summation_Puzzle()
{
	delete [] S;
	delete [] U;
}

/* Private Helper Function for find K value

The k value is the number of distinct characters that are used.

Each distinct value will be assigned a integer representation
to find a solution.

Takes no arguments.

Concatentes the two words and potentional solution (summation)
into one string and passes that into a function call for
an insertion sort to put the characters in alphabetical order.

Calls remove_duplication which removes the duplicates from the
returned string.

Finally, the function calculates the size of the string and sets
it to the k value of the class' member value.

Return type is void because the value is set to a class member 
variable.

*/
template <typename E>
void Summation_Puzzle<E>::calculate_k_value(void)
{
	//new string which is all three strings which all possible characters
	string total = first_word + second_word + summation;
	//call an insertion sort to put the string in order
	insertion_sort(total);
	//remove the duplicates of the sorted string
	remove_duplicates(total);
	//stores the finalized list of characters in to class member variable
	//str_entry for use later in the program
	str_entry = total;

	//store size of list for use in computing permutations
	k = total.size();
	return;
}

/* Private Helper Insertion Sort for String

Takes a reference to a string as an argument with the intention
of reordering said string.

Loops through the string and checks if data is lower or greater
and moves it into its correct relative location to the other
values in the string.  Loops through for all values.

Used to reorder string for purpose of removing duplicates later.

Return type is void because string is modified directly from
reference argument.

*/
template <typename E>
void Summation_Puzzle<E>::insertion_sort(string & data)
{
	//size of string for knowledge of how many loops to execute
	size_t size = data.size();
	//loop once for each value in string (will cover 1st value later)
	for (size_t i = 1; i != size; i++)
	{
		//store looped value
		char cur = data[i];
		//start one position sooner
		size_t j = i - 1;
		//check all positions compare relative to other and 
		//place accordingly
		while ((j+1 > 0) && (data[j] > cur))
		{
			data[j+1] = data[j];
			j--;
		}
		data[j+1] = cur;
	}
	return;
}

/* Private Helper Function for removing the duplicates for the 
list of characters

Arugment is a string with a sorted list of characters from the 
first word, second word, and proposed sum of words.

Compares each character and the next character and if 
there are duplicates will remove the next character and move
all subsequent characters one position to the left.

Return type is void as all operations occur to the reference
argument string directly.

*/
template <typename E>
void Summation_Puzzle<E>::remove_duplicates(string & word)
{
	//know how many loop to execute
	string::size_type size = word.size();
	//counter for keeping track of how many characters removed
	string::size_type counter = 0; 
	//loop to check each character
	for (size_t i = 0; i!=word.size(); i++)
	{
		//checks if the character and next character are equal
		if ((word[i] == word[i + 1]) && word[i] != char())
		{
			//increment if character removed
			counter++;
			//move all subsequent elements over to the left one position
			//for removal
			for (size_t j = i; j != word.size(); j++)
			{
				word[j] = word[j+1];
			}
		}
	}
	//resize the string to only fit the remaining characters
	word.resize(size-counter);
	return;
}

/* Private helper function which checks if there exists a possible
permuatation that solves the puzzle.

This is a private class function which executes (along with other function
calls) the entirety of checking if its a solution.  However it is 
called by a public function that main can call.

This function will remove one item from the U set and place it into
the S set.  It will keep doing this recursively until k is decremented
to one.  Then there will be a check by test_solution if the the 
permutation is a solution.  If it is, it will be printed.

When the program unrecurses, it will add the item back to U
and remove it from S.  Then it will recurse again to check
if it's a solution.  It will keep this pattern to meet every
single permutation possible.  Keep in mind it will do this for
every position in the list.  So every permutation will be 
covered.

The arguments are the size of the list of characters, pointers to
set S and U, the S counter and the U counter (which will be modified),
and a boolean for sending success of whether there is a solution.

The return type is bool indicating if their were solutions.

*/
template <typename E>
bool Summation_Puzzle<E>::solve_puzzle(size_t k, E * s,
 size_t & s_counter, E * u, size_t & u_counter, bool & solution)
{
	//loop through for each index of the list of characters
	for (size_t i = 0; i != u_counter; i++)
	{
		//remove item from U and store in S
		E data = remove_item(u,u_counter, i);
		s[s_counter] = data;
		s_counter++;
		//if there is a complete list (will have added one more
		//without decrementing k so entire size is covered)
		if (k == 1)
		{
			//check if permutation is a solution
			if (test_solution(s,s_counter))
			{
				//print message and permutation
				cout << "A Solution is: " << endl;
				solution = true;

				//loop through entire permutation and print each
				//number
				for (size_t i = 0; i != s_counter; i++)
				{
					cout << s[i] << ' ' << flush;
				}
				//newline
				cout << endl;
			}
		}
		//if not a full list continue recursivley calling function
		else
		{
			//recursive call decrements k as a reverse counter
		    solve_puzzle(k-1, s, s_counter, u, u_counter, solution);
		}
		//add the item from S back into U and remove from S
		add_item(u,u_counter, i, data);
		s[s_counter] = E();
		s_counter--;
	}
	return solution;
}

/* Private helper function for removing an item from a set.

Takes the pointer to the array, its size, and the index to remove
from as arguments.

Stores the value at the specified index of the array and returns it.

Moves all subsequent items to the left to effectively erase the 
value at the specified location

Return type is E (specfied when object was created).

*/
template <typename E>
E Summation_Puzzle<E>::remove_item(E * array, 
	size_t & counter, const size_t & index)
{
	//store value existing in array to be returned
	E temp = array[index];
	//loop through and move all subsequent items to the left
	//effectively erasing the item at that index
	for (size_t i = (index + 1); i != counter; i++)
	{
		//move to the left one place for all items in loop
		array[i-1] = array[i];
	}
	//decrement counter indicating that one less item exists
	counter--;
	return temp;
}

/* Private helper function for adding an item back to a set.

Takes a pointer to the array, its size, the specified index
to put the value and a constant reference (for efficiency) of
the value to insert at that index as arguments.

Moves every item to the right of the specified index one place
to the right making from at the specified index for a new value
without losing any information.  Stores the specified value into
the index specifie.

Return type is void as the array is modified directly by the 
function

*/
template <typename E>
void Summation_Puzzle<E>::add_item(E * array, 
	size_t & counter, const size_t & index, const E & item)
{
	/*Loop through entire array starting at one past the end
	and moving every item back one position*/
	for (size_t i = counter; i != index; i--)
	{
		//move items
		array[i] = array[i - 1];
	}
	//store the value passed in into the index specified
	array[index] = item;
	//increment the counter to include one more entry
	counter++;
	return;
}

/* Private helper function for testing whether or not a permutation
is a solution to the puzzle.

Takes a pointer to an array and its size as arguments.

Finds matching letters between the set and the first,second,summation
words.  Stores corresponding numbers in reference to those letters 
into new arrays (alphabetical ordered number association).

Does the summation of the first_word and second_word carrying numbers
with / and finding the base with %.  Final sum is stored in an array
called mods.

Checks each number in mod from the summation of the two words with the
proposed sum entered in main.  If all indicies of these arrays match,
then the permuation is a solution.

Deletes all allocated dynamic memory to test the solution.

Return type is bool which is an indicator of success for the solution.

*/
template <typename E>
bool Summation_Puzzle<E>::test_solution(E * set, const size_t & s_counter)
{

	/* Create three new arrays to store the number represenation from the
	set for each the first_word, second_word, and summation.

	Dynamically allocated arrays for this purpose

	Create counters to keep track of size*/
	E * first = new E [MAX_SIZE];
	size_t first_counter = 0;
	E * second = new E [MAX_SIZE];
	size_t second_counter = 0;
	E * sum = new E [MAX_SIZE];
	size_t sum_counter = 0;

	/* Store the number representation of each letter in the first_word,
	second_word, and summation after check that that letter exists in the
	total available characters string.*/
	for (size_t i = first_word.size() - 1; i+1 > 0; i--)
	{
		//store number of letter in alphabetical order from the passed word
		first[first_counter] = find_letter(set, s_counter, first_word[i]);
		//increment for size
		first_counter++;
	}
	for (size_t i = second_word.size() - 1; i+1 > 0; i--)
	{
		//store number of letter in alphabetical order from the passed word
		second[second_counter] = find_letter(set, s_counter, second_word[i]);
		//increment for size
		second_counter++;
	}
	for (size_t i = summation.size() - 1; i+1 > 0; i--)
	{
		//store number of letter in alphabetical order from the passed word.
		sum[sum_counter] = find_letter(set, s_counter, summation[i]);
		//increment for size
		sum_counter++;
	}

	//dynamically allocate an array for the sum of the two words
	E * mods = new E [MAX_SIZE];
	size_t mods_counter = 0;

	//in case words are of different sizes, use larger word (more space)
	if (first_counter > second_counter)
	{
		//loop through array
		for (size_t i = 0; i != first_counter; i++)
		{
			//store carry from summation of individual numbers
			mods[i] += (first[i] + second[i]) % 10;
			//store value of single digit of sum of numbers
			mods[i + 1] += (first[i] + second[i]) / 10;
			//increment for size
			mods_counter++;
		}
	}
	else
	{
		//loop through array
		for (size_t i = 0; i != second_counter; i++)
		{
			//store carry from summation of individual numbers
			mods[i] += (first[i] + second[i]) % 10;
			//store value of single digit of sum of numbers
			mods[i + 1] += (first[i] + second[i]) / 10;
			//increment for size
			mods_counter++;
		}
		
	}

	//in case the number AFTER the final of mods is not 0
	//error checking
	if (mods[mods_counter] != 0)
	{
		return false;
	}

	//boolean for determining if proposed solution is actual solution
	bool arrays_equal = true;
	//check if each number is identical meaning actual sum is equal
	//to proposed sum
	for (size_t i = 0; i != mods_counter; i++)
	{
		if (mods[i] != sum[i])
		{
			//if not equal solution is false
			arrays_equal = false;
		}
	}

	//deallocated allocated dynamic memory
	delete [] first;
	delete [] second;
	delete [] sum;
	delete [] mods;

	//return whether is solution or not
	return arrays_equal;

}

/*Private Helper Searching Function

Arguments are a set of characters, the size of the set and
the letter that is being seached for.

The primary use of this function is to search whether or not
the characters in a word (such as first_word or second_word) exist
with in the set (set S).  If that is true, the function will
return the number that letter corresponds to.

Another benefit of the use of this function is that the letters in the set
are in order alphabetically, but the letters in the word are not.  This
finds the matching letter in the set and returns that letter from the set
which number is then put into alphabetical order for easy checks on matching
words (not letters).

Uses a while loop that until the end of the set is reached
or the letter is found.

Return type is the type specified in main.  It returns a number.

*/
template <typename E>
E Summation_Puzzle<E>::find_letter(E * set, 
	const size_t & s_counter, const char & letter)
{
	size_t index = 0;
	//boolean used to exist loop if letter found
	bool keep_looping = true;
	//loop until end of set or letter found
	while ((index != s_counter) && keep_looping)
	{
		//if letter matches set boolean to false to exit
		if (letter == str_entry[index])
		{
			keep_looping = false;
		}
		//increment index counter to move to next letter
		index++;
	}
	//return the letter found (decrements because we passed the letter)
	return set[index-1];
}

/* Public Member function used for checking if solution

Takes no arguments.

Calls solve_puzzle which calls other private member functions
to test if summation exists.

Prints success or failure message.

Return type is void.

*/
template <typename E>
void Summation_Puzzle<E>::find_solution() 
{
	bool solution = false;
	//call to private member function solve_puzzle
	solve_puzzle(k,S,s_counter, U,u_counter, solution);
	if (solution)
	{
		cout << "\nSolutions are listed above" << endl;
	}
	else
	{
		cout << "\nThere were no solutions." << 
		" First and Second word do not sum to third word." << endl;
	}
	return;
}

