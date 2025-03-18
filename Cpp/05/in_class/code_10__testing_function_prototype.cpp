
#include <list>
#include <string>


// Sometimes we want to provide a template to a function, and let it 
// decise how to instantiate it.


/// This function tests "std::list<>" generic container.
void test_list()
{
	std::list< int > int_list;
	// 
	// some tests for integers list

	std::list< double > dbl_list;
	// 
	// some tests for list of real numbers

	std::list< std::string > string_list;
	// 
	// some tests for list of strings
}


// Note, there is no way of testing the 'std::list<>' template by itself.
// We NEED_TO_INSTANTIATE it somehow.
//
// What about testing OTHER sequential containers, like "deque", "vector", ...?
//
// We might want to have a general function for testing ALL SEQUENTIAL_CONTAINERS.


/// This function tests correctness of the sequenial container "CONT".
void test_container()
{
	CONT< int > int_cont;
	// 
	// some tests for integers container

	CONT< double > dbl_cont;
	// 
	// some tests for container of real numbers

	CONT< std::string > string_cont;
	// 
	// some tests for container of strings
}


// So we want to provide "CONT" template to the function, and ALLOW IT TO 
// INSTANTIATE it later.
