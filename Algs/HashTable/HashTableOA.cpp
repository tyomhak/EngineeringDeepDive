#include <vector>

#include "HashTableOA.h"

int main()
{
    int point_count = 40;
    int dim_range = 500;

    std::vector<int> points{};
    for (auto i = 0; i < point_count; ++i)
    {
        points.push_back(std::rand() % dim_range);
    }

    HashOA<int> ht(15);
    for (auto p : points)
    {    
        ht.insert(p);
        ht.print();
    }

    for (auto p : points)
    {
        ht.remove(p);
        ht.print();
    }
}