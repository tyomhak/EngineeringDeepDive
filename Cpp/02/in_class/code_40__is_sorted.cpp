
#include <iostream>


// This example shows how several conditions can be concatenated.


/// A template class which checks if "A < B".
template< int A, int B >
struct is_sorted_2
{
	static const bool value = (A < B);
};

/// A template class which checks if "A < B < C".
template< int A, int B, int C >
struct is_sorted_3
{
	static const bool value 
			= is_sorted_2< A, B >::value && is_sorted_2< B, C >::value;
};


// Question: How can we implement 'is_sorted_10<>'? Do we need 8 other 
//           class templates?


int main( int argc, char* argv[] )
{
	using std::cout;
	using std::endl;

	{
		cout << "Is (5, 7, 11) sorted : " << is_sorted_3< 5, 7, 11 >::value << endl;
		cout << "Is (5, 7, 3) sorted : "  << is_sorted_3< 5, 7, 3 >::value << endl;
		cout << "Is (6, 4, 12) sorted : " << is_sorted_3< 6, 4, 12 >::value << endl;
	}

	return 0;
}
