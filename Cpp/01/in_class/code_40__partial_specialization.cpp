
#include <map>
#include <vector>
#include <set>
#include <string>


//
// Classes partial specialization
//

/// A general implementation for mapping.
template< typename FromType, typename ToType >
class mapping
{
	std::map< FromType, ToType > _m;

	// Other members go here...
};

/// Specialization where 'FromType' is integer.
/// Here, we can store everything in an array.
template< typename ToType >
class mapping< int, ToType >
{
	std::vector< ToType > _v;

	// Other members go here...
};

/// Specialization where 'ToType' is boolean.
/// Here we can store everything in 2 sets.
template< typename FromType >
class mapping< FromType, bool >
{
	std::set< FromType > _false_set;
	std::set< FromType > _true_set;

	// Other members go here...
};

#if 0
/// We need this specialization too!
/// Otherwise compiler will not know what to use for "mapping< int, bool >".
template<>
class mapping< int, bool >
{
	// Behavior goes here...
};
#endif


//
// Functions "partial" specialization
//
// Functions can't be partially specialized right now. Instead 
// function OVERRIDING can be used.
//
// If we want to partially "specialize" function, we must ENCAPSULATE it 
// into a funcitonal-object.


/// Definition for the general case.
template< typename OutType, typename InType >
OutType convert( const InType& v )
{
	// Do something interesting here...
	return 0;
}

#if 0
/// A "partial specialization" for boolean result type (NOT ALLOWED).
template< typename InType >
bool convert< bool, InType >( const InType& v )
{
	// Do something differently here
	return false;
}
#endif

/// General implementation of converting as a functor.
/// This can act as a replacement for functions partial specialization.
template< typename OutType, typename InType >
struct converter
{
	OutType operator()( const InType& v ) const
		{ /* Do something interesting here... */ return 0; }
};


int main()
{
	// Part 1
	//

	mapping< std::string, double > m1;  // General mapping

	mapping< int, double > m2;  // First specialization

	mapping< std::string, bool > m3;  // Second specialization

	//mapping< int, bool > m4;  // Be careful here!!

	// Part 2
	//

	// Don't do this way... VVV

	int x1 = 14;
	double y1 = convert< double, int >( x1 );

	int x2 = 32;
	bool y2 = convert< bool, int >( x2 );

	// Do this instead... VVV

	y1 = converter< double, int >()( x1 );

	y2 = converter< bool, int >()( x2 );

	return 0;
}
