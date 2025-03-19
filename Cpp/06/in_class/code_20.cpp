
#include <iostream>

#include "code_10__ct_sequence.hpp"
#include "code_20__ct_sequence_algorithms.hpp"

using std::cout;
using std::endl;


int main()
{
	// Part 1 (accessing by index)
	{
		typedef ct_sequence< 5, 
					ct_sequence< 72, 
						ct_sequence< 9, 
							ct_sequence< 16, 
								ct_sequence< 24, ct_empty_sequence > > > > > s1;
		cout << "Length of sequence is " << s1::length << endl;
		cout << "Value at '2' is " << ct_at< s1, 2 >::value << endl;
		cout << "Value at '4' is " << ct_at< s1, 4 >::value << endl;
		//cout << "Value at '6' is " << ct_at< s1, 6 >::value << endl;

		cout << endl;
	}

	// Part 2 (printing complete sequences)
	{
		typedef ct_sequence< 7, 
					ct_sequence< 12, 
						ct_sequence< 19, 
							ct_sequence< 63, 
								ct_sequence< 4, ct_empty_sequence > > > > > s1;
		cout << "The first sequence is:";
		ct_printer< s1 >::print();

		typedef ct_sequence< 12, 
					ct_sequence< 14, 
						ct_sequence< 72, 
							ct_sequence< 9, ct_empty_sequence > > > > s2;
		cout << "The second sequence is:";
		ct_printer< s2 >::print();

		cout << endl;
	}

	// Part 3 (trippling the sequence)
	{
		typedef ct_sequence< 6, 
					ct_sequence< 8, 
						ct_sequence< 3, 
							ct_sequence< 1, ct_empty_sequence > > > > a5;
		cout << "The original sequence is:";
		ct_printer< a5 >::print();

		typedef typename ct_tripple< a5 >::type b5;
		cout << "The trippled sequence is:";
		ct_printer< b5 >::print();

		cout << endl;
	}

	return 0;
}
