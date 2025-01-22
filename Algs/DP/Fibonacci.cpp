#include <iostream>
#include <map>
#include <cmath>
#include <vector>

int fib_l(int n, std::map<int, int>& pre_calced)
{
    if (pre_calced.count(n))
        return pre_calced[n];

    auto pre_calc = [&pre_calced](int N) {
        if (pre_calced.count(N) == 0)
            pre_calced[N] = fib_l(N, pre_calced);
    };

    if (n % 2 != 0)
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
    precalced[0] = 0;
    precalced[1] = 1;
    for (int i = 2; i < 6; ++i)
        precalced[i] = precalced[i - 1] + precalced[i - 2];

    return fib_l(n, precalced);
}

int main()
{
    std::vector<int> fib_nums = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181};
    std::vector<int> my_fib_nums{};

    for (int i = 0; i < fib_nums.size(); ++i)
        my_fib_nums.push_back(fib_l(i));
    
    for (int i = 0; i < fib_nums.size(); ++i)
        std::cout << fib_nums[i] << ", ";
    std::cout << "\n";
    for (int i = 0; i < my_fib_nums.size(); ++i)
        std::cout << my_fib_nums[i] << ", ";
    std::cout << "\n";

    for (int i = 0; i < fib_nums.size(); ++i)
    {
        if (fib_nums[i] != my_fib_nums[i])
            std::cout << "Wrong\n";
    }
}
