
#ifndef EDD_CPP__VARIADIC_PALCEHOLDERS_HPP
#define EDD_CPP__VARIADIC_PALCEHOLDERS_HPP

/// A metafunction which when computed, adds values of 
/// argument metafunctions.
template< 
		template< int... > class Op1, 
		template< int... > class Op2 >
struct plus_v
{
	template< int... Args >
	struct t
		{ static constexpr auto value = (Op1<Args...>::value + Op2<Args...>::value); };
};

/// A metafunction which when computed, checks if value of the 
/// first metafunction is less than value of the second one.
template< 
		template< int... > class Op1, 
		template< int... > class Op2 >
struct less_v
{
	template< int... Args >
	struct t
		{ static constexpr bool value = (Op1<Args...>::value < Op2<Args...>::value); };
};

/// A metafunction which when computed, subtracts values of 
/// argument metafunctions.
template< 
		template< int... > class Op1, 
		template< int... > class Op2 >
struct minus_v
{
	template< int... Args >
	struct t
		{ static constexpr auto value = (Op1<Args...>::value - Op2<Args...>::value); };
};

/// Implementation of placeholder in the general case.
template< int U >
struct __
{
	typedef __<U-1> lower;

	//template< int... Args >
	//struct t
	//	{ static_assert( false, "General case of 't<>' can't be instantiated." ); };

	template< int Arg1, int... Args >
	struct t
		{ typedef typename lower::t< Args... > lower_t;
		  static constexpr auto value = lower_t::value; };

	//static_assert( false, 
	//		"Specializations must be used for placeholder template." );
};

// Specialization of placeholder for taking the first argument.
template<>
struct __<1>
{
	template< int... Args >
	struct t
		{ static_assert( false, "General case of 't<>' can't be instantiated." ); };

	template< int Arg1, int... Args >
	struct t< Arg1, Args... >
		{ static constexpr auto value = Arg1; };
};

/// A constant metafunction, which when computed, returns 
/// given constant value.
template< int Value >
struct constant_v
{
	template< int... Args >
	struct t
		{ static constexpr auto value = Value; };
};


#endif // EDD_CPP__VARIADIC_PALCEHOLDERS_HPP
