
#ifndef EDD_CPP__CT_FUNCTIONAL_HPP
#define EDD_CPP__CT_FUNCTIONAL_HPP


//
// Metafunction for duplicating the values which satisfy given predicate.
//

// Forward declaration
template< typename Sequence, template< int > class Pred >
struct ct_duplicate_if;

/// The delegate for duplication certain values of sequence.
template< typename Sequence, template< int > class Pred, bool DuplHead >
struct ct_duplicate_if_selector
{
	static_assert(
			false, 
			"Only specializations of 'ct_duplicate_if_selector<>' must be instantiated." );
};

/// Specialization, when we don't duplicate the head value.
template< typename Sequence, template< int > class Pred >
struct ct_duplicate_if_selector< Sequence, Pred, false >
{
	typedef ct_sequence< Sequence::head, 
				typename ct_duplicate_if< typename Sequence::body_type, Pred >::type > type;
			
};

/// Specialization, when we duplicate the head value.
template< typename Sequence, template< int > class Pred >
struct ct_duplicate_if_selector< Sequence, Pred, true >
{
	typedef ct_sequence< Sequence::head, 
				ct_sequence< Sequence::head, 
					typename ct_duplicate_if< typename Sequence::body_type, Pred >::type > > type;
};

/// The metafunction for duplicating all those values of 'Sequence', 
/// which satisfy 'Pred'.
template< typename Sequence, template< int > class Pred >
struct ct_duplicate_if
{
	typedef typename ct_duplicate_if_selector< 
			Sequence, 
			Pred, 
			Pred< Sequence::head >::value >::type type;
};

/// The "exit branch" for empty sequence.
template< template< int > class Pred >
struct ct_duplicate_if< ct_empty_sequence, Pred >
{
	typedef ct_empty_sequence type;
};









/// A metafunction for checking if 'X < Y'.
template< int X, int Y >
struct ct_less
	{ static constexpr bool value = (X < Y); };

/// A metafunction for checking if 'X < Y'.
template< int X, int Y >
struct ct_equal_to
	{ static constexpr bool value = (X == Y); };


/// A higher order metafunction, which binds 2nd argument of 'Func' to 
/// 'Arg2'.
//template< template< int, int > class Func, int Arg2 >
//template< int X >
//struct ct_bind2nd_1
//{
//	static constexpr auto value = Func< X, Arg2 >::value;
//};


/// A higher order metafunction, which binds 2nd argument of 'Func' to 
/// 'Arg2'.
template< template< int, int > class Func, int Arg2 >
struct ct_bind2nd
{
	template< int X >
	struct result_type
		{ static constexpr auto value = Func< X, Arg2 >::value; };
};


/// A metafunction for checking if 'X' is divisible over 'Y'.
template< int X, int Y >
struct ct_is_divisible
	{ static constexpr bool value = (X % Y == 0); };


/// A higher order metafunction, which negates result of provided 
/// unary metafunction 'Func'.
template< template< int > class Func >
struct ct_unary_negate
{
	template< int X >
	struct result_type
		{ static constexpr auto value = (! Func< X >::value); };
};


#endif // EDD_CPP__CT_FUNCTIONAL_HPP
