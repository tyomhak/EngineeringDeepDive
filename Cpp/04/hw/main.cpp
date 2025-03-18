#include <iostream>

#include "multi_array.h"
#include "tuple.h"

int main()
{
    using std::cout;
    using std::endl;


    multi_array< float, 5, 4, 3 > y;

    // 1. volume
    constexpr int volume = y.volume;
    cout << volume << endl; // 60

    // 2. multi_array accessor
    array_get<0,1,0>(y) = 1.1f;
    array_get<1,2,3>(y) = 1.2f;
    array_get<3,2,1>(y) = 1.3f;

    cout << array_get<0,1,0>(y) << ", " 
        << array_get<1,2,3>(y) << ", "
        << array_get<3,2,1>(y) << endl;

    cout << std::is_same<decltype(array_get<0,1,0>(y)), const float&>::value << endl;


    tuple< float, std::string, int > t1( 5.2f, "letter", 61 );
    tuple< float, std::string, int > t2( 5.2f, "letter", 61 );
    tuple< float, std::string, int > t3( 5.2f, "message", 61 );
    tuple< float, std::string, float > t4( 5.2f, "letter", 61.0f );


    // 3. tuple accessor compile time index overflow
    auto v1 = get<0>(t1);
    // auto v4 = get<4>(t1); // error: index overflow

    // 4. tuple equality operator
    cout << (t1 == t2) << endl; // true
    cout << (t1 == t3) << endl; // false
    // cout << (t1 == t4) << endl; // error: different tuple types

    
    return 0;

}