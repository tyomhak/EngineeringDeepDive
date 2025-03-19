
#ifndef EDD_CPP__CT_SEQUENCE_BUILDER_HPP
#define EDD_CPP__CT_SEQUENCE_BUILDER_HPP

#include "code_10__ct_sequence.hpp"


/// Building sequence from 1 value.
template< int V1 >
struct ct_sequence_1
{
	typedef ct_sequence< V1, ct_empty_sequence > type;
};

/// Building seqeunce from 2 values.
template< int V1, int V2 >
struct ct_sequence_2
{
	typedef ct_sequence< 
			V1, 
			typename ct_sequence_1< V2 >::type > type;
};

/// Building seqeunce from 3 values.
template< int V1, int V2, int V3 >
struct ct_sequence_3
{
	typedef ct_sequence< 
			V1, 
			typename ct_sequence_2< V2, V3 >::type > type;
};

/// Building seqeunce from 4 values.
template< int V1, int V2, int V3, int V4 >
struct ct_sequence_4
{
	typedef ct_sequence< 
			V1, 
			typename ct_sequence_3< V2, V3, V4 >::type > type;
};

/// Building seqeunce from 5 values.
template< int V1, int V2, int V3, int V4, int V5 >
struct ct_sequence_5
{
	typedef ct_sequence< 
			V1, 
			typename ct_sequence_4< V2, V3, V4, V5>::type > type;
};


// Exercises:
//
// 1) Write "ct_sequence_6" class template.
//
// 2) Implement "ct_sequence_L" class variadic template.


#endif // EDD_CPP__CT_SEQUENCE_BUILDER_HPP
