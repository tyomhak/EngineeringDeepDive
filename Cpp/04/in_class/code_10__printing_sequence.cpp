
#include <iostream>

/// Ordinary implementation of printing function.
template< typename T1, typename T2, typename T3 >
void print_regular( const T1& arg1, const T2& arg2, const T3& arg3 )
{
	std::cout << " " << arg1 << " " << arg2 << " " << arg3 << std::endl;
}


// Now comes imlementation with variadic templates.


/// The exit branch, when parameters pack becomes empty.
/// Note, exit branch must PRECEED the general case. This is 
/// not a specialization.
void print()
{
	std::cout << std::endl;
}

/// This function prints to console all the provided arguments.
template< typename HeadType, typename... Types >
void print( const HeadType& head, Types... body )
{
	std::cout << " " << head;
	print( body... );
}


// Note, parameters pack can also be empty.
//
// Let's do an altered implementation, when we print 2 values at a time.


/// The exit branch, when parameters pack becomes empty.
/// Note, exit branch must PRECEED the general case. This is 
/// not a specialization.
void print_by_2()
{
	std::cout << std::endl;
}

/// This function prints to console all the provided arguments.
template< typename FirstType, typename SecondType, typename... Types >
void print_by_2( const FirstType& first, const SecondType& second, Types... body )
{
	std::cout << " " << first << " " << second;
	print_by_2( body... );
}


// Another example, where parameters pack is integers sequence.
//    Recall, integers also can be used as template arguments.


template< int TailValue >
void print_integers()
{
	std::cout << " " << TailValue << std::endl;
}

template< int Value1, int Value2, int... Values >
void print_integers()
{
	std::cout << " " << Value1;
	print_integers< Value2, Values... >();
}


// Note:
//
// Parameters pack can be empty, which might cause ambiguity.
//
// Compiler doesn't allow us having 'print_integers()' with no template arguments
//     (it confuses that with specialization, which is not allowed for functions).
//
// This is why we are forced to do the trick with 2 head values.
//
// Also, we imitate another parameters pack there.


int main( int argc, char* argv[] )
{
	// Part 1.1
	{
		print( 12, "ABC", 9.8 );
		print( 8.2, 'x', 'y', "variance" );
	}

	// Part 1.2
	{
		// print_by_2( 12, "ABC", 9.8 );  <-- This causes error...   Why?
		print_by_2( 8.2, 'x', 'y', "variance" );
	}

	// Part 2
	{
		std::cout << "Sequence 1:";
		print_integers< 8, 12, 9 >();

		std::cout << "Sequence 2:";
		print_integers< 7, 61, 4, 27 >();
	}

	return 0;
}
