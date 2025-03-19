#pragma once

#include <limits>

#include "../in_class/code_10__ct_sequence.hpp"
#include "../in_class/code_30__ct_sequence_builder.hpp"


// 1) Write a metafunction for counting number of occurrences of given 
//     value 'Y', in provided sequence.
template<typename Sequence, int value>
struct ct_count
{
    static constexpr auto count = 
        ct_count<typename Sequence::body_type, value>::count +
        (Sequence::head == value ? 1 : 0);
};

template<int value>
struct ct_count<ct_empty_sequence, value>
{
    static constexpr auto count = 0;
};



// PART 2
// 1) Write "ct_sequence_6" class template.
template< int V1, int V2, int V3, int V4, int V5, int V6 >
struct ct_sequence_6
{
	typedef ct_sequence< 
			V1, 
			typename ct_sequence_5< V2, V3, V4, V5, V6>::type > type;
};


// 2) Implement "ct_sequence_L" class variadic template.
template<int... vals>
struct ct_sequence_L
{};

template<int val, int... vals>
struct ct_sequence_L<val, vals...>
{
    typedef typename ct_sequence_L<vals...>::type inner_type;
    typedef ct_sequence<val, inner_type> type;
};

template<>
struct ct_sequence_L<>
{
    typedef ct_empty_sequence type;
};


// PART 3
// 1) 'ct_pop_front< Seq >', to remove first element of the sequence,
template<typename Sequence>
struct ct_pop_front
{
    typedef typename Sequence::body_type type;
};

// template<>
// struct ct_pop_front<ct_empty_sequence>
// {
//     static_assert(false, "Popping from empty sequence");
// };




// 2) 'ct_insert< Seq, Index, Value >', to insert 'Value' in certain position,
template<typename Seq, int Index, int Value>
struct ct_insert
{
    typedef ct_sequence<Seq::head, 
        typename ct_insert<typename Seq::body_type, Index - 1, Value>::type> type;
};

template<typename Seq, int Value>
struct ct_insert<Seq, 0, Value>
{
    typedef ct_sequence<Value, Seq> type;
};


// 3) 'ct_erase< Seq, Index >', to erase the value at position 'Index',
template<typename Seq, int Index>
struct ct_erase
{
    typedef ct_sequence<Seq::head, typename ct_erase<typename Seq::body_type, Index - 1>::type> type;
};

template<typename Seq>
struct ct_erase<Seq, 0>
{
    typedef typename Seq::body_type type;
};

template<int Index>
struct ct_erase<ct_empty_sequence, Index>
{
    static_assert(false, "Erasing from empty ct_sequence");
};

// template<>
// struct ct_erase<ct_empty_sequence, 0>
// {
//     // static_assert(false, "Erasing from empty ct_sequence");
// };


// 4) 'ct_max_element< Seq >', for computing maximal value of given sequence,
template<typename Seq>
struct ct_max_element
{
    static constexpr int inner_max = ct_max_element<typename Seq::body_type>::value;
    static constexpr int value = Seq::head > inner_max ? Seq::head : inner_max;
};

template<>
struct ct_max_element<ct_empty_sequence>
{
    static constexpr int value = std::numeric_limits<int>::min();
};


// 5) 'ct_push_back< Seq, Value >', for appending 'Value' to given sequence,
template<typename Seq, int Value>
struct ct_push_back
{
    typedef ct_sequence<Seq::head, 
        typename ct_push_back<typename Seq::body_type, Value>::type> type;
};

template<int value>
struct ct_push_back<ct_empty_sequence, value>
{
    typedef ct_sequence<value, ct_empty_sequence> type;
};


// 6) 'ct_reverse< Seq >', for reversing given sequence,
template< typename Sequence, int V1 >
struct ct_push_front
{
	typedef ct_sequence< V1, Sequence > type;
};

template<typename Seq, typename InnerSeq = ct_empty_sequence>
struct ct_reverse
{
    typedef ct_sequence<Seq::head, InnerSeq> inner_seq;
    typedef typename ct_reverse<typename Seq::body_type, inner_seq>::type type;
};

template<typename InnerSeq>
struct ct_reverse<ct_empty_sequence, InnerSeq>
{
    typedef InnerSeq type;    
};


//
// 7) 'ct_insert_to_sorted< Seq, Value >', insertion of 'Value' into sorted 
//         sequence 'Seq', so the latter one will remain sorted,
template<typename Seq, int Value>
struct ct_insert_to_sorted;

template<typename Seq, int Value, bool InsertAtHead>
struct ct_insert_helper
{
    typedef ct_sequence<Seq::head,
        typename ct_insert_to_sorted<typename Seq::body_type, Value>::type> type;
};

template<typename Seq, int Value>
struct ct_insert_helper<Seq, Value, true>
{
    typedef ct_sequence<Value, Seq> type;
};

template<typename Seq, int Value>
struct ct_insert_to_sorted
{
    typedef ct_insert_helper<Seq, Value, Value <= Seq::head>::type type;
};

template<int Value>
struct ct_insert_to_sorted<ct_empty_sequence, Value>
{
    typedef ct_sequence<Value, ct_empty_sequence> type;
};

// 8) 'ct_insertion_sort< Seq >', implementation of sorting,
template<typename SortedSeq, typename UnsortedSeq>
struct ct_insertion_sort_helper
{
    typedef typename ct_insertion_sort_helper<
        typename ct_insert_to_sorted<SortedSeq, UnsortedSeq::head>::type,
        typename UnsortedSeq::body_type>::type type;
};

template<typename SortedSeq>
struct ct_insertion_sort_helper<SortedSeq, ct_empty_sequence>
{
    typedef SortedSeq type;
};

template<typename Seq>
struct ct_insertion_sort
{
    typedef typename ct_insertion_sort_helper<ct_empty_sequence, Seq>::type type;
};