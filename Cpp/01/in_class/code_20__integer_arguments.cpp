
#include <random>

//
// Template integer arguments
//

template< int P1, int P2 >
class handler
	{ /* Some implementation here. */ };


// Why not passing 'P1' and 'P2' in constructors at runtime?
// 
// Because sometimes we want 'P1' and 'P2' be known at compile time.


// Static array (resides on stack memory).
template< typename T, int N >
class array
	{ T _data[ N ];  /* Methods of the class... */ };


// One node of Unrolled linked list.
template< typename T, int M >
class unrolled_linked_list_node {
	T _data[ M ];
	int _length;
};


// ToDo: Observe definition of this class... VVV
//
// It uses some large enough prime numbers, which can be known during 
// compilation, in order to speed-up execution.
std::default_random_engine gen;


//
// Template instantiation
//


array< int, 12 > a1;  // Proper instantiation.
array< double > a2;  // Improper instantiation (all arguments must be provided).
