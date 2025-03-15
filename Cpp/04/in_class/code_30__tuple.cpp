
#include <utility>
#include <string>
#include <iostream>


//
// Trivial solutions for kkeping 3 or more items.
// 

void dont_do_this_way()
{
	typedef std::pair< std::pair< char, int >, double > my_type;

	my_type a;
	a.first.first = 'c';
	a.first.second = 234;
	a.second = 17.8;

	my_type b = std::make_pair( std::make_pair( 'f', 92 ), 29.3 );
}


// We should not econom on number of classes. Such behavior will lead to
//  * longer codes,
//  * which is more difficult to understand,
//  * and maintain.


//
// Basic implementation of tuple
//

/// Declaration of the class. 
/// The general case is never instantiated.
template< typename... Types >
struct tuple
{
	static_assert( 
			false, 
			"The non-specialized 'tuple<>' should never be instantiated." );
};

/// The specialization of 'tuple' which should be instantiated.
template< typename HeadType, typename... BodyTypes >
struct tuple< HeadType, BodyTypes... >
{
	typedef HeadType head_type;                // Type of the first value
	typedef tuple< BodyTypes... > inner_type;  // Type of nested tuple

	HeadType _head;               // First value of the tuple
	tuple< BodyTypes... > _body;  // The remaining values

	/// Constructor
	tuple( const HeadType& head_, BodyTypes... body_ )
		: _head( head_ ), 
		  _body( body_... )
		{}
};

/// The "exit-branch" for tuple class.
template<>
struct tuple<>
{
};


// Let's see how this can already be used, in the 'main()' function... VVV
//
// Using 'tuple<>' is not easy that way. So let's write accessor class for it.


//
// Getter for tuple
//

/// This class implements access to tuple fields by index.
template< typename TupleType, unsigned int Index >
struct getter
{
	/// Type of the nested tuple.
	typedef typename TupleType::inner_type inner_tuple_type;

	/// Type of the field at 'Index'.
	typedef typename getter< 
			inner_tuple_type, 
			Index - 1 >::type type;

	/// Type of the getter, to work with nested tuple.
	typedef getter<	
			inner_tuple_type, 
			Index - 1 > inner_getter_type;

	/// Const / non-const access to the field at 'Index'.
	static const type& get( const TupleType& t )
		{ return inner_getter_type::get( t._body ); }
	//
	static type& get( TupleType& t )
		{ return inner_getter_type::get( t._body ); }
};

/// Specialization for the "exit-branch".
template< typename TupleType >
struct getter< TupleType, 0 >
{
	/// Type of the field at 'Index'.
	typedef typename TupleType::head_type type;

	/// Const / non-const access to the field at 'Index'.
	static const type& get( const TupleType& t )
		{ return t._head; }
	//
	static type& get( TupleType& t )
		{ return t._head; }
};


// Note, index for the tuple must be specified at compile time.
//  * It makes the return type to be known,
//  * as well as optimizes the nested 'get()' calls.
// 
// Let's see how the 'getter<>' class can be used in 'main()' ... VVV


/// Helper function for accessing tuple by index.
template< unsigned int Index, typename TupleType >
const typename getter< TupleType, Index >::type&
get( const TupleType& t )
	{ return getter< TupleType, Index >::get( t ); }
//
template< unsigned int Index, typename TupleType >
typename getter< TupleType, Index >::type&
get( TupleType& t )
	{ return getter< TupleType, Index >::get( t ); }


//
// Unpacking 'tuple<>'
//


// Packing means: "A, B, C, D"  ==>  "MyClass< A, B, C, D >"
//
// Unpacking means: "MyClass< A, B, C, D >"  ==>  "A, B, C, D"
//
// Unpacking might be necessary if we want to provide all items of a tuple 
// as an argument to a function.
//
// See an inconvenient example below... VVV


/// This is a tester function, which will be used as "Callable".
void test_printer_func( float a, const std::string& b, int c )
{
	std::cout << "Arguments : " 
			<< a << " - [\"" 
			<< b << "\","
			<< c << "]" << std::endl;
}


/// Trivial implementation of "executor".
/// User is required to specify all necessary indexes for addressing
/// the tuple.
template< unsigned int... Indexes >
struct executor_by_indexes
{
	/// Invokes "Callable" 'f', using some fields of tuple 't' as arguments.
	/// Indexes of the fields to be used are specified in 'Indexes...'
	/// Returns result of execution of 'f'.
	template< typename Callable, typename TupleType >
	static auto run( Callable f, TupleType t )
	{
		return f( get<Indexes>(t)... );
	}
};


// In order to get to the general implementation, we need to somehow generate 
//   indexes "<0, 1, 2, ..., N>"


/// The general case of "executor" template.
/// The indexes "<I, I+1, I+2, ..., N>" are already generated.
/// It remains for us to instantiate the first 'I' indexes.
template< unsigned int I, unsigned int... UpperIndexes >
struct executor
{
	/// Type f inner executor, which has the next maximal index 
	/// specified.
	typedef executor< I-1, I, UpperIndexes... > inner_executor_type;

	/// Here we just delegate execution to inner executor.
	template< typename Callable, typename TupleType >
	static auto run( Callable f, TupleType t )
	{
		return inner_executor_type::run( f, t );
	}
};

/// "Exit-branch" specialization for the "executor" class.
/// Here 'UpperIndexes' pack is equal to "<0, 1, 2, ..., N>".
template< unsigned int... UpperIndexes >
struct executor< (unsigned int)(-1), UpperIndexes... >
{
	/// Here we perform the call
	template< typename Callable, typename TupleType >
	static auto run( Callable f, TupleType t )
	{
		return f( get<UpperIndexes>(t)... );
	}
};


// So if in previous examples we were "shrinking" the parameters pack...
//
//   ... here we "expand" it.


int main( int argc, char* argv[] )
{
	// Part 1 (the basics)
	{
		tuple< float, std::string, int > t1( 5.2f, "letter", 61 );

		std::cout << t1._head << " "                     // first item
				<< t1._body._head << " "                 // second item
				<< t1._body._body._head << std::endl;    // third item

		std::cout << std::endl;
	}

	// Part 2 (using getter class)
	{
		tuple< float, std::string, int > t2( 9.1f, "pairwise", 70 );
		std::cout << "The second item is : " 
				<< getter< decltype(t2), 1 >::get( t2 ) << std::endl;

		getter< decltype(t2), 2 >::get( t2 ) += 12;
		std::cout << "The third item is : " 
				<< getter< decltype(t2), 2 >::get( t2 ) << std::endl;

		std::cout << std::endl;
	}

	// Part 3 (using getter function)
	{
		tuple< float, std::string, int, char > t3( 5.2f, "Hello", 64, 'x' );

		std::cout << "Second item is : " << get< 1 >( t3 ) << std::endl;
		std::cout << "Fourth item is : " << get< 3 >( t3 ) << std::endl;

		get< 0 >( t3 ) += 1.5;
		get< 2 >( t3 ) = 78;

		std::cout << std::endl;
	}

	// Part 4.0 (calling a function by tuple, without unpacking)
	{
		tuple< float, std::string, int > t4( 12.4f, "limit", 83 );

		test_printer_func( get<0>(t4), get<1>(t4), get<2>(t4) );
		//
		// instead we want write smth. like "test_printer_funct( t4 )"
	}

	// Part 4 (unpacking with specifying indexes explicitly)
	{
		tuple< float, std::string, int > t4( 7.1f, "basic", 64 );
		executor_by_indexes< 0, 1, 2 >::run( test_printer_func, t4 );

		// Some other invocation (just as an example)
		executor_by_indexes< 2, 1, 0 >::run( test_printer_func, t4 );

		tuple< float, char, int, std::string > t5( 5.2f, 'q', 371, "property" );
		executor_by_indexes< 0, 3, 2 >::run( test_printer_func, t5 );

		std::cout << std::endl;
	}

	// Part 5 (unpacking without specifying indexes)
	{
		tuple< float, std::string, int > t6(
				5.9f, "force", 72 );
		executor< 2 >::run( test_printer_func, t6 );

		tuple< float, std::string, int, char > t7(
				12.8f, "micro", 127, 'f' );
		executor< 2 >::run( test_printer_func, t7 );

		std::cout << std::endl;
	}

	return 0;
}
