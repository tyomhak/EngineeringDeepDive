
#include <string>


/// Declaration of static array.
template< typename T, int Capacity >
class static_array {};

/// Declaration of Circular buffer.
template< typename T, int Capacity >
class circular_buffer {};

/// Declaration of Unrolled linked list
template< typename T, int Capacity >
class unrolled_linked_list {};


/// This function measures performance of contianer template 'CONT'.
template< 
		template< typename, int > class CONT >
void measure_performance()
{
	// Measure suite 1
	CONT< int, 15 > c1;
	//
	// ... some tests on 'c1'

	// Measure suite 2
	CONT< int, 2500 > c2;
	//
	// ... some tests on 'c2'

	// Measure suite 3
	CONT< double, 750 > c3;
	//
	// ... some tests on 'c3'

	// Measure suite 4
	CONT< std::string, 150 > c4;
	//
	// ... some tests on 'c4'
}


int main( int argc, char* argv[] )
{
	measure_performance< static_array >();

	measure_performance< circular_buffer >();

	measure_performance< unrolled_linked_list >();

	return 0;
}


// Exercises:
//
// 1) In function "measure_performance()" provide also sizes of containers, as a variadic list 
//    of integers. Make the function to instantiate provided conatiner with all those sizes.
// 
// 2) In function "measure_performance()" provide also types of elements of the containers, 
//    as a variadic sequence of types integers. Make the function to instantiate provided 
//    conatiner with all those sizes.
// 
// 3) [*] Provide both variadic lists: list of 'M' sizes, and list of 'N' types. Make the
//    function "measure_performance()" to do "M*N" instantiations.
//
