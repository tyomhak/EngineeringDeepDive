#include <iostream>

#include "metaprogramming.h"
#include "type_manipulation.h"

int main()
{
    using std::cout;
    using std::endl;

    int arr[10];
    int arr2[10][10][10];

    // 1. metaprogramming
    {
        cout << "power\n";
        cout << power<5, 2>::value << endl;
        cout << power<2, -1>::value << endl;
        cout << power<5, 0>::value << endl;

        cout << power_fast<5, 2>::value << endl;
        cout << power_fast<2, 9>::value << endl;
        cout << power_fast<5, 0>::value << endl;
        // cout << power_fast<2, -1>::value << endl;
        cout << endl;

        cout << "absolute value\n";
        cout << absolute<int, 0>::value << endl;
        cout << absolute<int, 5>::value << endl;
        cout << absolute<int, -5>::value << endl;

        cout << absolute_alt<int, 5>::value << endl;
        cout << absolute_alt<int, -5>::value << endl;
        cout << endl;

        cout << "Max of 3\n";
        cout << max_3<int, 5, 5, 5>::value << endl;
        cout << max_3<int, 5, 10, -10>::value << endl;
        cout << max_3<int, 100, 0, 101>::value << endl;
        cout << endl;

        cout << "Number of digits\n";
        static_assert(digits_count<123345>::value == 6, "digits_count<123345>::value");
        static_assert(digits_count<404>::value == 3, "digits_count<123345>::value");
        static_assert(digits_count<0>::value == 1, "digits_count<123345>::value");
        cout << digits_count<112038700, true>::value    << endl;
        cout << digits_count<150 * 34>::value           << endl;
        cout << digits_count<0>::value                  << endl;
        cout << digits_count<0, false>::value           << endl;


        cout << "Divisor count\n";
        cout << divisor_count<5>::value << endl;
        cout << divisor_count<6>::value << endl;
        cout << divisor_count<12>::value << endl;
        cout << endl;
    }

    // type manipulation
    {
        cout << "is array\n";
        cout << is_array<int>::value << endl;
        cout << is_array<decltype(arr)>::value << endl;
        cout << is_array<decltype(arr2)>::value << endl;
        cout << endl;


        cout << "is pointer\n";
        cout << is_pointer<int*>::value << endl;
        cout << is_pointer<int>::value << endl;
        cout << is_pointer<decltype(arr)>::value << endl;
        cout << endl;

        cout << "is same type\n";
        cout << is_same<int, float>::value << endl;
        cout << is_same<int, int>::value << endl;
        cout << endl;
        
        cout << "array size\n";
        cout << extent<decltype(arr)>::value << endl;
        cout << extent<decltype(arr)>::value << endl;
        cout << endl;


        cout << "dimensions\n";
        cout << rank<decltype(arr)>::value << endl;
        cout << rank<decltype(arr2)>::value << endl;
        cout << endl;

    }
    
}