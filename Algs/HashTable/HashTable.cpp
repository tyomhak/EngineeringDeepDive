#include "HashTable.h"
#include <vector>
#include <cmath>

int main()
{
    int point_count = 500;
    int dim_range = 100000;

    std::vector<Point3> points{};
    for (auto i = 0; i < point_count; ++i)
    {
        points.push_back(Point3(rand() % dim_range, rand() % dim_range, rand() % dim_range));
    }

    auto hash_func_sum = [](const Point3& p) {
        return p.x + p.y + p.z;
    };

    auto hash_prime_mult = [](const Point3& p) {
        return p.x * 5 + p.y * 7 + p.z * 11;
    };

    auto hash_prime_pow = [](const Point3& p) {
        return pow(p.x * 13, 3) + pow(p.y * 17, 5) + pow(p.z * 19, 7);
    };


    HashTable<Point3, 200> ht(hash_prime_mult);
    for (auto p : points)
        ht.insert(p);

    ht.print();
}