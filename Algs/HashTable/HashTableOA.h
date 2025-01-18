#include <vector>
#include <optional>
#include <iostream>
#include <algorithm>


template<class T, class hash_t = std::hash<T>>
class HashOA
{
public:
    HashOA() : HashOA(_min_size)
    {}
    HashOA(size_t size)
    : _table(size, std::nullopt)
    {}

    void insert(const T& val);
    void remove(const T& val);
    bool search(const T& val) const;

    void print() const;

private:
    void _insert(const T& val, std::vector<std::optional<T>>& table);
    void _remove(const T& val, std::vector<std::optional<T>>& table);

    size_t hash(const T& key, size_t max_val) const { return hash_t()(key) % max_val; }

    void rehash()
    {
        const float max_load = 0.75f;
        const float min_load = 0.3f;
        const float upscale = 2.0f;
        const float downscale = 0.5f;

        float curr_load = load();
        if (curr_load > max_load)
            rehash(upscale);
        if (_table.size() > _min_size && curr_load < min_load)
            rehash(downscale);
    }
    void rehash(float coefficient);
    
    float load() const 
    {
        auto non_empty_count = std::count_if(_table.begin(), _table.end(), [](const std::optional<T>& o){ return o != std::nullopt; });
        float load = (float)non_empty_count / (float)_table.size();
        return load;
    }


private:
    std::vector<std::optional<T>> _table;
    const int _min_size = 8;
};



template<class T, class hash_t>
void HashOA<T, hash_t>::insert(const T& val) 
{ 
    rehash();
    return _insert(val, _table); 
}

template<class T, class hash_t>
void HashOA<T, hash_t>::remove(const T& val) 
{ 
    return _remove(val, _table);
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

template<class T, class hash_t>
void HashOA<T, hash_t>::_remove(const T& val, std::vector<std::optional<T>>& table)
{
    auto table_size = table.size();
    auto hash_key = hash(val, table_size);
    if (table.at(hash_key).has_value())
    {
        table.at(hash_key) = std::nullopt;

        auto repl_key = (hash_key + 1) % table_size;
        while (table.at(repl_key) != std::nullopt)
        {
            auto curr_val = table.at(repl_key).value();
            auto curr_val_key = hash(curr_val, table_size);
            // if (curr_val_key < )

            repl_key = (repl_key + 1) % table_size;
        }
    }
}