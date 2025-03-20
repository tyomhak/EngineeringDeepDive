#include <iostream>

#include "sequence.hpp"
#include "multitype_sequence.hpp"
#include "bst_template.hpp"


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


int main()
{
	using std::cout;
	using std::endl;

	bool test_sequences = true;
	bool test_multitypes = true;
	bool test_bst = true;

	if (test_sequences)
	{
		cout << "\n=== Sequences ===\n";
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

	// multitype_sequence
	if (test_multitypes)
	{
		cout << "\n=== Multitype Sequences ===\n";
		typedef ct_multitype_sequence< int, 19, 
					ct_multitype_sequence< long long, 45'674'005'354'012,
						ct_multitype_sequence< char, 'g', 
							ct_multitype_sequence< int, 42, ct_empty_sequence > > > > a1;

		print<a1>();
		
		typedef typename ct_remove_t<a1, int>::type a2;
		cout << "remove ints\n";
		print<a2>();

		cout << "filter ints\n";
		typedef typename ct_filter_t<a1, int>::type a3;
		print<a3>();
	}

	// Binary Search Tree 
	if (test_bst)
	{
		cout << "\n=== Binary Search Tree ===\n";
		typedef ct_node<5> t1;
		typedef typename insert_node<t1, 10>::type t2;
		typedef typename insert_node<t2, 1>::type t3;
		typedef typename insert_node<t3, 7>::type t4;
		typedef typename insert_node<t4, 3>::type t5;

		cout << "Min: " << min_value<t5>::value << endl;
		cout << "Max: " << max_value<t5>::value << endl;


		cout << "\n\n";
		node_printer<t5>::print();
		
		typedef typename find_node<t5, 7>::type t6;
		cout << t6::value << endl;
	}
}