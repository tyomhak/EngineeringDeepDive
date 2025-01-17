#include <string>
#include <list>
#include <functional>
#include <iostream>
#include <cstdint>


struct Point3
{
    int x;
    int y;
    int z;

    Point3(int _x, int _y, int _z) : x(_x), y(_y), z(_z)
    {}

    friend std::ostream& operator<< (std::ostream& stream, const Point3& p) {
        stream << "(" << p.x << "," << p.y << "," << p.z << ")";
        return stream;
    }
};

namespace std
{
    template<> struct hash<Point3>
    {
        size_t operator()(const Point3& p) const
        {
            return p.x * 5 + p.y * 7 + p.z * 11;
        }
    };
}


template<class T, class __hash = std::hash<T>>
class HashTable
{
public:
    HashTable()
    : HashTable(200)
    {}

    HashTable(int table_size)
    : _table_size(table_size)
    , _list_table(table_size, std::list<T>())
    {}

    void insert(const T& obj);

    void remove(const T& obj);
    // bool contains(const T& obj) const;

    void print()
    {
        for (int i = 0; i < _table_size; ++i)
        {
            std::cout << _list_table[i].size() << " : ";
            for (auto elem : _list_table[i])
            {
                std::cout << elem << "----";
            }
            std::cout << std::endl;
        }
    }

    void print_stats()
    {
        size_t max_list_length = 0;
        size_t min_list_length = SIZE_MAX;
        size_t avg_list_length = 0;

        for (int i = 0; i < _table_size; ++i)
        {
            max_list_length = std::max(max_list_length, _list_table[i].size());
            min_list_length = std::min(min_list_length, _list_table[i].size());
            avg_list_length += _list_table[i].size();
        }

        avg_list_length = avg_list_length / _table_size;
        std::cout << "Max: " << max_list_length << ", Min: " << min_list_length << ", Avg: " << avg_list_length << std::endl;

        // calculate VARIANCE (for grading hash func)
    }

private:
    size_t hash(const T& obj) { return __hash()(obj); }

    int _table_size;
    std::vector<std::list<T>> _list_table;
};


template<class T, class __hash>
void HashTable<T, __hash>::insert(const T& obj)
{
    auto hash_num = hash(obj);
    hash_num = hash_num % _table_size;
    _list_table[hash_num].insert(_list_table[hash_num].begin(), obj);
}

// template<class T>
// void HashTable<T>::remove(const T& obj)
// {

// }



