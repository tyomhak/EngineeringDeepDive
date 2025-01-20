#include <vector>

#include "HashTableOA.h"

int main()
{
    int value_count = 500;
    int max_value = 10000;

    std::vector<int> points{};
    for (auto i = 0; i < value_count; ++i)
        points.push_back(std::rand() % max_value);

    int table_size = 500;
    HashOA<int> ht(table_size);

    for (auto p : points)
    {    
        ht.insert(p);
        ht.print();
    }

    ht.print_clusters_length();

    for (auto p : points)
    {
        ht.remove(p);
        ht.print();
    }
}