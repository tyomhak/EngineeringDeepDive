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



template<class T, int _table_size = 20>
class HashTable
{
public:
    HashTable(std::function<size_t(const T&)> hash_func) : _hash(hash_func)
    {}

    void insert(const T& obj);

    // void remove(const T& obj);
    // bool contains(const T& obj) const;

    void print()
    {
        size_t max_list_length = 0;
        size_t min_list_length = SIZE_MAX;
        size_t avg_list_length = 0;
        for (int i = 0; i < _table_size; ++i)
        {
            std::cout << _list_table[i].size() << " : ";
            for (auto elem : _list_table[i])
            {
                std::cout << elem << "----";
            }
            std::cout << std::endl;

            max_list_length = std::max(max_list_length, _list_table[i].size());
            min_list_length = std::min(min_list_length, _list_table[i].size());
            avg_list_length += _list_table[i].size();
        }

        avg_list_length = avg_list_length / _table_size;
        std::cout << "Max: " << max_list_length << ", Min: " << min_list_length << ", Avg: " << avg_list_length << std::endl;
    }

private:
    size_t hash(const T& obj) { return _hash(obj); }


    // constexpr static size_t _table_size = 20; 
    std::list<T> _list_table[_table_size];
    std::function<size_t(const T&)> _hash;
};


template<class T, int _table_size>
void HashTable<T, _table_size>::insert(const T& obj)
{
    auto hash_num = hash(obj);
    hash_num = hash_num % _table_size;
    _list_table[hash_num].insert(_list_table[hash_num].begin(), obj);
}

// template<class T>
// void HashTable<T>::remove(const T& obj)
// {

// }



