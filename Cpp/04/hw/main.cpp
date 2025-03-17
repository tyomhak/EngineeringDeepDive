#include <iostream>

#include "multi_array.h"
#include "tuple.h"

int main()
{
    using std::cout;
    using std::endl;


    multi_array< float, 5, 4, 3 > y;
    constexpr int volume = y.volume;
    cout << volume << endl;

    // cout << multi_array_accessor<decltype(y), 2, 0,0,0>::get(y) << endl;

    tuple< float, std::string, int > t1( 5.2f, "letter", 61 );
    tuple< float, std::string, int > t2( 5.2f, "letter", 61 );
    tuple< float, std::string, int > t3( 5.2f, "letter", 62 );
    tuple< float, std::string, float > t4( 5.2f, "letter", 61.0f );
    auto v1 = get<0>(t1);
    // auto v4 = get<4>(t1);

    cout << (t1 == t2) << endl;
    cout << (t1 == t3) << endl;
    // cout << (t1 == t4) << endl;

    
    return 0;

}