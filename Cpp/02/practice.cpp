#include <iostream>


/*
1. Calculate a^N
*/
template<int base, int exponent, bool is_negative>
struct power_impl
{
    constexpr static double value = base * power_impl<base, exponent - 1, is_negative>::value;
};

template<int base, bool is_negative>
struct power_impl<base, 0, is_negative>
{
    constexpr static double value = 1.0;
};

template<int base, int exponent>
struct power_impl<base, exponent, true>
{
    constexpr static double value = 1.0 / power_impl<base, -exponent, false>::value;   
};

template<int base, int exponent>
struct power
{
    constexpr static double value = power_impl<base, exponent, exponent < 0>::value;
};




/*
2. Maximal of 3 values
*/
template<typename T, T v1, T v2>
struct max
{
    const static T value = v1 < v2 ? v2 : v1;
};

template<typename T, T v1, T v2, T v3>
struct max_3
{
    const static T value = max<T, max<T, v1, v2>::value, v3>::value;
};


/*
3. |x|
*/
template<bool is_positive>
struct modulo_helper
{
    static const bool value = is_positive;
};

template<int x>
int modulo()
{
    return modulo_helper<x >= 0>::value ? x : -x;
}


/*
4. Check a == b
*/
template<int a, int b>
struct equals
{
    const static bool value = false;
};

template<int a>
struct equals<a, a>
{
    const static bool value = true;
};


/*
5. Return number of digits of n, such that n belongs to [1, 9999]
*/
template<int number, bool first_call = true>
struct digits_count
{
    const static int value = 1 + digits_count<number / 10, false>::value;
};

template<>
struct digits_count<0, true>
{
    const static int value = 1;
};

template<>
struct digits_count<0, false>
{
    const static int value = 0;
};


/*
6. Check if template argument is a C-style array.
*/
// template<typename T>
// struct is_array
// {
//     const static bool value = false;
// };

// template<typename T, size_t size>
// struct is_array<T[size]>
// {
//     const static bool value = true;
// };

template<typename T>
bool is_array(T) { return false; }

template<typename T, size_t size>
bool is_array(T(&)[size]) { return true; }



/*
7. Check if argument is a pointer
*/
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

/*
8. Check if A & B types are the same
*/
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


/*
9. Return size of the C-style array.
*/
template<typename T, size_t size>
size_t extent(T(&)[size]) { return size; }


/*
10. Return dimensions of the C-style array.
*/
template<typename T>
size_t rank(T) { return 0; }

template<typename T, size_t size>
size_t rank(T(&arr)[size])
{
    return rank(arr[0]) + 1;
}


int main()
{
    int arr[10];
    int arr2[10][10][10];


    // 1. a^n
    std::cout << "\npower\n";
    std::cout << power<5, 3>::value << std::endl;
    std::cout << power<0, 12>::value << std::endl;
    std::cout << power<12, 0>::value << std::endl;
    std::cout << power<16, -2>::value << std::endl;
    std::cout << power<2, -1>::value << std::endl;


    // 2. max of 3
    // std::cout << "max of 3\n";
    // std::cout << max<int, 5, 10>::value << std::endl;
    // std::cout << max_3<int, 10, 15, 20>::value << std::endl;
    // std::cout << max_3<int, 40, 5, 10>::value << std::endl;

    // 3. |x|
    std::cout << "\nModulo\n";
    std::cout << modulo<5>() << std::endl;
    std::cout << modulo<-5>() << std::endl;

    // 4. a == b
    std::cout << "\nequals\n";
    std::cout << equals<1, 2>::value << std::endl;
    std::cout << equals<1, 1>::value << std::endl;
    
    // 5. dumber of digits
    std::cout << "\nDigits count\n";
    static_assert(digits_count<123345>::value == 6, "digits_count<123345>::value");
    static_assert(digits_count<123345>::value == 6, "digits_count<123345>::value");
    static_assert(digits_count<123345>::value == 6, "digits_count<123345>::value");
    std::cout << digits_count<112038700, true>::value << std::endl;
    std::cout << digits_count<150 * 34>::value << std::endl;
    std::cout << digits_count<0>::value << std::endl;
    std::cout << digits_count<0, false>::value << std::endl;
    
    // 6. check if template arg is a c-style array
    std::cout << "\nis_array\n";
    std::cout << is_array(arr) << std::endl;
    std::cout << is_array(10) << std::endl;

    // 7. check if template arg is a ptr. 
    std::cout << "\nis_pointer\n";
    std::cout << is_pointer<int*>::value << std::endl;
    std::cout << is_pointer<int>::value << std::endl;
    std::cout << is_pointer<decltype(arr)>::value << std::endl;

    // 8. check if template args are of the same type
    std::cout << "\nis_same\n" << std::endl;
    std::cout << is_same<int, float>::value << std::endl;
    std::cout << is_same<int, int>::value << std::endl;
    
    // 9. c-style array size.
    std::cout << "\nextent\n";
    std::cout << extent(arr) << std::endl;

    // 10. c-style array dimensions
    std::cout << "\nrank\n";
    std::cout << rank(arr) << std::endl;
    std::cout << rank(arr2) << std::endl;
}