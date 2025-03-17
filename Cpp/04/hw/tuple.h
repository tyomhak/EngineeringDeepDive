#pragma once

/*
3) tuple դասի getter-ը ձևափոխել այնպես, 
որ ինդեքսով overflow-ի ժամանակ մենք compile error տեսնենք։ 
Հիշենք որ tuple-ի ինդեքսները compile time հայտնի մեծություններ են։


4) Իրականացնել երկու tuple-ների համեմատման օպերատոր "operator==":
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
};



template< typename TupleType, unsigned int Index >
struct getter
{
	/// Type of the nested tuple.
	typedef typename TupleType::inner_type inner_tuple_type;

	/// Type of the field at 'Index'.
	typedef typename getter< 
			inner_tuple_type, 
			Index - 1 >::type type;

	/// Type of the getter, to work with nested tuple.
	typedef getter<	
			inner_tuple_type, 
			Index - 1 > inner_getter_type;

	/// Const / non-const access to the field at 'Index'.
	static const type& get( const TupleType& t )
		{ return inner_getter_type::get( t._body ); }
	//
	static type& get( TupleType& t )
		{ return inner_getter_type::get( t._body ); }
};

/// Specialization for the "exit-branch".
template< typename TupleType >
struct getter< TupleType, 0 >
{
	/// Type of the field at 'Index'.
	typedef typename TupleType::head_type type;

	/// Const / non-const access to the field at 'Index'.
	static const type& get( const TupleType& t )
		{ return t._head; }
	//
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
//
template< unsigned int Index, typename TupleType >
typename getter< TupleType, Index >::type&
get( TupleType& t )
	{ return getter< TupleType, Index >::get( t ); }



template<typename... T>
bool operator==(const tuple<T...>& l, const tuple<T...>& r)
{
	return l._head == r._head &&
		l._body == r._body;
}

bool operator==(const tuple<>&, const tuple<>&)
{ return true; }
