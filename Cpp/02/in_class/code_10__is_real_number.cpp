
#include <iostream>
#include <vector>
#include <algorithm>


// Simplest example of manipulating with types.
//
// Here we query some properties of a type.


/// This template class holds if the argument class is capable of 
/// storing real values.
template< typename NumberType >
struct is_real_number
{
	static const bool value = false;
};

// List of specializations for built-in types.
template<>
struct is_real_number< float >
	{ static const bool value = true; };

template<>
struct is_real_number< double >
	{ static const bool value = true; };

template<>
struct is_real_number< long double >
	{ static const bool value = true; };


/// A custom big-integer class.
class my_big_integer
{
	// Some implementation here
	//
	//
};

/// A custom big-real number class.
class my_big_real
{
	// Some other implementation here
	//
	//
};

// So we need one more specialization.
template<>
struct is_real_number< my_big_real >
	{ static const bool value = true; };


/// Another variant of checking if provided type 'NumberType' 
/// represents a real number.
/// This is NOT SAFE. Controversal examples:
///   --> rational numbers,
///   --> complex numbers.
template< typename NumberType >
struct is_real_number_2
{
	static const bool value 
			= NumberType(20.0) / NumberType(7.0) * NumberType(7.0) > NumberType(19.0);
};


// Another example for testing if provided type is a function-type.


/// Tests if 'T' is a function-type.
template< typename T >
struct is_function
	{ static const bool value = false; };  // By default, not a function

/// Specialization for nullary functions.
template< typename Ret >
struct is_function< Ret (*)() >
	{ static const bool value = true; };

/// Specialization for unary functions.
template< typename Ret, typename Arg1 >
struct is_function< Ret (*)( Arg1 ) >
	{ static const bool value = true; };

/// Specialization for binary functions.
template< typename Ret, typename Arg1, typename Arg2 >
struct is_function< Ret (*)( Arg1, Arg2 ) >
	{ static const bool value = true; };

// Functions to be tested on.
int f1( int a, int b ) { return a - b; }
int f2( int c ) { return c * 3; }


#include <type_traits>
		// Multiple type manipulations are now part of STL, starting 
		// from cpp0x standard.
		// See example calls below ... VVV


int main( int argc, char* argv[] )
{
	using std::cout;
	using std::endl;

	// Part 1.1
	{
		cout << "\t Testing 'is_real_number<>' ..." << endl;

		cout << "Is 'int' a real number : "
				<< is_real_number< int >::value << endl;
		cout << "Is 'float' a real number : "
				<< is_real_number< float >::value << endl;
		cout << "Is 'long long' a real number : "
				<< is_real_number< long long >::value << endl;
	}

	// Part 1.2
	{
		cout << "Is 'my_big_integer' a real number : "
				<< is_real_number< my_big_integer >::value << endl;
		cout << "Is 'my_big_real' a real number : "
				<< is_real_number< my_big_real >::value << endl;
	}

	// Part 2.1
	{
		cout << "\t Testing 'is_real_number_2<>' ..." << endl;

		cout << "Is 'int' a real number (variant 2) : "
				<< is_real_number_2< int >::value << endl;
		cout << "Is 'float' a real number (variant 2) : "
				<< is_real_number_2< float >::value << endl;
		cout << "Is 'long long' a real number (variant 2) : "
				<< is_real_number_2< long long >::value << endl;
	}

	// Part 3.1
	{
		cout << "\t Testing 'is_function<>' ..." << endl;

		cout << "Is 'f1' a function type : "
				<< is_function< decltype(& f1) >::value << endl;
		cout << "Is 'double' a function type : "
				<< is_function< double >::value << endl;
		cout << "Is 'f2' a function type : "
				<< is_function< decltype(& f2) >::value << endl;
		cout << "Is 'std::size< vector<int> >' a function type : "
				<< is_function< decltype(& std::size< std::vector<int> >) >::value << endl;
		cout << "Is 'std::vector< int >' a function type : "
				<< is_function< std::vector< int > >::value << endl;
		cout << "Is 'std::partition< int* >' a function type : "
				<< is_function< decltype(& std::partition< int*, std::less<int> >) >::value << endl;

		//  Question: Why for the last case we get 'false'?
	}

	// Part 4.1
	{
		cout << "\t Testing some of standard predicates ..." << endl;

		cout << std::is_floating_point< double >::value << endl;
		cout << std::is_floating_point< char >::value << endl;

		cout << std::is_reference< int* >::value << endl;
		cout << std::is_reference< const int& >::value << endl;

		cout << std::is_arithmetic< long long* >::value << endl;
		cout << std::is_arithmetic< const long long >::value << endl;
	}

	return 0;
}
