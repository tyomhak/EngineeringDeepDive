#include <iostream>
#include <vector>
#include <algorithm>


template<class T>
int lcs_memo(const std::vector<T>& l, const std::vector<T>& r, std::vector<std::vector<int>>& cache, int l_ndx, int r_ndx, int &computed_count)
{
    if (cache[l_ndx][r_ndx] == -1)
    {
        if (l[l_ndx - 1] == r[r_ndx - 1])
            cache[l_ndx][r_ndx] = lcs_memo(l, r, cache, l_ndx - 1, r_ndx - 1, computed_count) + 1;
        else
        {
            cache[l_ndx][r_ndx] = std::max(
                lcs_memo(l, r, cache, l_ndx - 1, r_ndx, computed_count),
                lcs_memo(l, r, cache, l_ndx, r_ndx - 1, computed_count));
        }

        computed_count++;
    }

    return cache[l_ndx][r_ndx];
}

template<class T>
int lcs_memo(const std::vector<T>& l, const std::vector<T>& r)
{
    int computed_count = 0;
    std::vector<std::vector<int>> cache(l.size() + 1, std::vector<int>(r.size() + 1, -1));
    for (int i = 0; i < cache.size(); ++i)
        cache[i][0] = 0;
    for (int i = 0; i < cache[0].size(); ++i)
        cache[0][i] = 0;

    auto result = lcs_memo(l, r, cache, l.size(), r.size(), computed_count);
    std::cout << "Computed " << (float)computed_count * 100.0f / (float)(l.size() * r.size()) << "% of total." << std::endl;

    return result;
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
    std::vector<char> l{'c', 't', 'g', 'a', 'a', 't', 'g', 'c', 'a', 't', 'g', 'c', 'a', 't', 'g', 'a', 'c', 't', 'g', 'a', 'c', 'g', 't', 'a', 'c', 'g', 't', 'a', 'c', 'g', 't', 'a', 'c', 'g', 't', 'a', 'c', 'g', 't', 'a'};
    std::vector<char> r{'a', 'c', 'a', 't', 'g', 't', 'c', 'a', 't', 'g', 'c', 'a', 't', 'g', 'a', 'c', 't', 'g', 'a', 't', 'c', 'g', 'a', 't', 'c', 'g', 'a', 't', 'c', 'g', 'a', 't', 'c', 'g', 'a', 't', 'c', 'g', 'a', 't'};

    auto lcs_result_memo = lcs_memo(l, r);
    std::cout << "memo LCS length: " << lcs_result_memo << std::endl;

    auto lcs_result_dp = lcs_dp_items(l, r);
    std::cout << "dp LCS length: " << lcs_result_dp.size() << "\n";
    for (auto c : lcs_result_dp)
        std::cout << c;
    std::cout << std::endl;
}