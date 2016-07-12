#include <string>

template <typename E>
class Summation_Puzzle
{

private:
	std::string first_word;
	std::string second_word;
	std::string summation;
	std::string str_entry;
	const size_t MAX_SIZE;
	E * S;
	size_t s_counter;
	E * U;
	size_t u_counter;
	size_t k;

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

	Function prints the string of characters after sorting and removal
	of duplicates.

	Finally, the function calculates the size of the string and sets
	it to the k value of the class' member value.

	Return type is void because the value is set to a class member 
	variable.

	*/
	void calculate_k_value(void);


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
	void insertion_sort(std::string & data);


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
	void remove_duplicates(std::string & word);


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

	The return type is bool indicating if a solution if found.

	*/
	bool solve_puzzle(size_t k, E * s, 
		size_t & s_counter, E * u, size_t & u_counter, bool & solution);



	/* Private helper function for removing an item from a set.

	Takes the pointer to the array, its size, and the index to remove
	from as arguments.

	Stores the value at the specified index of the array and returns it.

	Moves all subsequent items to the left to effectively erase the 
	value at the specified location

	Return type is E (specfied when object was created).

	*/
	E remove_item(E * array, 
		size_t & counter, const size_t & index);



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
	void add_item(E * array, 
		size_t & counter, const size_t & index, const E & item);


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
	bool test_solution(E * set, const size_t & s_counter);


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
	E find_letter(E * set, const size_t & s_counter, const char & letter);

public:
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
	Summation_Puzzle();

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
	Summation_Puzzle(const std::string & one,
	 const std::string & two, const std::string & three);

	/*Copy constructor

	Takes an entire Summation_Puzzle object as an argument.

	Will initialize every member variable of the new object to
	its associated variable's value from the argument's object.
	This is effectively copying the object.

	Rather than copy the pointer to the two sets S and U, we are allocating
	new dynamic memory and copy all of the values of each array to the new
	allocated memory.

	Also, we are calling calculate_k_value to calculate the new objects
	k value.  It seems unecessary, but for symmetry, it is still being done.

	There is no return type as this is a constructor.

	*/
	Summation_Puzzle(const Summation_Puzzle & copy);

	/* Assignment Operator for copy values into a new object from existing

	Operator overloaded for the = operator.  Will copy data from object
	into another object by using = sign.  Takes a summation_puzzle object
	as an argument.

	Will copy first_word, second_word, etc through all the member variables
	of the argument object into the calling object.

	Will iterate through the set S and U arrays to copy its data as well.

	Return type is Summation_Puzzle (the object) and will return *this.

	*/
	Summation_Puzzle<E> operator=(const Summation_Puzzle & copy);


	/*Destructor

	Deallocates memory for the S and U arrays used to solve the puzzle.

	Called with delete is called on an object of this class

	*/
	~Summation_Puzzle();



	/* Public Member function used for checking if solution

	Takes no arguments.

	Calls solve_puzzle which calls other private member functions
	to test if summation exists.

	Prints success or failure message.

	Return type is void.

	*/
	void find_solution();


};

#include "summation_puzzles_class.cpp"
