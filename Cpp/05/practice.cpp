
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


template<typename T, unsigned int _size>
struct TypeSize
{
    typedef T type;
    static const unsigned int size = _size;
};

template<
    template<typename, int> class CONT,
    typename... types>
struct performance_evaluator
{
    static_assert( false, 
        "General case of 'performance_evaluator' class template should"
        " not be instantiated." );
};

template<
    template<typename, int> class CONT,
    typename TS,
    typename... types>
struct performance_evaluator<CONT, TS, types...>
{
    void measure() {
        CONT<typename TS::type, TS::size> cont{};
        // .. run

        performance_evaluator<CONT, types...> inner_evaluator;
        inner_evaluator.measure();
    }
};

template<
    template<typename, int> class CONT>
struct performance_evaluator<CONT>
{
    void measure()
    {}
};

int main()
{
    Logger<SimpleCombiner, Receiver1, Transformer1, Sender1> logger_1{};
    Logger<ComplexCombiner, Receiver1, Transformer2, Sender3> logger_2{};

    performance_evaluator< 
        static_array, 
        TypeSize<int, 5>,
        TypeSize<float, 10>,
        TypeSize<double, 15>,
        TypeSize<char, 20>
        > ev1;
    
    ev1.measure();

    performance_evaluator< 
        unrolled_linked_list, 
        TypeSize<int, 5>,
        TypeSize<float, 10>,
        TypeSize<double, 15>,
        TypeSize<char, 20>
        > ev2;

    ev2.measure();

}