
#ifndef EDD_CPP__CT_SEQUENCE_ALGORITHMS_HPP
#define EDD_CPP__CT_SEQUENCE_ALGORITHMS_HPP

#include <iostream>


// We need only forward declaration for empty sequence here.
struct ct_empty_sequence;


// We can access element of such array by index:
//
//    ... and even catch overflows.


/// This metafunction returns value of 'Sequence' at position 'Index'.
template< typename Sequence, unsigned int Index >
struct ct_at
{
	/// Value of 'Sequence' at 'Index'.
	static constexpr auto value = ct_at<
			typename Sequence::body_type, 
			Index - 1 >::value;
};

/// Specialization for "Index == 0".
template< typename Sequence >
struct ct_at< Sequence, 0 >
{
	/// Value at index '0' is always the head.
	static constexpr auto value = Sequence::head;
};

/// Specialization for cases of overflow.
/// Overflow happens when "Index >= Sequence::length".
template< unsigned int Index >
struct ct_at< ct_empty_sequence, Index >
{
	static_assert( 
			false, 
			"'ct_sequence' overflow inside 'ct_at<>'." );
};


// As content of any 'ct_sequence' is known at compile time, there is NO NEED 
// to instantiate any object of it. That's why there we use only:
//  * typedefs, and
//  * static constexpr fields.


// Another simplest operation is to print all values of the sequence.


/// This class prints values of provided compile-time sequence
/// to the screen.
template< typename Sequence >
struct ct_printer
{
	static void print() {
		// Print the head value
		std::cout << " " << Sequence::head;
		// Delegate printing of body to another class
		typedef ct_printer< typename Sequence::body_type > body_printer;
		body_printer::print();
	}
};

/// Specialization of "ct_printer" class for empty sequence.
template<>
struct ct_printer< ct_empty_sequence >
{
	static void print() {
		std::cout << std::endl;  // Just move to new line
	}
};


// We can implement not only accessor metafunctions, but also modificators.


/// Metafunction which tripples each entry of provided sequence.
template< typename Sequence >
struct ct_tripple
{
	typedef ct_sequence< 
			Sequence::head * 3, 
			typename ct_tripple< typename Sequence::body_type >::type > type;
};

/// The "exit branch" for trippling algorithm.
template<>
struct ct_tripple< ct_empty_sequence >
{
	typedef ct_empty_sequence type;
};


// Note, how "type" is used there, and not the metafunction itself... ^^^


// Exercises:
// 
// 1) Write a metafunction for counting number of occurrences of given 
//     value 'Y', in provided sequence.


#endif // EDD_CPP__CT_SEQUENCE_ALGORITHMS_HPP
