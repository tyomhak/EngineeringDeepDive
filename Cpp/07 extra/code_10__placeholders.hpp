
#ifndef EDD_CPP__PALCEHOLDERS_HPP
#define EDD_CPP__PALCEHOLDERS_HPP

/// A metafunction which when computed, adds values of 
/// argument metafunctions.
template< 
		template< int, int > class Op1, 
		template< int, int > class Op2 >
struct plus
{
	template< int X, int Y >
	struct t
		{ static constexpr auto value = (Op1<X, Y>::value + Op2<X, Y>::value); };
};

/// A metafunction which when computed, checks if value of the 
/// first metafunction is less than value of the second one.
template< 
		template< int, int > class Op1, 
		template< int, int > class Op2 >
struct less
{
	template< int X, int Y >
	struct t
		{ static constexpr bool value = (Op1<X, Y>::value < Op2<X, Y>::value); };
};

/// A metafunction which when computed, subtracts values of 
/// argument metafunctions.
template< 
		template< int, int > class Op1, 
		template< int, int > class Op2 >
struct minus
{
	template< int X, int Y >
	struct t
		{ static constexpr auto value = (Op1<X, Y>::value - Op2<X, Y>::value); };
};

/// A metafunction, which when computed, returns value of the 
/// first argument.
template< int X, int Y >
struct _1
	{ static constexpr auto value = X; };

/// A metafunction, which when computed, returns value of the 
/// second argument.
template< int X, int Y >
struct _2
	{ static constexpr auto value = Y; };

/// A constant metafunction, which when computed, returns 
/// given constant value.
template< int Value >
struct constant
{
	template< int X, int Y >
	struct t
		{ static constexpr auto value = Value; };
};


#endif // EDD_CPP__PALCEHOLDERS_HPP
