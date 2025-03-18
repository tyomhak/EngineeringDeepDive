
#include <string>
#include <iostream>


/// Declaration of static array.
template< typename T, int Capacity >
class static_array {};

/// Declaration of Circular buffer.
template< typename T, int Capacity >
class circular_buffer {};

/// Declaration of Unrolled linked list
template< typename T, int Capacity >
class unrolled_linked_list {};


/// The general case of evaluator class.
template<
		template< typename, int > class CONT, 
		int... Sizes >
struct performance_evaluator
{
	static_assert( false, 
			"General case of 'performance_evaluator' class template should"
			" not be instantiated." );
};

/// Its specialization for at least 1-long list of Sizes.
template<
		template< typename, int > class CONT, 
		int Size1, int... Sizes >
struct performance_evaluator< CONT, Size1, Sizes... >
{
	void measure() {
		CONT< int, Size1 > c1;
		// ... run 'c1'

		CONT< double, Size1 > c2;
		// ... run 'c2'

		CONT< std::string, Size1 > c3;
		// ... run 'c3'

		// Continue with remaining sizes :-)
		performance_evaluator< CONT, Sizes... > inner_evaluator;
		inner_evaluator.measure();
	}
};

/// Its specialization list of Sizes becomes exhausted.
template<
		template< typename, int > class CONT >
struct performance_evaluator< CONT >
{
	void measure()
		{}  // Do nothing here.
};


int main( int argc, char* argv[] )
{
	performance_evaluator< static_array, 15, 50, 250 > ev1;
	ev1.measure();

	performance_evaluator< circular_buffer, 25, 75, 250, 750 > ev2;
	ev2.measure();

	performance_evaluator< unrolled_linked_list, 10, 20, 30, 40 > ev3;
	ev3.measure();

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
