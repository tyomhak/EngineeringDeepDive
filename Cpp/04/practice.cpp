#include <iostream>
#include "hw/tuple.h"

// function which prints arguments in reverse order
void print_rev()
{}

template<typename T, typename... ArgTypes>
void print_rev(const T& arg, ArgTypes... args)
{
    print_rev(args...);
    std::cout << arg << ", ";
}


// integers printing function, to print also other types (not ints) ???
template<int value>
void print_int()
{
    std::cout << " " << value << "\n";
}

template<int value_1, int value_2, int... values>
void print_int()
{
    std::cout << " " << value_1;
    print_int<value_2, values...>();
}

template<int value, int... values>
struct value_printer
{
    static void print()
    {
        std::cout << " " << value << ", ";
        value_printer<values...>::print();
    }
};

template<int value>
struct value_printer<value>
{
    static void print()
    {
        std::cout << " " << value << ", ";
    }
};

template<int... values>
void print_values()
{
    value_printer<values...>::print();
}

template<typename T, T value>
void print_vals()
{
    std::cout << value << std::endl;
}

template<typename T, T value_1, T value_2, T... values>
void print_vals()
{
    std::cout << value_1 << ", ";
    print_vals<T, value_2, values...>();
}


int main()
{
    print_rev(0, 15.3f, "something", 'c');
    print_int<1,2,3,4,5>();

    print_values<1,2,3,4,5>();
    print_vals<int, 1,2,3,4,5>();
    print_vals<float, 1.0f, 2.0f, 3.0f, 4.5f>();

    tuple< float, std::string, int > t1( 5.2f, "letter", 61 );

    std::cout << rget<0>(t1) << std::endl;
    std::cout << rget<2>(t1) << std::endl;

    return 0;
}