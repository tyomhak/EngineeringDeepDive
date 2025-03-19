
#include <iostream>

#include "code_10__ct_sequence.hpp"
#include "code_20__ct_sequence_algorithms.hpp"
#include "code_30__ct_sequence_builder.hpp"
#include "code_40__sequence_algoritums_2.hpp"

using std::cout;
using std::endl;


int main()
{
	// Part 5 (prepending values)
	{
		typedef typename ct_sequence_4< 5, 14, 13, 6 >::type b1;
		cout << "The original sequence is:";
		ct_printer< b1 >::print();

		typedef typename ct_push_front< b1, 4 >::type b2;
		cout << "The sequence after prepending '4' is:";
		ct_printer< b2 >::print();

		typedef typename ct_push_front< ct_empty_sequence, 6 >::type c2;
		cout << "Prepending '6' to empty sequence results in:";
		ct_printer< c2 >::print();

		cout << endl;
	}

	// Part 6 (filtering)
	{
		typedef typename ct_sequence_4< 5, 14, 13, 6 >::type a1;
		cout << "The original sequence is:";
		ct_printer< a1 >::print();

		typedef typename ct_remove< a1, 14 >::type b1;
		cout << "The sequence after removing '14' is:";
		ct_printer< b1 >::print();

		//

		typedef typename ct_sequence_3< 8, 1, 8 >::type a2;
		cout << "The original sequence is:";
		ct_printer< a2 >::print();

		typedef typename ct_remove< a2, 8 >::type b2;
		cout << "The sequence after removing '8' is:";
		ct_printer< b2 >::print();

		//

		typedef typename ct_sequence_4< 5, 9, 1, 6 >::type a3;
		cout << "The original sequence is:";
		ct_printer< a3 >::print();

		typedef typename ct_remove< a3, 8 >::type b3;
		cout << "The sequence after removing '8' is:";
		ct_printer< b3 >::print();

		cout << endl;
	}

	// Part 9 (trippling every 2nd value)
	{
		typedef typename ct_sequence_5< 5, 1, 6, 12, 9 >::type b1;
		cout << "The 5-long sequence is:";
		ct_printer< b1 >::print();

		typedef typename ct_tripple_every_2nd< b1 >::type b2;
		cout << "The sequence after trippling every 2nd value:";
		ct_printer< b2 >::print();

		typedef typename ct_tripple_every_2nd< b1, false >::type b3;
		cout << "The sequence after trippling every 2nd value, starting from 2nd:";
		ct_printer< b3 >::print();

		cout << endl;
	}

	// Part 10 (difference series, method 1)
	{
		typedef typename ct_sequence_5< 8, 3, 12, 1, 6 >::type c1;
		cout << "The 5-long original sequence is:";
		ct_printer< c1 >::print();

		typedef typename ct_difference_sequence_1< c1 >::type c2;
		cout << "The difference sequence is:";
		ct_printer< c2 >::print();

		typedef typename ct_difference_sequence_1< c2 >::type c3;
		cout << "The d^2 sequence is:";
		ct_printer< c3 >::print();

		cout << endl;
	}

	// Part 11 (difference series, method 2)
	{
		typedef typename ct_sequence_5< 8, 3, 12, 1, 6 >::type c1;
		cout << "The 5-long original sequence is:";
		ct_printer< c1 >::print();

		typedef typename ct_difference_sequence_2< c1 >::type c2;
		cout << "The difference sequence is:";
		ct_printer< c2 >::print();

		typedef typename ct_difference_sequence_2< c2 >::type c3;
		cout << "The d^2 sequence is:";
		ct_printer< c3 >::print();

		cout << endl;
	}

	return 0;
}
