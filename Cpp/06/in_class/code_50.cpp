
#include <iostream>

#include "code_10__ct_sequence.hpp"
#include "code_20__ct_sequence_algorithms.hpp"
#include "code_50__ct_multitype_sequence.hpp"

using std::cout;
using std::endl;


int main()
{
	// Part 7 (multitype sequence)
	{
		typedef ct_multitype_sequence< int, 19, 
					ct_multitype_sequence< long long, 45'674'005'354'012,
						ct_multitype_sequence< char, 'g', 
							ct_multitype_sequence< int, 42, ct_empty_sequence > > > > a1;

		// Printing length
		cout << "Length of the sequence is " << a1::length << endl;

		// Addressing by index
		// Note, we use the same 'ct_at<>' metafunction.
		cout << "Value at index '1' is " << ct_at< a1, 1 >::value << endl;
		cout << "Value at index '2' is " << ct_at< a1, 2 >::value << endl;

		// Printing the sequence
		// Note, we use the same 'ct_printer<>' metafunction.
		ct_printer< a1 >::print();

		cout << endl;
	}

	return 0;
}
