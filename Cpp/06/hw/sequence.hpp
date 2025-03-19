

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

// 4) 'ct_max_element< Seq >', for computing maximal value of given sequence,
//
// 5) 'ct_push_back< Seq, Value >', for appending 'Value' to given sequence,
//
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
// 
// 8) 'ct_insertion_sort< Seq >', implementation of sorting,