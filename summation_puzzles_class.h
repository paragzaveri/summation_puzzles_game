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

	void calculate_k_value(void);
	void insertion_sort(std::string & data);
	void remove_duplicates(std::string & word);

	void solve_puzzle(size_t k, E * s, 
		size_t & s_counter, E * u, size_t & u_counter);

	E remove_item(E * array, 
		size_t & counter, const size_t & index);
	
	void add_item(E * array, 
		size_t & counter, const size_t & index, const E & item);

	bool test_solution(E * set, const size_t & s_counter);

	E find_letter(E * set, const size_t & s_counter, const char & letter);

public:
	Summation_Puzzle();
	Summation_Puzzle(const std::string & one, const std::string & two, 
		const std::string & three);
	//I need a copy constructor
	~Summation_Puzzle();

	void find_solution();


};

#include "summation_puzzles_class.cpp"
