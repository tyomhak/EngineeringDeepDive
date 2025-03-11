#pragma once

/*
1. Power a^N, where N is an integer
*/

// 1.1 O(N)
template<int base, int exponent, bool is_negative>
struct power_impl
{
    constexpr static double value = base * power_impl<base, exponent - 1, is_negative>::value;
};

// specialization for exponent == 0
template<int base, bool is_negative>
struct power_impl<base, 0, is_negative>
{
    constexpr static double value = 1.0;
};

// specialization for negative exponent
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


// 1.2 O(log N)
template<int base, int exponent>
struct power_fast
{
    static_assert(exponent >= 0, "power_fast doesn't support negative exponents.");
    const static int value  = power_fast<base, exponent / 2>::value
                            * power_fast<base, exponent / 2>::value
                            * (exponent % 2 ? base : 1);
                            
    // const static int value = exponent % 2 == 0
    //     ? power_fast<base, exponent / 2> * power_fast<base, exponent / 2>
    //     : power_fast<base, exponent / 2> * power_fast<base, exponent / 2> * base;
};

template<int base>
struct power_fast<base, 0>
{
    const static int value = 1;
};




/*
2. Absolute |X| of given value 'X'
*/
template<typename T, T val, bool is_positive>
struct absolute_impl
{
    const static T value = val;
};

template<typename T, T val>
struct absolute_impl<T, val, false>
{
    const static T value = -val;
};

template<typename T, T val>
struct absolute
{
    const static T value = absolute_impl<T, val, val >= 0>::value;
};


template<typename T, T val>
struct absolute_alt
{
    const static T value = (val >= 0) ? val : -val;
};




/*
3. Maximal of 3 values {A, B, C}
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
4. Number of digits of given integer 'N'
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
5. Number of divisors of 'N'
*/
template<int number, int divisor>
struct divisor_count_helper
{
    const static size_t value = (number % divisor == 0 ? 1 : 0) 
        + divisor_count_helper<number, divisor - 1>::value;
};

template<int number>
struct divisor_count_helper<number, 0>
{
    const static size_t value = 0;
};

template<int number>
struct divisor_count
{
    const static int value = divisor_count_helper<number, number>::value;
};