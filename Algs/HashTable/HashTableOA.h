#include <vector>
#include <optional>
#include <iostream>
#include <algorithm>


template<class T, class hash_t = std::hash<T>>
class HashOA
{
public:
    HashOA() : HashOA(20)
    {}
    HashOA(size_t size)
    : _table(size, std::nullopt)
    {}

    void insert(const T& val);
    bool search(const T& val) const;

    void print() const;

private:
    void _insert(const T& val, std::vector<std::optional<T>>& table);
    void rehash(float coefficient);

    size_t hash(const T& key, size_t max_val) const { return hash_t()(key) % max_val; }

    float load() const 
    {
        auto non_empty_count = std::count_if(_table.begin(), _table.end(), [](const std::optional<T>& o){ return o != std::nullopt; });
        float load = (float)non_empty_count / (float)_table.size();
        return load;
    }


private:
    // size_t _curr_table_size;
    std::vector<std::optional<T>> _table;
};



template<class T, class hash_t>
void HashOA<T, hash_t>::insert(const T& val) 
{ 
    float curr_load = load();
    if (curr_load > 0.75f)
        rehash(2.0);
    if (curr_load < 0.5)
        rehash(0.7);

    return _insert(val, _table); 
}

template<class T, class hash_t>
bool HashOA<T, hash_t>::search(const T& val) const
{
    auto table_size = _table.size();
    auto hash_key = hash(val, table_size);
    while (_table.at(hash_key) != std::nullopt)
    {
        if (_table.at(hash_key) == val) return true;
        hash_key = (hash_key + 1) % table_size;
    }
    return false;
}

template<class T, class hash_t>
void HashOA<T, hash_t>::print() const
{
    std::cout << "|";
    for (const auto& i : _table)
    {
        if (i == std::nullopt)
            std::cout << " ";
        else
            std::cout << "*";
    }
    std::cout << "|";

    std:: cout << "  " << load() << std::endl;
}

template<class T, class hash_t>
void HashOA<T, hash_t>::rehash(float coefficient)
{
    size_t new_table_size = size_t(_table.size() * coefficient);
    std::vector<std::optional<T>> new_table(new_table_size, std::nullopt);
    for (auto& val_opt : _table)
    {
        if (val_opt.has_value())
            _insert(val_opt.value(), new_table);
    }

    std::swap(_table, new_table);
}


template<class T, class hash_t>
void HashOA<T, hash_t>::_insert(const T& val, std::vector<std::optional<T>>& table)
{
    auto hash_key = hash(val, table.size());
    while (table.at(hash_key) != std::nullopt)
        hash_key = (hash_key + 1) % table.size(); 

    table[hash_key] = val;
}
