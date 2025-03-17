#pragma once
#include <cstddef>
#include <type_traits>
/*
1. 
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
2. 
Իրականացնել multi_array_accessor template, 
որի պարամետրերը կլինեն հենց ինքը multi_array-ը ու 
ինդեքսների variadic հաջորդականությունը։ 

Նպատակն է՝ հասանելիություն ստանալ կոնկրետ վանդակներին։
*/

// template< typename MultiArrayT, size_t depth, size_t... indices>
// struct accessor
// {
//     static_assert(sizeof...(indices) == MultiArrayT::volume, "Incorrect number of indices passed");

//     typedef typename MultiArrayT::type type;
//     typedef typename MultiArrayT::inner_array_type inner_array_type;

//     static const type& get(const MultiArrayT& array) const
//     {
//         return accessor<inner_array_type, depth - 1, indices...>::get(array.data[])
//     }

// };

// template< typename MultiArrayT, size_t depth >
// struct accessor
// {

// };






// template<typename MultiArrayType, size_t depth, size_t index, size_t... indices>
// struct multi_array_accessor
// {
//     typedef typename MultiArrayType::type type;
//     typedef typename MultiArrayType::inner_array_type inner_array_type;
//     typedef multi_array_accessor<inner_array_type, depth - 1, indices...> inner_accessor;

//     static const inner_accessor::type& get(const MultiArrayType& arr)
//         { return inner_accessor::get(arr.data[index]); }

//     static inner_accessor::type& get(MultiArrayType& arr)
//         { return inner_accessor::get(arr.data[index]); }
// };

// template<typename MultiArrayType, size_t index>
// struct multi_array_accessor<MultiArrayType, 0, index>
// {
//     typedef typename MultiArrayType::type type;

//     static const type& get(MultiArrayType& arr)
//         { return arr.data[index]; }

//     static type& get(MultiArrayType& arr) 
//         { return arr.data[index]; }
// };