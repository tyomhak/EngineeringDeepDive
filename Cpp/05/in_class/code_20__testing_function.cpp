
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <string>


// The way of doing that is to use "template template argument".


/// This function tests correctness of the sequenial container "CONT".
template< 
		template< typename T, typename Alloc > class CONT >
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

	std::cout << "Testing in general ..." << std::endl;
}

/// This function tests correctness of the sequenial container "CONT".
template<
		template< typename T, typename Alloc > class CONT >
void test_container< CONT< char, std::allocator<char> > >()
{
	CONT< char > char_cont;
	// 
	// some tests for integers container

	std::cout << "Testing for char sequences ..." << std::endl;
}


// So this means that the following can be used as template arguments:
//  * typenames (classes),
//  * integers,
//  * other templates.
// 
// The list of template arguments of template parameter is MANDATORY,
//    ... so it will be known HOW the template can be instantiated.
//
// Note how the containers are written below... VVV


int main( int argc, char* argv[] )
{
	std::cout << "Testing 'std::vector<>' ..." << std::endl;
	test_container< std::vector >();

	std::cout << "Testing 'std::list<>' ..." << std::endl;
	test_container< std::list >();

	std::cout << "Testing 'std::deque<>' ..." << std::endl;
	test_container< std::deque >();

	return 0;
}
