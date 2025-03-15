
#include <iostream>


// Initially templates were introdced to reduce code duplication.
//
// Then, it becomes clear that templates can be used to do calculations 
// at compile time.


/// The template class for factorial calculation.
template< unsigned int N >
struct factorial
{
	static const unsigned int value = N * factorial< N-1 >::value;
};

/// Specialization for "0! = 1".
template<>
struct factorial< 0 >
{
	static const unsigned int value = 1;
};


int main( int argc, char* argv[] )
{
	using std::cout;
	using std::endl;

	// Part 1.1
	{
		cout << "5! = " << factorial< 5 >::value << endl;
	}

	// Part 1.2
	{
		int A[ factorial< 4 >::value ];  // Size of the array is '24'.

		cout << "Size of the array is " 
				<< sizeof(A) / sizeof(A[0]) << endl;
	}

	return 0;
}
