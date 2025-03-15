
#include <iostream>

using std::cin;
using std::cout;
using std::endl;


int main( int argc, char* argv[] )
{
	// The "const" keyword states for: 
	//    "can't be changed"
	// However, it can be created & initialized "generally by any value".
	//
	// This makes "const" objects known at RT, but allows to be not known
	// during compilation.

	// Part 1.1
	{
		const int CN = 5;  // OK [known at both CT and RT]

		cin >> CN;  // Error (CN can't be altered)
	}
	
	// Part 1.2
	{
		int N;
		cin >> N;  // Reading into non-const

		const int CN = N;  // OK [not known at CT, known at RT]
	}

	// Part 1.3
	{
		const int CN;  // Error (not assigned during creation)

		cin >> CN;  // Error (CN can't be altered)
	}

	// Let's see how "const" is related with sizes of arrays allocated 
	// on the stack.
	// Recall, those sizes must be known at CT.
	
	// Part 2.1
	{
		int A[ 12 ];  // OK, size of array is known at CT.
	}

	// Part 2.2
	{
		const int CL = 12;  // Known both at CT and RT.
		int A[ CL ];  // OK, size of array is known at CT.
	}

	// Part 2.3
	{
		int L;
		cin >> L;
		const int CL = L;  // OK ('CL' is const, but not known at CT).

		int A[ CL ];  // Error (size of array is not known at CT).
	}

	// Conclusion
	//
	// Some "const int" can be conceptually different from another "const int".
	//

	return 0;
}
