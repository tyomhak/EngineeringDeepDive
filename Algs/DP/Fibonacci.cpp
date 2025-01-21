#include <iostream>
#include <map>
#include <cmath>

int fib_l(int n, std::map<int, int>& pre_calced)
{
    if (pre_calced.count(n))
        return pre_calced[n];

    auto pre_calc = [&pre_calced](int N) {
        if (pre_calced.count(N) == 0)
            pre_calced[N] = fib_l(N, pre_calced);
    };

    if (n % 2 == 0)
    {
        pre_calc(n / 2);
        pre_calc(n / 2 + 1);

        return pre_calced[n / 2] * pre_calced[n / 2] + pre_calced[n / 2 + 1] * pre_calced[n / 2 + 1];
    }
    else
    {
        pre_calc(n / 2);
        pre_calc(n / 2 - 1);
        pre_calc(n / 2 + 1);
        
        return pre_calced[n / 2] * (pre_calced[n / 2 - 1] + pre_calced[n / 2 + 1]);
    }
}

int fib_l(int n)
{
    std::map<int,int> precalced{};
    precalced[0] = 1;
    precalced[1] = 1;
    for (int i = 2; i < 10; ++i)
        precalced[i] = precalced[i - 1] + precalced[i - 2];

    return fib_l(n, precalced);
}

int main()
{
    for (int i = 0; i < 20; ++i)
        std::cout << fib_l(i) << ", ";
    
    std::cout << std::endl;
}