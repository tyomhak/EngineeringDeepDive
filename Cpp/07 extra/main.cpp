
#include <iostream>

#include "code_10__placeholders.hpp"

#include "solution_50__variadic_placeholders.hpp"


// "x+y < 12-x"
template< int X, int Y >
using formula_1 = typename less< 
		typename plus< _1, _2 >::t, 
		typename minus< typename constant<12>::t, _1 >::t >::t< X, Y >;


int main( int argc, char* argv[] )
{
	// Binders vs. placeholders
	{
		// The expression is "x%5 != 0"
#if 0
		// The expression with binders:
		typename ct_unary_negate< 
				typename ct_bind2nd< 
						ct_is_divisible, 5 >::result_type >::result_type;

		// The expression with placeholders
		ct_not< ct_mod< _1, constant<5> >::v >::v;
#endif
		/// 

		// Another expression is "x+7 < 2*y"
#if 0
		// The expression with binders
		typename ct_less< 
				typename ct_bind2nd< 
						ct_plus,
						7 >::result_type, 
				typename ct_bind1st< 
						2, 
						ct_multiply >::result_type 
				>::result_type;  // Incomplete, as 'x' and 'y' are not specified.

		// The expression with placeholders
		ct_less< 
				ct_plus< _1, constant<7> >::v, 
				ct_multiply< constant<2>, _2 >::v >::v;
#endif
	}
	
	// Part 1 (introducing placeholders)
	std::cout << "\t Simple expressions with placeholders ..." << std::endl;
	{
		std::cout << "5 + 8 = " 
				<< plus< _1, _2 >::t< 5, 8 >::value
				<< std::endl;

		std::cout << "(7 < 10)  -->  "
				<< less< _1, _2 >::t< 7, 10 >::value
				<< std::endl;

		// Same with reverse order of arguments
		std::cout << "(7 < 10)  -->  "
				<< less< _2, _1 >::t< 10, 7 >::value
				<< std::endl;

		// A placeholder used more than once
		std::cout << "14*2 = 14 + 14 = "
				<< plus< _1, _1 >::t< 14, 0 >::value
				<< std::endl;
	}

	// Part 2 (continuing placeholders)
	std::cout << "\t More complex expressions with placeholders ..." << std::endl;
	{
		// "x + 7 < y"
		std::cout << "1 + 7 < 5  -->  "
				<< less< 
						plus< _1, constant< 7 >::t >::t, 
						_2 >::t< 1, 5 >::value << std::endl;
		std::cout << "1 + 7 < 15  -->  "
				<< less< 
						plus< _1, constant< 7 >::t >::t, 
						_2 >::t< 1, 15 >::value << std::endl;
	}

	// Part 3 (constructing formulas)
	std::cout << "\t Separating expressions from their calculation ..." << std::endl;
	{
		std::cout << "'x + y < 12 - x' : [4, 1]  -->  "
				<< formula_1< 4, 1 >::value 
				<< std::endl;
		std::cout << "'x + y < 12 - x' : [8, 1]  -->  "
				<< formula_1< 8, 1 >::value 
				<< std::endl;
	}

	// Part 4 (shorter syntax for constants)
	std::cout << "\t Making the syntax shorter ..." << std::endl;
	{
#if 0
		std::cout << "'x + 14' : [8]  -->  "
				<< plus< _1, 14 >::t< 8, 0 >::value << std::endl;

		std::cout << "'1 + y' : [12]  -->  "
				<< plus< 1, _2 >::t< 0, 12 >::value << std::endl;
#endif
	}

	// Part 5 (using arbitrary number of variables)
	std::cout << "\t Using arbitrary number of variables ..." << std::endl;
	{
		// 'x + y < z'
		std::cout << "'x + y < z' : [3, 4, 9]  -->  "
				<< less_v< 
						plus_v< __<1>::t, __<2>::t >::t, 
						__<3>::t >::t< 3, 4, 9 >::value 
				<< std::endl;
		std::cout << "'x + y < z' : [8, 7, 9]  -->  "
				<< less_v< 
						plus_v< __<1>::t, __<2>::t >::t, 
						__<3>::t >::t< 8, 7, 9 >::value 
				<< std::endl;
	}

	return 0;
}
