#include <iostream>

template<int a, int N>
struct power
{
    const static int value = a * power<a, N - 1>::value;
};

template<int a>
struct power<a, 0>
{
    const static int value = 1;
};



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






template<int a, int b>
struct eqs
{
    const static bool value = false;
};

template<int a>
struct eqs<a, a>
{
    const static bool value = true;
};


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


// template<typename T>
// bool is_pointer() { return false; }

// template<typename T>
// bool is_pointer<T*>() { return true; }


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


template<typename T, size_t size>
size_t extent(T(&)[size]) { return size; }


template<typename T>
size_t rank(T) { return 0; }

template<typename T, size_t size>
size_t rank(T(&arr)[size])
{
    return rank(arr[0]) + 1;
}


int main()
{
    std::cout << power<5, 3>::value << std::endl;

    std::cout << eqs<1, 2>::value << std::endl;
    std::cout << eqs<1, 1>::value << std::endl;


    std::cout << modulo<5>() << std::endl;
    std::cout << modulo<-5>() << std::endl;

    std::cout << is_same<int, float>::value << std::endl;
    std::cout << is_same<int, int>::value << std::endl;
    

    int arr[10];
    std::cout << "extent\n";
    std::cout << extent(arr) << std::endl;

    std::cout << "is_array\n";
    std::cout << is_array(arr) << std::endl;
    std::cout << is_array(10) << std::endl;

    std::cout << "is_pointer\n";
    std::cout << is_pointer<int*>::value << std::endl;
    std::cout << is_pointer<int>::value << std::endl;
    std::cout << is_pointer<decltype(arr)>::value << std::endl;

    int arr2[10][10][10];
    std::cout << rank(arr) << std::endl;
    std::cout << rank(arr2) << std::endl;



}