#pragma once

/*
3) tuple դասի getter-ը ձևափոխել այնպես, 
որ ինդեքսով overflow-ի ժամանակ մենք compile error տեսնենք։ 
Հիշենք որ tuple-ի ինդեքսները compile time հայտնի մեծություններ են։
*/

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

	constexpr static int size = inner_type::size + 1;

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
	constexpr static int size = 0;
};



template< typename TupleType, unsigned int Index >
struct getter
{
	typedef typename TupleType::inner_type inner_tuple_type;

	typedef typename getter< 
			inner_tuple_type, 
			Index - 1 >::type type;

	typedef getter<	
			inner_tuple_type, 
			Index - 1 > inner_getter_type;

	static const type& get( const TupleType& t )
		{ return inner_getter_type::get( t._body ); }
	static type& get( TupleType& t )
		{ return inner_getter_type::get( t._body ); }
};

/// Specialization for the "exit-branch".
template< typename TupleType >
struct getter< TupleType, 0 >
{
	typedef typename TupleType::head_type type;

	static const type& get( const TupleType& t )
		{ return t._head; }
	static type& get( TupleType& t )
		{ return t._head; }
};

template< unsigned int Index >
struct getter< tuple<>, Index >
{
	static_assert( 
		false, 
		"Out of bounds Index" );
};


template< unsigned int Index, typename TupleType >
const typename getter< TupleType, Index >::type&
get( const TupleType& t )
	{ return getter< TupleType, Index >::get( t ); }

template< unsigned int Index, typename TupleType >
typename getter< TupleType, Index >::type&
get( TupleType& t )
	{ return getter< TupleType, Index >::get( t ); }



/*
4. Equality comparison of 2 tuples
*/
template<typename... T>
bool operator==(const tuple<T...>& l, const tuple<T...>& r)
{
	return l._head == r._head &&
		l._body == r._body;
}

bool operator==(const tuple<>&, const tuple<>&)
{ return true; }


/*
implement access by index from right (reverse access)
*/
template<typename tuple_type, unsigned int index>
struct getter_rev
{
	typedef typename tuple_type::inner_type inner_type;
	typedef getter_rev<inner_type, index> inner_getter_type;
	typedef typename inner_getter_type::type type;

	static const type& get(const tuple_type& tuple)
	{
		return inner_getter_type::get(tuple._body);
	}
	static type& get(tuple_type& tuple)
	{
		return inner_getter_type::get(tuple._body);
	}
};

template<typename tuple_type>
struct getter_rev<tuple_type, tuple_type::size - 1>
{
	typedef tuple_type::head_type type;

	static const type& get(const tuple_type& tuple)
		{ return tuple._head; }
	static type& get(tuple_type& tuple)
		{ return tuple._head; }
};


template<unsigned int index, typename tuple_type>
const typename getter_rev<tuple_type, index>::type&
rget(const tuple_type& tuple)
{
	return getter_rev<tuple_type, index>::get(tuple);
}

template<unsigned int index, typename tuple_type>
typename getter_rev<tuple_type, index>::type&
rget(tuple_type& tuple)
{
	return getter_rev<tuple_type, index>::get(tuple);
}