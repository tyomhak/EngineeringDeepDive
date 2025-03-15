
#include <iostream>
#include <random>

using std::cin;
using std::cout;
using std::endl;


// Constexpr constructor means such constructor, which can RUN at CT,
//
// Any constructor is also a function.
//
// What can't we have functions which also can run at CT?
//
// We actually can, and the rules are the same. To run at CT:
//    --> all arguments must be known at CT,
//    --> the function must be "simple enough".


/// This function can run during compilation.
constexpr int sum3( int a, int b, int c )  //   <-- note the qualifier
{
	return a + b + c;
}


/// This function can not be calculated at CT.
constexpr int rand_1_10()  //  <-- Error here, "rand()" can't run at CT
{
	return rand() % 10 + 1;
}


/// A more complex function, which runs during CT.
constexpr int factorial_iterative( int N )
{
	int result = 1;
	for ( int i = 2; i <= N; ++i )  // We can even run loops during compilation
		result *= i;
	return result;
}

/// A recursive function, which runs during CT.
constexpr int factorial_recursive( int N )  //   <-- note the qualifier
{
	if ( N <= 1 )
		return 1;
	else
		return N * factorial_recursive( N-1 );  // And even have recursive calls
}


// Let's note, all this means that the language compiler can actually:
//    1) compile some code,
//    2) run it during compilation,
//    3) based on results, compile some other code.


// Question: Bring few examples of functions which CAN be declared as constexpr, 
//     and the ones which CAN'T.


// This refers also to methods of classes, as those are the same functions, 
// taking one extra "this" argument.
//
// In order for them to run at CT, "*this" should also be known at that time.


/// This class represents a 2D point.
/// Differs from previous implementation only by constexpr-constructors.
struct ModernPoint
{
	int _x;  // The coordinates
	int _y;  //

	/// Default constructor
	constexpr ModernPoint()
		: _x( 0 ), _y( 0 )
		{}

	/// Constructor
	constexpr ModernPoint( int x_, int y_ )
		: _x( x_ ), _y( y_ )
		{}

	/// Returns square of length of the vector.
	constexpr int length_2() const  //   <- note the qualifier
		{ return _x*_x + _y*_y; }

	/// Returns another point, twice farther from zero-point.
	constexpr ModernPoint doubled() const  //   <- note the qualifier
		{ return ModernPoint( _x*2, _y*2 ); }

	/// Comparison operators
	constexpr bool operator==( const ModernPoint& rhs ) const
		{ return _x == rhs._x && _y == rhs._y; }
	constexpr bool operator!=( const ModernPoint& rhs ) const
		{ return ! (*this == rhs); }

	/// Rotates this point by '90' degrees CCW.
	constexpr void rotate() {
		int new_x = -_y;  // Calculate new coordinates
		int new_y = _x;   //
		_x = new_x;  // Remember them
		_y = new_y;  //
	}

	/// Returns copy of this point, rotated by "alpha" angle CCW.
	ModernPoint rotated( float alpha ) const {
		int new_x = _x*cos( alpha ) - _y*sin(alpha);
		int new_y = _x*sin(alpha) + _y*cos(alpha);
		return ModernPoint( new_x, new_y );
	}
};


// Note that ALMOST ALL functions of "ModernPoint" are declared as "constexpr".
//
// We can see that majority of functions and methods in STL are also 
//    declared that way.


// Also let's point that "constexpr" function is NOT RELATED to "const" function.
//
// When working with variables, "constexpr" imposes "const",
//
// But with methods we have 4 possible scenarios:
//   - constexpr const method
//   - regular const method
//   - constexpr non-const method
//   - regular non-const method
//
// ... because altering "*this" object is not related to running the code at CT.


/// This function can't be declared as constexpr.
constexpr ModernPoint generate(   //   <-- Error, can't run at CT
		int x_min, int x_max, 
		int y_min, int y_max, 
		std::default_random_engine& gen )
{
	std::uniform_int_distribution<> x_dist( x_min, x_max );
	std::uniform_int_distribution<> y_dist( y_min, y_max );
	int x = x_dist( gen );
	int y = y_dist( gen );
	return ModernPoint( x, y );
}


// Question: Why "ModernPoint::rotated()" method is not declared as "constexpr"?


int main( int argc, char* argv[] )
{
	// Part 1.1
	{
		int A[ sum3( 6, 7, 8 ) ];  // OK

		int B[ 6 + 7 + 8 ];  // OK in every standard
	}

	// Part 1.2
	{
		int A[ rand_1_10() ];  // Error (not known at CT).

		const int L = rand_1_10();  // OK, known at RT.
	}

	// Part 1.3
	{
		int B[ factorial_iterative( 5 ) ];  // OK (loop works during CT).
	}

	// Part 1.4
	{
		int B[ factorial_recursive( 5 ) ];  // OK (recursion works during CT).
	}

	// Conclusion:
	// 
	// Mentioned functions will run in CT.

	// Part 2
	
	// Part 2.1
	{
		constexpr ModernPoint p1( 5, 3 );
		int A[ p1.length_2() ];  // The size will be "5^2 + 3^2 = 34"
	}

	// Part 2.2
	{
		constexpr ModernPoint p1( 5, 3 );
		constexpr ModernPoint p2( 10, 6 );

		int A[ 
				p1.doubled() == p2
				? 10 
				: 16 ];  // Some complex calculation, result is "10".
	}

	// Part 3

	std::default_random_engine gen;

	// Part 3.1
	{
		constexpr ModernPoint p1 = generate( 0, 10, 0, 10, gen );  // Error here
		const ModernPoint p2 = generate( 0, 10, 0, 10, gen );  // OK, known at RT
	}

	return 0;
}
