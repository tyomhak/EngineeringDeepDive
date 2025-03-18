#pragma once
#include <cstddef>

/*
1. get volume of multi_array

multi_array template-ի մեջ ավելացնել "static constexpr int volume = ..." դաշտ, 
որը ցույց կտա ընդհանուր վանդակների քանակը այդ կառուցվածքում։
*/

/// The base case of container.
template< typename T, int... Extents >
struct multi_array
{
	static_assert( false, 
			"Implementation is placed only in the specializations." );
};

/// Specialization for extracting the first extent.
template< typename T, int Ext1, int... Extents >
struct multi_array< T, Ext1, Extents... >
{
    typedef T type;
    typedef multi_array< T, Extents... > inner_array_type;

	inner_array_type data[ Ext1 ];
    static constexpr int volume = inner_array_type::volume * Ext1;
};

/// Specialization, when all extents are extracted.
template< typename T >
struct multi_array< T >
{
    typedef T type;
	T data;  // The final cell
    static constexpr int volume = 1;
};




/*
2. access by index to multi_array

Իրականացնել multi_array_accessor template, 
որի պարամետրերը կլինեն հենց ինքը multi_array-ը ու 
ինդեքսների variadic հաջորդականությունը։ 
Նպատակն է՝ հասանելիություն ստանալ կոնկրետ վանդակներին։
*/

template<typename ArrayType, int... indices>
struct multi_array_accessor
{
    static_assert(false, 
        "temp");
};

template<typename ArrayType, int index, int... indices>
struct multi_array_accessor<ArrayType, index, indices...>
{
    typedef typename ArrayType::inner_array_type inner_array_type;
    typedef multi_array_accessor<inner_array_type, indices...> inner_getter;
    typedef typename inner_getter::type type;

    static const type& get(const ArrayType& array)
    {
        return inner_getter::get(array.data[index]);
    }
    static type& get(ArrayType& array)
    {
        return inner_getter::get(array.data[index]);
    }
};


template<typename ArrayType>
struct multi_array_accessor<ArrayType>
{
    typedef typename ArrayType::type type;

    static const type& get(const ArrayType& array)
        { return array.data; }

    static type& get(ArrayType& array)
        { return array.data; }
};

template<unsigned int... indices, typename multi_array_type>
const multi_array_accessor<multi_array_type, indices...>::type&
array_get(const multi_array_type& array)
{
    return multi_array_accessor<multi_array_type, indices...>::get(array);
}

template<unsigned int... indices, typename multi_array_type>
multi_array_accessor<multi_array_type, indices...>::type&
array_get(multi_array_type& array)
{
    return multi_array_accessor<multi_array_type, indices...>::get(array);
}