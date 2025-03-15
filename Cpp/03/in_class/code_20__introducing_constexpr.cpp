
#include <iostream>

using std::cin;
using std::cout;
using std::endl;


/// Calculates factorial of 'N'
int factorial( int N )
{
	if ( N <= 1 )
		return 1;
	else
		return N * factorial( N-1 );
}


int main( int argc, char* argv[] )
{
	// Part 1: "const" vs. "constexpr"
	
	// Part 1.1
	{
		const int C_N = 7;  // OK (known both at CT and RT).
		constexpr int CE_N = 7;  // OK (known both at CT and RT).
	}

	// Part 1.2
	{
		int N;
		cin >> N;

		const int C_N = N;  // OK ('C_N' is const, but not known at CT).
		constexpr int CE_N = N;  // Error ('CE_N' is not known at CT).
	}

	// Part 1.3
	{
		constexpr int CE_N = 5*2 + 6;

		int A[ CE_N ];  // OK ('CN' is known at CT).
	}

	// Conclusion
	//
	// 'constexpr' means also 'const', but not vice-versa.
	// So 'constexpr' is more strict than 'const'.
	
	// Question: Can we assign a "const int" to "constexpr int"?
	//
	// Question: Can we assign a "constexpr int" to "const int"?

	// Part 2:
	// 
	// Let's do a but more complex things...
	
	// Part 2.1
	{
		const int fact5 = factorial( 5 );  // OK, "fact_5 = 120"
	}

	// Part 2.2
	{
		constexpr int fact5 = factorial( 5 );  // Error (why we can't have "fact_5 = 120"?)
	}

	// It looks like "factorial()" function does simple things...
	//
	// Why know its result for any argument, why can't we take it?

	return 0;
}
