
#ifndef EDD_CPP__CT_SEQUENCE_ALGORITHMS_2_HPP
#define EDD_CPP__CT_SEQUENCE_ALGORITHMS_2_HPP


// We can push it further and implement STL-style modificators:


/// This metafunction prepends 'V1' to provided sequence.
template< typename Sequence, int V1 >
struct ct_push_front
{
	typedef ct_sequence< V1, Sequence > type;
};


// A bit more complex example, which requires O(N) instantiations:


/// Metafunction for removing all occurrences of 'X' from provided 
/// sequence.
template< typename Sequence, int X >
struct ct_remove
{
	// In the base implementation we delegate filtering to continuation.
	typedef ct_sequence< 
			Sequence::head, 
			typename ct_remove< typename Sequence::body_type, X >::type > type;
};

/// Specialization for the case when the sequence starts with 'X'.
template< typename NestedSequence, int X >
struct ct_remove< ct_sequence< X, NestedSequence >, X >
{
	// If this sequence starts with 'X', then the result is filtering  
	// of the nested sequence.
	typedef typename ct_remove< NestedSequence, X >::type type;
};

/// Specialization for filtering an empty sequence.
template< int X >
struct ct_remove< ct_empty_sequence, X >
{
	// Filtering an empty sequence leaves it untouched.
	typedef ct_empty_sequence type;
};


// Important note, when modifying any sequence, the original sequence 
// is actually NOT BEING MODIFIED, but a modified-copy of it is being 
// instantiated.
//
// That is always the case when we are in template metaprogramming.


// A bit more complex example is when we want to tripple every 2nd 
// value of given sequence.


/// Base implementation for trippling every 2nd value.
template< typename Sequence, bool FromFirst = true >
struct ct_tripple_every_2nd
{
	static_assert( 
			false, 
			"Only specializations of 'tripple_every_2nd<>' must be instantiated." );
};

/// Tripple every 2nd value, starting from the first one.
template< typename Sequence >
struct ct_tripple_every_2nd< Sequence, true >
{
	typedef ct_sequence< 
			Sequence::head * 3, 
			typename ct_tripple_every_2nd< 
					typename Sequence::body_type, 
					false >::type > type;
};

/// Tripple every 2nd value, starting from the second one.
template< typename Sequence >
struct ct_tripple_every_2nd< Sequence, false >
{
	typedef ct_sequence< 
			Sequence::head, 
			typename ct_tripple_every_2nd< 
					typename Sequence::body_type, 
					true >::type > type;
};

// Pay attention, we can't write exit branch this way, as it will cause 
// ambiguity...  vvv

#if 0
/// Tripple every 2nd value in an empty sequence.
template< bool FromFirst >
struct ct_tripple_every_2nd< ct_empty_sequence, FromFirst >
{
	// Answer is the empty sequence.
	typedef ct_empty_sequence type;
};
#endif

/// Tripple every 2nd value in an empty sequence.
/// Answer is the empty sequence.
template<>
struct ct_tripple_every_2nd< ct_empty_sequence, false >
	{ typedef ct_empty_sequence type; };
//
template<>
struct ct_tripple_every_2nd< ct_empty_sequence, true >
	{ typedef ct_empty_sequence type; };


// Let's see one more example of a function, that we can implement 
// in 2 ways:


// Metafunction for calculating difference series.
template< typename Sequence >
struct ct_difference_sequence_1
{
	typedef ct_sequence< 
			Sequence::body_type::head - Sequence::head, 
			typename ct_difference_sequence_1< 
					typename Sequence::body_type >::type > type;
};

/// Exit branch for 1-long sequence.
template< int Tail >
struct ct_difference_sequence_1< 
		ct_sequence< Tail, ct_empty_sequence > >
{
	typedef ct_empty_sequence type;
};

//

/// The base case for calculating difference sequence.
template< typename Sequence >
struct ct_difference_sequence_2
{
	static_assert(
			false, 
			"Only specializations of 'ct_difference_sequence_2<>' must be instantiated." );
};

/// Specialization for calculating the difference sequence, 
/// when first two values are known.
template< int V1, int V2, typename BodyType >
struct ct_difference_sequence_2< 
		ct_sequence< V1, ct_sequence< V2, BodyType > > >
{
	typedef ct_sequence< 
			V2 - V1, 
			typename ct_difference_sequence_2< 
					ct_sequence< V2, BodyType > >::type > type;
};

/// Exit branch for 1-long sequence.
template< int Tail >
struct ct_difference_sequence_2<
		ct_sequence< Tail, ct_empty_sequence > >
{
	typedef ct_empty_sequence type;
};


// Exercises:
//
// Implement the following metafunctions:
//
// 1) 'ct_pop_front< Seq >', to remove first element of the sequence,
//
// 2) 'ct_insert< Seq, Index, Value >', to insert 'Value' in certain position,
// 
// 3) 'ct_erase< Seq, Index >', to erase the value at position 'Index',
//
// 4) 'ct_max_element< Seq >', for computing maximal value of given sequence,
//
// 5) 'ct_push_back< Seq, Value >', for appending 'Value' to given sequence,
//
// 6) 'ct_reverse< Seq >', for reversing given sequence,
//
// 7) 'ct_insert_to_sorted< Seq, Value >', insertion of 'Value' into sorted 
//         sequence 'Seq', so the latter one will remain sorted,
// 
// 8) 'ct_insertion_sort< Seq >', implementation of sorting,


// Advanced exercise:
//
// 1) Implement compile-time Binary search tree, and several metafunctions 
//        for it.
//


#endif // EDD_CPP__CT_SEQUENCE_ALGORITHMS_2_HPP
