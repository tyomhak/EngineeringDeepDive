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

template<typename T>
void print()
{
	ct_printer<T>::print();
	std::cout << "\n";
}


// Advanced exercise:
// 1) Implement compile-time Binary search tree, and several metafunctions 
//        for it.


// Exercises:
//
// 1) Implement removal of all the values which are of given type 'T'.
//
// 2) Implement filtering of all those values, which are of given type 'T'.


int main()
{
	using std::cout;
	using std::endl;

    typedef ct_sequence< 5, 
					ct_sequence< 72, 
						ct_sequence< 9, 
							ct_sequence< 16, 
								ct_sequence< 24, ct_empty_sequence > > > > > s1;

	print<s1>();
    cout << "Count of 9: " << ct_count<s1, 9>::count << "\n\n";

	typedef typename ct_sequence_6<1,2,3,4,5,6>::type s1_1;
	print<s1_1>();

    typedef typename ct_sequence_L<4,1,4,2,3,4,5,4, 6>::type s2;
	print<s2>();

    typedef typename ct_pop_front<s2>::type s3;
	cout << "pop front\n";
	print<s3>();

    typedef typename ct_insert<s3, 2, 4>::type s4;
	cout << "insert 4 at index 2\n";
	print<s4>();

    typedef typename ct_reverse<s4>::type s5;
	cout << "reversed: \n";
    print<s5>();

	typedef typename ct_erase<s5, 3>::type s6;
	cout << "erase at index 3\n";
	print<s6>();

	constexpr auto max = ct_max_element<s6>::value;
	cout << "Max: " << max << endl;

	typedef typename ct_push_back<s6, 10>::type s7;
	cout << "push_back 10\n";
	print<s7>();

	typedef typename ct_sequence_L<1,2,3,4,5,8>::type s8;
	cout << "\nNew Sorted Seq\n";
	print<s8>();
	typedef typename ct_insert_to_sorted<s8, 7>::type s9;
	cout << "Insert into sorted 7\n";
	print<s9>();


	cout << "Sorting V\n";
	print<s7>();
	typedef typename ct_insertion_sort<s7>::type s10;
	cout << "Sorted:\n";
	print<s10>();
}