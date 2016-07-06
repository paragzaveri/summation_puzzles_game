#include <iostream>
#include <string>


using namespace std;

template <typename E>
Summation_Puzzle<E>::Summation_Puzzle()
: first_word(""), second_word(""), summation(""), str_entry(""),
 MAX_SIZE(26), s_counter(0), u_counter(10)
{
	S = new E [MAX_SIZE];
	U = new E [MAX_SIZE];
	calculate_k_value();
}

template <typename E>
Summation_Puzzle<E>::Summation_Puzzle(const string & one, 
	const string & two, const string & three)
: first_word(one), second_word(two), summation(three), str_entry(""),
 MAX_SIZE(26), s_counter(0), u_counter(10)
{
	S = new E [MAX_SIZE];
	U = new E [MAX_SIZE];
	for (size_t i = 0; i != 10; i++)
	{
		U[i] = static_cast<E>(i);
	}
	calculate_k_value();
}

//I need a copy constructor

template <typename E>
Summation_Puzzle<E>::~Summation_Puzzle()
{
	delete [] S;
	delete [] U;
}

template <typename E>
void Summation_Puzzle<E>::calculate_k_value(void)
{
	string total = first_word + second_word + summation;
	insertion_sort(total);
	remove_duplicates(total);
	str_entry = total;
	cout << str_entry << endl;
	k = total.size();
	return;
}


template <typename E>
void Summation_Puzzle<E>::insertion_sort(string & data)
{
	size_t size = data.size();
	for (size_t i = 1; i != size; i++)
	{
		char cur = data[i];
		size_t j = i - 1;
		while ((j+1 > 0) && (data[j] > cur))
		{
			data[j+1] = data[j];
			j--;
		}
		data[j+1] = cur;
	}
	return;
}

template <typename E>
void Summation_Puzzle<E>::remove_duplicates(string & word)
{
	string::size_type size = word.size();
	string::size_type counter = 0; 
	for (size_t i = 0; i!=word.size(); i++)
	{
		if ((word[i] == word[i + 1]) && word[i] != char())
		{
			counter++;
			for (size_t j = i; j != word.size(); j++)
			{
				word[j] = word[j+1];
			}
		}
	}
	word.resize(size-counter);
	return;
}

template <typename E>
void Summation_Puzzle<E>::solve_puzzle(size_t k, E * s,
 size_t & s_counter, E * u, size_t & u_counter)
{
	//cerr<<"solving "<<k<<"-extension\n";
	for (size_t i = 0; i != u_counter; i++)
	{
		E data = remove_item(u,u_counter, i);
		s[s_counter] = data;
		s_counter++;
		if (k == 1)
		{
			if (test_solution(s,s_counter))
			{
				cout << "That is a solution: " << endl;
				cout << "Solution is: " << endl;
				for (size_t i = 0; i != s_counter; i++)
				{
					cout << s[i] << ' ' << flush;
				}
				cout << endl;
			}
	
			
		}
		else
		{
		    solve_puzzle(k-1, s, s_counter, u, u_counter);
		}
		add_item(u,u_counter, i, data);
		s[s_counter] = E();
		s_counter--;
	}
	return;
}

template <typename E>
E Summation_Puzzle<E>::remove_item(E * array, 
	size_t & counter, const size_t & index)
{
	E temp = array[index];
	for (size_t i = (index + 1); i != counter; i++)
	{
		array[i-1] = array[i];
	}
	counter--;
	return temp;
}

template <typename E>
void Summation_Puzzle<E>::add_item(E * array, 
	size_t & counter, const size_t & index, const E & item)
{
	for (size_t i = counter; i != index; i--)
	{
		array[i] = array[i - 1];
	}
	array[index] = item;
	counter++;
	return;
}

template <typename E>
bool Summation_Puzzle<E>::test_solution(E * set, const size_t & s_counter)
{

	E * first = new E [MAX_SIZE];
	size_t first_counter = 0;
	E * second = new E [MAX_SIZE];
	size_t second_counter = 0;
	E * sum = new E [MAX_SIZE];
	size_t sum_counter = 0;
	for (size_t i = first_word.size() - 1; i+1 > 0; i--)
	{
		first[first_counter] = find_letter(set, s_counter, first_word[i]);
		first_counter++;
	}
	for (size_t i = second_word.size() - 1; i+1 > 0; i--)
	{
		second[second_counter] = find_letter(set, s_counter, second_word[i]);
		second_counter++;
	}
	for (size_t i = summation.size() - 1; i+1 > 0; i--)
	{
		sum[sum_counter] = find_letter(set, s_counter, summation[i]);
		sum_counter++;
	}

	E * mods = new E [MAX_SIZE];
	size_t mods_counter = 0;

	/*for (size_t i = 0; i!= MAX_SIZE; i++)
	{
		mods[i] = 0;
	}*/

	if (first_counter > second_counter)
	{
		for (size_t i = 0; i != first_counter; i++)
		{
			mods[i] += (first[i] + second[i]) % 10;
			mods[i + 1] += (first[i] + second[i]) / 10;
			mods_counter++;
		}
	}
	else
	{
		for (size_t i = 0; i != second_counter; i++)
		{
			mods[i] += (first[i] + second[i]) % 10;
			mods[i + 1] += (first[i] + second[i]) / 10;
			mods_counter++;
		}
		
	}

	if (mods[mods_counter] != 0)
	{
		return false;
	}

	bool arrays_equal = true;
	for (size_t i = 0; i != mods_counter; i++)
	{
		if (mods[i] != sum[i])
		{
			arrays_equal = false;
		}
	}

	return arrays_equal /* ? true : false */;

}

template <typename E>
E Summation_Puzzle<E>::find_letter(E * set, 
	const size_t & s_counter, const char & letter)
{
	size_t index = 0;
	bool keep_looping = true;
	while ((index != s_counter) && keep_looping)
	{
		if (letter == str_entry[index])
		{
			keep_looping = false;
		}
		index++;
	}
	return set[index-1];
}

template <typename E>
void Summation_Puzzle<E>::find_solution() 
{
	solve_puzzle(k,S,s_counter, U,u_counter);
	return;
}

