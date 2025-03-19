
#ifndef EDD_CPP__CT_MULTITYPE_SEQUENCE_HPP
#define EDD_CPP__CT_MULTITYPE_SEQUENCE_HPP


// Current environment allows us to have sequence of values of
// different types.


/// Recursive implementation of a multitype sequence.
template< typename HeadType, HeadType Head, typename BodyType >
struct ct_multitype_sequence
{
	/// Type of head value of this sequence.
	typedef HeadType head_type;

	/// Head value of this sequence.
	static constexpr HeadType head = Head;

	/// Continuation of this sequence.
	typedef BodyType body_type;

	/// Length of this sequence.
	static constexpr unsigned int length = body_type::length + 1;
};

// Forward declaration for the empty sequence.
// Note, there is no need to define another kind of empty multitype
// sequence.
struct ct_empty_sequence;


// So in some sence, at compile time WE CAN DO MORE, compared to runtime.


// Exercises:
//
// 1) Implement removal of all the values which are of given type 'T'.
//
// 2) Implement filtering of all those values, which are of given type 'T'.


#endif // EDD_CPP__CT_MULTITYPE_SEQUENCE_HPP
