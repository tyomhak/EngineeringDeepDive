
#include <iostream>
#include <vector>

using std::cout;
using std::endl;


// How to get double-precision integer types?
// Such types can be used as intermediate results, when 
// implementing multiplication.


/// This template class holds if the argument class is capable of 
/// storing real values.
template< typename NumberType >
struct doubled_precision
{
	typedef NumberType type;  // By default we keep the same type.
};

// List of specializations for built-in types.
template<>
struct doubled_precision< char >
	{ typedef short type; };

template<>
struct doubled_precision< short >
	{ typedef int type; };

template<>
struct doubled_precision< int >
	{ typedef long long type; };


/// A custom big-integer class, which keeps 'Bits' binary digits.
template< unsigned int Bits >
class my_big_integer
{
	// Some implementation here
	//
	//
};

// Custom specialization here
template< unsigned int Bits >
struct doubled_precision< my_big_integer< Bits > >
	{ typedef my_big_integer< 2 * Bits > type; };


/// This template removes pointer from the provided type 'T'.
template< typename T >
struct remove_pointer
	{ typedef T type; };  // Default implementation does nothing.

/// Specialization for pointer types.
template< typename Q >
struct remove_pointer< Q* >
	{ typedef Q type; };


#include <type_traits>
		// There are multiple type conversions in STL, started from the 
		// latest standards.
		// See few examples below... VV


// Note, manipulations with values (made in previous section) could also 
// be made during runtime.
// But manipulations with types must be made at CT.


int main( int argc, char* argv[] )
{
	// Part 1.1
	{
		doubled_precision< int >::type temp;  // 'temp' is "long long"
	}

	// Part 1.2
	{
		doubled_precision< float >::type temp;  // 'temp' is "float"
	}

	// Part 2.1
	{
		doubled_precision< my_big_integer< 100 > >::type temp;
				// 'temp' is "my_big_integer< 200 >"
	}

	// Part 3.1
	{
		typedef remove_pointer< int* >::type int_t;
		static_assert( 
				std::is_same< int, int_t >::value, 
				"Must be same..." );

		typedef remove_pointer< char** >::type char_ptr;
		static_assert( 
				std::is_same< char*, char_ptr >::value, 
				"Must be same..." );

		typedef remove_pointer< std::vector<int*> >::type vec_int_t;
		static_assert( 
				std::is_same< std::vector<int*>, vec_int_t >::value,
				"Must be same..." );
	}

	// Part 3.2
	{
		typedef std::add_pointer< int >::type int_ptr;
		static_assert( 
				std::is_same< int*, int_ptr >::value, 
				"Must be same..." );

		typedef std::remove_reference< float& >::type float_t;
		static_assert( 
				std::is_same< float, float_t >::value,
				"Must be same..." );

		typedef std::add_const< float >::type c_float;
		static_assert( 
				std::is_same< const float, c_float >::value,
				"Must be same..." );
	}

	return 0;
}
