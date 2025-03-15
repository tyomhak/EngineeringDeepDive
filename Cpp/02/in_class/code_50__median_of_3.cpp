
#include <iostream>


/// Stores "B" if (A, B, C) is strictly increasing, and "0" otherwise.
template< int A, int B, int C >
struct median_of_3_helper
{
	static const int value 
			= (A < B && B < C) ? B : 0;
};

/// Stores median of (A, B, C).
template< int A, int B, int C >
struct median_of_3
{
	static const int value 
			= median_of_3_helper< A, B, C >::value 
					+ median_of_3_helper< A, C, B >::value
					+ median_of_3_helper< B, A, C >::value
					+ median_of_3_helper< B, C, A >::value
					+ median_of_3_helper< C, A, B >::value
					+ median_of_3_helper< C, B, A >::value;
};


// Question: Can we implement non-strict comparison "<=" in the 
//           'median_of_3_helper<>' class template?


int main( int argc, char* argv[] )
{
	using std::cout;
	using std::endl;

	// Part 1.1
	{
		cout << "Median of (5, 6, 4) is : "    << median_of_3< 5, 6, 4 >::value << endl;
		cout << "Median of (10, 19, 16) is : " << median_of_3< 10, 19, 16 >::value << endl;
		cout << "Median of (8, 6, 3) is : "    << median_of_3< 8, 6, 3 >::value << endl;
	}

	// Part 1.2
	{
		int X[ median_of_3< 5, 14, 8 >::value ];

		cout << "Size of 'X' is " << sizeof(X) / sizeof(X[0]) << endl;
	}

	return 0;
}
