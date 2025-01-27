#include <iostream>
#include <vector>
#include <algorithm>


template<class T>
int lcs_memo(const std::vector<T>& l, const std::vector<T>& r, std::vector<std::vector<int>>& cache, int l_ndx, int r_ndx)
{
    if (cache[l_ndx][r_ndx] == -1)
    {
        if (l[l_ndx] == r[r_ndx])
            cache[l_ndx][r_ndx] = lcs_memo(l, r, cache, l_ndx - 1, r_ndx - 1) + 1;
        else
        {
            cache[l_ndx][r_ndx] = std::max(
                lcs_memo(l, r, cache, l_ndx - 1, r_ndx),
                lcs_memo(l, r, cache, l_ndx, r_ndx - 1));
        }
    }

    return cache[l_ndx][r_ndx];
}

template<class T>
int lcs_memo(const std::vector<T>& l, const std::vector<T>& r)
{
    std::vector<std::vector<int>> cache(l.size() + 1, std::vector<int>(r.size() + 1, -1));
    for (int i = 0; i < cache.size(); ++i)
        cache[i][0] = 0;
    for (int i = 0; i < cache[0].size(); ++i)
        cache[0][i] = 0;

    return lcs_memo(l, r, cache, l.size(), r.size());
}

template<class T>
std::vector<T> lcs_dp_items(const std::vector<T>& l, const std::vector<T>& r)
{
    std::vector<std::vector<int>> cache(l.size() + 1, std::vector<int>(r.size() + 1, 0));
    std::vector<std::vector<int>> items(l.size() + 1, std::vector<int>(r.size() + 1, -1));

    for (int l_ndx = 1; l_ndx < cache.size(); ++l_ndx)
    {
        for (int r_ndx = 1; r_ndx < cache[0].size(); ++r_ndx)
        {
            if (l[l_ndx - 1] == r[r_ndx - 1])
            {
                cache[l_ndx][r_ndx] = cache[l_ndx - 1][r_ndx - 1] + 1;
                items[l_ndx][r_ndx] = l_ndx;
            }
            else
                cache[l_ndx][r_ndx] = std::max(
                    cache[l_ndx - 1][r_ndx],
                    cache[l_ndx][r_ndx - 1]
                );
        }
    }

    std::vector<T> result_lcs{};
    auto l_ndx = l.size();
    auto r_ndx = r.size();
    while (l_ndx > 0 && r_ndx > 0)
    {
        if (l[l_ndx - 1] == r[r_ndx - 1])
        {
            result_lcs.push_back(l[l_ndx - 1]);
            --l_ndx;
            --r_ndx;
            continue;
        }
        else
        {
            if (cache[l_ndx - 1][r_ndx] < cache[l_ndx][r_ndx - 1])
                --r_ndx;
            else
                --l_ndx;
        }
    }

    std::reverse(result_lcs.begin(), result_lcs.end());
    return result_lcs;
}


int main()
{
    std::vector<char> l{'c', 't', 'g', 'a', 'a', 't'};
    std::vector<char> r{'a', 'c', 'a', 't', 'g', 't'};

    std::cout << "memo LCS length: " << lcs_memo(l, r) << std::endl;
    auto result_lcs = lcs_dp_items(l, r);
    std::cout << "dp LCS length: " << result_lcs.size() << "\n";
    for (auto c : result_lcs)
        std::cout << c;
    std::cout << std::endl;
}