
#include <iostream>

using std::cout;
using std::endl;


/// The template class for Fibonacci values calculation.
///
/// First items of Fibonacci sequence are:
///    0   1   2   3   4   5   6   7   8  ...
///    1   1   2   3   5   8  13  21  34  ...
/// 
template< unsigned int N >
struct fibonacci
{
	static const unsigned int value 
			= fibonacci< N-1 >::value + fibonacci< N-2 >::value;
};

/// Here we need 2 specializations:
/// Specialization for "fib(0) = 1",
template<>
struct fibonacci< 0 >
{
	static const unsigned int value = 1;
};

/// Specialization for "fib(1) = 1".
template<>
struct fibonacci< 1 >
{
	static const unsigned int value = 1;
};


// This illustrates how run-time loops can be replaced with compile-time 
// template instantiation mechanism.


int main( int argc, char* argv[] )
{
	// Part 1.1
	{
		cout << "fib(5) = " << fibonacci< 5 >::value << endl;
	}

	// Part 1.2
	{
		int A[ fibonacci< 6 >::value ];  // Size of the array is '13'.

		cout << "Size of the array is " 
				<< sizeof(A) / sizeof(A[0]) << endl;
	}

	return 0;
}
