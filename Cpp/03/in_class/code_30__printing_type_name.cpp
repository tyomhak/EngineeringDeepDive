
#include <iostream>
#include <string>
#include <list>
#include <vector>


// All this capabilities allow us to convert back given type
// to its name.


/// This template class prints name of the template typename argument.
template< typename T >
struct type_name_printer
{
	static std::string name()
		{ return std::string(); }  // Do nothing in the base implementation
};


// List of specializations
template<>
struct type_name_printer< int >
	{ static std::string name()
		{ return "int"; } };

template<>
struct type_name_printer< long long >
	{ static std::string name()
		{ return "long long"; } };

template< typename T >
struct type_name_printer< T* >
	{ static std::string name()
		{ return type_name_printer< T >::name() + "*"; } };

template< typename T >
struct type_name_printer< const T >
	{ static std::string name()
		{ return "const " + type_name_printer< T >::name(); } };


int main( int argc, char* argv[] )
{
	using std::cout;
	using std::endl;

	// Part 1
	{
		cout << type_name_printer< const int >::name() << endl;
		cout << type_name_printer< long long** >::name() << endl;
	}

	// Part 2
	{
		cout << type_name_printer< int[15] >::name() << endl;
		cout << type_name_printer< char[50][30] >::name() << endl;
		cout << type_name_printer< int& >::name() << endl;
		cout << type_name_printer< const int& >::name() << endl;
		cout << type_name_printer< const int* const >::name() << endl;
	}

	// Part 3
	{
		cout << type_name_printer< std::vector< int > >::name() << endl;
		cout << type_name_printer< std::list< std::vector< char > > >::name() << endl;
	}

	return 0;
}
