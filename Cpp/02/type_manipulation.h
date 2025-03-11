#pragma once


// 1. Check if 'T' represents a plain array,
template<typename T>
struct is_array
{
    const static bool value = false;
};

template<typename T, size_t size>
struct is_array<T[size]>
{
    const static bool value = true;
};



// 2. Check if 'T' is a pointer
template<typename T>
struct is_pointer
{
    const static bool value = false;
};

template<typename T>
struct is_pointer<T*>
{
    const static bool value = true;
};


// 3. Check if 2 argument types 'T' and 'U' are the same type
template<typename A, typename B>
struct is_same
{
    const static bool value = false;
};

template<typename A>
struct is_same<A,A>
{
    const static bool value = true;
};

// 4. Return size (extent) of provided static array type 'T'
template<typename T>
struct extent;

template<typename T, size_t size>
struct extent<T[size]>
{
    const static size_t value = size;
};



// 5. Return dimensionality (rank) of provided static multidimensional array type 'U'.
// template<typename T>
// struct rank;

// template<typename T, size_t size>
// struct rank<T[size]>
// {
//     const static size_t rank =  
// }

// template<typename T>
// struct rank
// {
//     const static size_t value = 0;
// };

// template<typename T, size_t size>
// struct rank<T[size]>
// {
//     const static size_t value = rank<decltype(T)>::value + 1;
// };


