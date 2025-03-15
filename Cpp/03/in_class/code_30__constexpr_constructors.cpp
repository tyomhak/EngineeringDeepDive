
#include <iostream>
#include <cstdlib>

using std::cin;
using std::cout;
using std::endl;


/// This class represents a 2D point.
///
/// Note, it does really simple things.
struct Point
{
	int _x;  // The coordinates
	int _y;  //

	/// Default constructor
	Point()
		: _x( 0 ), _y( 0 )
		{}

	/// Constructor
	Point( int x_, int y_ )
		: _x( x_ ), _y( y_ )
		{}
};


/// This class represents a 2D point.
/// Differs from previous implementation only by constexpr-constructors.
struct ModernPoint
{
	int _x;  // The coordinates
	int _y;  //

	/// Default constructor
	constexpr ModernPoint()  //   <- note the qualifier
		: _x( 0 ), _y( 0 )
		{}

	/// Constructor
	constexpr ModernPoint( int x_, int y_ )  //   <- note the qualifier
		: _x( x_ ), _y( y_ )
		{}
};


/// Some object which represents one uppercase letter.
struct CustomObject
{
	char _ch;  // Some uppercase letter

	/// Default construcotr
	constexpr CustomObject()  //   <-- Error, cant' work at CT
		: _ch ( 'A' + rand() % 26 )
		{}

	/// Constructor
	constexpr CustomObject( char ch_ )  //   <-- OK, can work at CT if argument is known
		: _ch( ch_ )
		{}
};


int main( int argc, char* argv[] )
{
	// We already know how to create constexpr of primitive types.
	// 
	// Let's do the same with "class" types.
	
	// Part 1.1
	{
		const Point p1;          // OK (point [0,0])
		const Point p2( 5, 3 );  // OK (point [5,3])
	}

	// Part 1.2
	{
		constexpr Point p1;          // Error (why (0,0) is not created?)
		constexpr Point p2( 5, 3 );  // Error (why...?)
	}
	
	// The reason is: 
	//  --> object creation invokes a constructor
	//  --> which is generally a function, 
	//  --> so it might do also tricky things.
	//
	// However...
	//     our constructors are really simple,
	//     which means they can run during compilation.
	
	// Part 2.1
	{
		constexpr ModernPoint p1;          // Works
		constexpr ModernPoint p2( 5, 3 );  // Works
	}

	// Now constructors of "ModernPoint" run at CT,
	//     ... and objects 'p1' and 'p2' become known at CT.
	//
	// Concluding: constexpr-constructor is such constructor, which can 
	//     run during compilation, in case if all its arguments are known 
	//     at CT.

	// Part 2.2
	{
		int i, j;
		cin >> i >> j;

		constexpr ModernPoint p3( i, j );  // Error ([i,j] is not known at CT)
		const ModernPoint p4( i, j );  // OK, constexpr constructor runs at RT
		const Point p5( i, j );  // OK, regular constructor runs at RT
	}

	// This shows that compiler DECIDES if constexpr-constructor can run at CT.
	// If it can't, it will run during RT.

	// Part 3

	// It it not always that a constructor can be declared as "constexpr"
	//
	// Look implementation of "CustomObject"

	// Part 3.1
	{
		// Run this code AFTER changing default constructor to regular.

		CustomObject obj1;  // OK
		const CustomObject obj2;  // OK (known at RT)
		constexpr CustomObject obj3;  // Error (the constructor is not constexpr)
		constexpr CustomObject obj4( 'p' );  // OK (calls the other constructor at CT).
	}

	return 0;
}
