#include <vector>
#include <optional>
#include <iostream>
#include <algorithm>
#include <memory>


template<class T, class hash_t = std::hash<T>, bool lazy_rehash = false>
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
    void print_clusters_length() const;

private:
    void _insert(const T& val, std::vector<std::optional<T>>& table);
    void _remove(size_t hash_key, std::vector<std::optional<T>>& table);
    int _search(const T& val, const std::vector<std::optional<T>>& table);

    size_t hash(const T& key, size_t upper_bound) const { return hash_t()(key) % upper_bound; }
    size_t increment(size_t index) const { return increment(index, _table.size()); }
    size_t increment(size_t index, size_t upper_bound) const { return (index + 1) % upper_bound; }
    
    void rehash();
    void rehash(float coefficient);
    
    float load() const 
    {
        auto non_empty_count = std::count_if(_table.begin(), _table.end(), [](const std::optional<T>& o){ return o != std::nullopt; });
        float load = (float)non_empty_count / (float)_table.size();
        return load;
    }

    bool lazy_rehash_running() const { return _new_table != nullptr; }


private:
    std::vector<std::optional<T>> _table;
    const size_t _min_size = 8;

    std::unique_ptr<std::vector<std::optional<T>>> _new_table{nullptr};
};



template<class T, class hash_t, bool lazy_rehash>
void HashOA<T, hash_t, lazy_rehash>::insert(const T& val) 
{ 
    rehash();
    return _insert(val, lazy_rehash_running() ? *_new_table : _table); 
}

template<class T, class hash_t, bool lazy_rehash>
void HashOA<T, hash_t, lazy_rehash>::remove(const T& val) 
{ 
    rehash();

    if (lazy_rehash_running())
    {
        if (auto index = _search(val, *_new_table); index != -1)
            _remove(index, *_new_table);
    }

    if (auto index = _search(val, _table); index != -1)
        _remove(index, _table);
}

template<class T, class hash_t, bool lazy_rehash>
bool HashOA<T, hash_t, lazy_rehash>::search(const T& val) const
{
    if (lazy_rehash_running() && _search(val, *_new_table) != -1)
        return true;
    if (auto index = _search(val, _table); index != -1)
        return true;

    return false;
}

template<class T, class hash_t, bool lazy_rehash>
void HashOA<T, hash_t, lazy_rehash>::print() const
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

    std:: cout << "  Load: " << load() << std::endl;
}

template<class T, class hash_t, bool lazy_rehash>
void HashOA<T, hash_t, lazy_rehash>::print_clusters_length() const
{
    size_t first_empty = 0;
    while (_table[first_empty].has_value())
        first_empty = increment(first_empty);
    
    auto start = increment(first_empty);
    while (true)
    {
        while (!_table.at(start).has_value())
        {
            if (start == first_empty)
            {
                std::cout << std::endl;
                return;
            }

            start = increment(start);
        }

        auto end = increment(start);
        while (_table.at(end).has_value())
            end = increment(end);
        
        if (start < end)
            std::cout << (end - start) << ", ";
        else
            std::cout << (end + (_table.size() - start)) << ", ";
        start = end;
    }
}


template<class T, class hash_t, bool lazy_rehash>
void HashOA<T, hash_t, lazy_rehash>::rehash()
{
    const float max_load = 0.75f;
    const float min_load = 0.25f;

    const float upscale = 2.0f;
    const float downscale = 0.5f;

    if (lazy_rehash)
    {
        if (lazy_rehash_running())
        {
            int val_count_to_rehash = 5;
            int rehashed_count = 0;
            for (int i = 0; i < _table.size(); ++i)
            {
                if (_table.at(i).has_value())
                {
                    _insert(_table.at(i).value(), *_new_table);
                    _remove(i, _table);
                    rehashed_count++;

                    if (rehashed_count >= val_count_to_rehash)
                        break;
                }
            }

            if (rehashed_count == 0)
            {
                std::swap(_table, *_new_table);
                _new_table.reset();
            }
        }
        else
        {
            auto start_lazy_rehash = [this](float coefficient)
            {
                size_t new_table_size = std::max(size_t((float)_table.size() * coefficient), _min_size);
                if (new_table_size == _table.size()) return;

                _new_table.reset(new std::vector<std::optional<T>>(new_table_size, std::nullopt));
                rehash();
            };

            float curr_load = load();
            if (curr_load > max_load)
                start_lazy_rehash(upscale);
            else if (curr_load < min_load)
                start_lazy_rehash(downscale);
        }
    }
    else
    {
        const float max_load = 0.75f;
        const float min_load = 0.25f;

        const float upscale = 2.0f;
        const float downscale = 0.5f;

        float curr_load = load();
        if (curr_load > max_load)
            rehash(upscale);
        else if (curr_load < min_load)
            rehash(downscale);
    }
}

template<class T, class hash_t, bool lazy_rehash>
void HashOA<T, hash_t, lazy_rehash>::rehash(float coefficient)
{
    size_t new_table_size = std::max(size_t((float)_table.size() * coefficient), _min_size);
    if (new_table_size == _table.size()) return;

    std::vector<std::optional<T>> new_table(new_table_size, std::nullopt);
    for (auto& val_opt : _table)
    {
        if (val_opt.has_value())
            _insert(val_opt.value(), new_table);
    }

    std::swap(_table, new_table);
}

template<class T, class hash_t, bool lazy_rehash>
void HashOA<T, hash_t, lazy_rehash>::_insert(const T& val, std::vector<std::optional<T>>& table)
{
    auto hash_key = hash(val, table.size());
    while (table.at(hash_key) != std::nullopt)
        hash_key = increment(hash_key, table.size());

    table[hash_key] = val;
}

template<class T, class hash_t, bool lazy_rehash>
void HashOA<T, hash_t, lazy_rehash>::_remove(size_t to_remove_ndx, std::vector<std::optional<T>> &table)
{
    auto table_size = table.size();
    if (!table.at(to_remove_ndx).has_value())
        return;

    table.at(to_remove_ndx) = std::nullopt;

    auto replacement_ndx = increment(to_remove_ndx, table_size);
    while (table.at(replacement_ndx).has_value())
    {
        auto replacement_value = table.at(replacement_ndx).value();
        auto replacement_hash = hash(replacement_value, table_size);
        if (replacement_hash == replacement_ndx)
        {
            replacement_ndx = increment(replacement_ndx, table_size);
            continue;
        }

        if ((replacement_hash <= to_remove_ndx && to_remove_ndx < replacement_ndx)
            || (to_remove_ndx < replacement_ndx && replacement_ndx < replacement_hash)
            || (replacement_ndx < replacement_hash && replacement_hash <= to_remove_ndx)
            ) 
        {
            table.at(to_remove_ndx) = replacement_value;
            return _remove(replacement_ndx, table);
        }
        
        replacement_ndx = increment(replacement_ndx, table_size);
    }
}

template<class T, class hash_t, bool lazy_rehash>
int HashOA<T, hash_t, lazy_rehash>::_search(const T& val, const std::vector<std::optional<T>>& table)
{
    auto table_size = table.size();
    auto hash_key = hash(val, table_size);

    for (int i = 0; i < table_size; ++i)
    {
        if (table.at(hash_key) == val)
            return hash_key;
        if (!table.at(hash_key).has_value())
            break;

        hash_key = increment(hash_key);
    }
    return -1;
}

