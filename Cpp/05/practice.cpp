#include <string>

#include "Logger.h"

// Exercises:
//
// 1) In function "measure_performance()" provide also sizes of containers, as a variadic list 
//    of integers. Make the function to instantiate provided conatiner with all those sizes.
// 
// 2) In function "measure_performance()" provide also types of elements of the containers, 
//    as a variadic sequence of types integers. Make the function to instantiate provided 
//    conatiner with all those sizes.
// 
// 3) [*] Provide both variadic lists: list of 'M' sizes, and list of 'N' types. Make the
//    function "measure_performance()" to do "M*N" instantiations.
//

/// Declaration of static array.
template< typename T, int Capacity >
class static_array {};

/// Declaration of Circular buffer.
template< typename T, int Capacity >
class circular_buffer {};

/// Declaration of Unrolled linked list
template< typename T, int Capacity >
class unrolled_linked_list {};

namespace type_1
{
template<
    template<typename, int> class CONT,
    int... sizes>
struct performance_evaluator
{
    static_assert(false, "Default impl should never be used");
};

template<
    template<typename, int> class CONT,
    int size,
    int... sizes>
struct performance_evaluator<CONT, size, sizes...>
{
    void measure_performance()
    {
        CONT< int, size > c1;
        CONT< char, size > c2;
        CONT< double, size > c3;
        CONT< std::string, size > c4;

        performance_evaluator<CONT, sizes...> pe{};
        pe.measure_performance();
    }
};

template<
    template<typename, int> class CONT>
struct performance_evaluator<CONT>
{
    void measure_performance()
    {}
};
}

namespace type_2
{

        
}


int main()
{
    test_logger();
    type_1::performance_evaluator<static_array, 1,2,3> pe;
    pe.measure_performance();

    

}


// template<typename T, unsigned int _size>
// struct TypeSize
// {
//     typedef T type;
//     static const unsigned int size = _size;
// };

// template<
//     template<typename, int> class CONT,
//     typename... types>
// struct performance_evaluator
// {
//     static_assert( false, 
//         "General case of 'performance_evaluator' class template should"
//         " not be instantiated." );
// };

// template<
//     template<typename, int> class CONT,
//     typename TS,
//     typename... types>
// struct performance_evaluator<CONT, TS, types...>
// {
//     void measure() {
//         CONT<typename TS::type, TS::size> cont{};
//         // .. run

//         performance_evaluator<CONT, types...> inner_evaluator;
//         inner_evaluator.measure();
//     }
// };

// template<
//     template<typename, int> class CONT>
// struct performance_evaluator<CONT>
// {
//     void measure()
//     {}
// };