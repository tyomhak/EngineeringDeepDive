
#include <iostream>


// Let's see if conditions also can be executed during compilation.


/// This is a helper class for maximal calculation.
template< bool Cond, int A, int B >
struct maximal_helper
{
	static const int value = -1;  // Just some dummy value here
};

/// The specialization for case when "A < B"
template< int A, int B >
struct maximal_helper< true, A, B >
{
	static const int value = B;  // 'B' is maximal then.
};

/// The specialization for case when "A >= B"
template< int A, int B >
struct maximal_helper< false, A, B >
{
	static const int value = A;  // 'A' is maximal then.
};

/// Calculates maximal between 'A' and 'B' during compilation.
template< int A, int B >
struct maximal
{
	static const int value
			= maximal_helper< (A<B), A, B >::value;
};


// Question: Can we omit the general case of 'maximal_helper<>' template?

// Question: Can we implement "maximal<>" with just 1 template declaration?


int main( int argc, char* argv[] )
{
	using std::cout;
	using std::endl;

	// Part 1.1
	{
		cout << "maximal(3, 7) = "   << maximal< 3, 7 >::value << endl;
		cout << "maximal(14, 11) = " << maximal< 14, 11 >::value << endl;
	}

	// Part 1.2
	{
		int A[ maximal< 16, 24 >::value ];  // Size of the array is '24'.

		cout << "Size of the array is " 
				<< sizeof(A) / sizeof(A[0]) << endl;
	}

	return 0;
}
