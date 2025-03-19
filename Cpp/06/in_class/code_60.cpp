
#include <iostream>

#include "code_10__ct_sequence.hpp"
#include "code_20__ct_sequence_algorithms.hpp"
#include "code_30__ct_sequence_builder.hpp"
#include "code_60__ct_functional.hpp"


/// A metafunction for checking if "X < 10".
template< int X >
struct less_than_10
	{ static constexpr bool value = (X < 10); };

/// A metafunction for checking if 'X' is odd.
template< int X >
struct is_odd
	{ static constexpr bool value = (X % 2); };

// Predicate for checking if "X < 15".
// Here we introduce a new type name, and MUST do that in global scope.
// This is allowed only in cpp0x and later standards.
template< int X >
using less_than_15 = typename ct_bind2nd< ct_less, 15 >::result_type< X >;

// Predicate for checking if "X < 30".
// Here we introduce a new type name, and MUST do that in global scope.
// This is allowed only in cpp0x and later.
template< int X >
using less_than_30 = ct_less< X, 30 >;


/// A metafunction for checking that 'X' is not divisible over 5.
template< int X >
struct is_not_divisible_over_5
	{ static constexpr bool value = (X % 5 != 0); };

/// A metafunction for checking that 'X' is divisible over 5.
template< int X >
struct is_divisible_over_5
	{ static constexpr bool value = (X % 5 == 0); };


using std::cout;
using std::endl;

int main( int argc, char* argv[] )
{


	// Part 12 (duplication of certain values)
	{
		typedef typename ct_sequence_5< 8, 12, 17, 9, 6 >::type a1;
		cout << "The original sequence is:";
		ct_printer< a1 >::print();

		typedef typename ct_duplicate_if< a1, less_than_10 >::type a2;
		cout << "The duplicated sequence upon (x < 10) is:";
		ct_printer< a2 >::print();

		typedef typename ct_duplicate_if< a1, is_odd >::type a3;
		cout << "The duplicated sequence upon oddness is:";
		ct_printer< a3 >::print();

		cout << endl;
	}

	// Part 13 (duplication of certain values, using generic predicates)
	{
		typedef typename ct_sequence_5< 5, 39, 64, 14, 22 >::type a1;
		cout << "The original sequence is:";
		ct_printer< a1 >::print();

		//   ... note, here we don't introduce new type name.
		typedef typename ct_duplicate_if< 
				a1,
				typename ct_bind2nd< ct_less, 50 >::result_type >::type a3;
		cout << "The duplicated sequence upon (x < 50) is:";
		ct_printer< a3 >::print();

		//   ... here we need to introduce new type name.
		typedef typename ct_duplicate_if< 
				a1,
				less_than_15 >::type a2;
		cout << "The duplicated sequence upon (x < 15) is:";
		ct_printer< a2 >::print();

		//   ... here also we need to introduce new type name.
		typedef typename ct_duplicate_if< 
				a1,
				less_than_30 >::type a4;
		cout << "The duplicated sequence upon (x < 30) is:";
		ct_printer< a4 >::print();

		std::cout << std::endl;
	}

	// Part 14 (duplicating values, not divisible over 5)
	{
		typedef typename ct_sequence_5< 8, 15, 32, 14, 20 >::type b1;
		cout << "The original sequence is:";
		ct_printer< b1 >::print();

		// ... trivial duplication
		typedef typename ct_duplicate_if< 
				b1,
				is_not_divisible_over_5 >::type b2;
		cout << "The trivial duplication for (x%5!=0) is:";
		ct_printer< b2 >::print();

		// ... implementation with negating
		typedef typename ct_duplicate_if< 
				b1,
				typename ct_unary_negate< is_divisible_over_5 >::result_type >::type b3;
		cout << "The duplication (with negation) for (x%5!=0) is:";
		ct_printer< b3 >::print();

		// ... implementation with binding and negating
		typedef typename ct_duplicate_if< 
				b1,
				typename ct_unary_negate< 
						typename ct_bind2nd< ct_is_divisible, 5 >::result_type >::result_type >::type b4;
		cout << "The duplication (with binding and negation) for (x%5!=0) is:";
		ct_printer< b4 >::print();

		// ... implementation with negating and binding
		//
		//
		//
	}

	return 0;
}
