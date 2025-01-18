#include "HashTable.h"
#include <vector>
#include <cmath>


struct point_hash_sum
{
    size_t operator()(const Point3& p) const {
        return size_t(p.x + p.y + p.z);
    }
};

struct point_hash_mult
{
    size_t operator()(const Point3& p) const {
        return p.x * 5 + p.y * 7 + p.z * 11;
    }
};

struct point_hash_pow
{
    size_t operator()(const Point3& p) const {
        return pow(p.x * 13, 3) + pow(p.y * 17, 5) + pow(p.z * 19, 7);
    }
};


int main()
{
    int point_count = 150;
    int dim_range = 100000;

    std::vector<Point3> points{};
    for (auto i = 0; i < point_count; ++i)
    {
        points.push_back(Point3(rand() % dim_range, rand() % dim_range, rand() % dim_range));
    }

    HashTable<Point3> ht{};
    for (auto p : points)
        ht.insert(p);

    HashTable<Point3, point_hash_sum> ht_sum{};
    for (auto p : points)
        ht_sum.insert(p);

    HashTable<Point3, point_hash_pow> ht_pow{};
    for (auto p : points)
        ht_pow.insert(p);
    

    // ht.print();
    std::cout << "Default, e.g. mult by primes and sum \n";
    ht.print_stats();

    std::cout << "\n\nSum\n";
    ht_sum.print_stats();

    std::cout << "\nPow\n";
    ht_pow.print_stats();

    Point3 p1 = Point3(-1, -1, -1);
    std::cout << "\nPoint" << p1 << " found: " << (ht.contains(p1) ? "true" : "false") << std::endl;
    std::cout << "Point" << points[3] << " found: " << (ht.contains(points[3]) ? "true" : "false" ) << "\n" << std::endl;

    for (auto p : points)
    {
        ht.remove(p);
    }
    ht.print_stats();
}