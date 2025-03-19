#include <iostream>


#include "sequence.hpp"


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

// Exercises:
//
// Implement the following metafunctions:
//
//
// 
//



// Advanced exercise:
//
// 1) Implement compile-time Binary search tree, and several metafunctions 
//        for it.
//


// Exercises:
//
// 1) Implement removal of all the values which are of given type 'T'.
//
// 2) Implement filtering of all those values, which are of given type 'T'.


int main()
{
    typedef ct_sequence< 5, 
					ct_sequence< 72, 
						ct_sequence< 9, 
							ct_sequence< 16, 
								ct_sequence< 24, ct_empty_sequence > > > > > s1;

    std::cout << "Count of 9: " << ct_count<s1, 9>::count << std::endl;


    typedef typename ct_sequence_L<4,1,4,2,3,4,5,4, 6>::type s2;
    std::cout << "Count of 4: " << ct_count<s2, 4>::count << std::endl;

    typedef typename ct_pop_front<s2>::type s3;
    std::cout << "Count of 4: " << ct_count<s3, 4>::count << std::endl;

    typedef typename ct_insert<s3, 2, 4>::type s4;
    std::cout << "Count of 4: " << ct_count<s4, 4>::count << std::endl;

    ct_printer<s4>::print();

    typedef typename ct_reverse<s4>::type s5;
    ct_printer<s5>::print();
}