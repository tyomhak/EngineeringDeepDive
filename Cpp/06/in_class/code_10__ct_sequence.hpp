
#ifndef EDD_CPP__CT_SEQUENCE_HPP
#define EDD_CPP__CT_SEQUENCE_HPP


// Till now we were writing metafunctions which operated on SINGLE types or
// values:
//  --> value to value
//  --> type to value
//  --> type to type
// 
// Metaprogramming refers not only to single values and single types,
//    ... but also for sequences of values or types.
//
// Most popular representation of a sequence there is:
//  * a value,
//  * and its continuation.


/// Recursive implementation of a sequence.
template< int Head, typename BodyType >
struct ct_sequence
{
	/// Head value of this sequence.
	static constexpr int head = Head;

	/// Continuation of this sequence.
	typedef BodyType body_type;

	/// Length of this sequence.
	static constexpr unsigned int length = body_type::length + 1;
};

/// The "exit branch" for recursive sequence.
struct ct_empty_sequence
{
	/// Length of empty sequence is zero.
	static constexpr unsigned int length = 0;
};


#endif // EDD_CPP__CT_SEQUENCE_HPP
