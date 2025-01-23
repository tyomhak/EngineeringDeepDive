#include <vector>
#include <map>
#include <algorithm>

#include <iostream>


class unbounded_knapsack
{
public:
    unbounded_knapsack(const std::vector<std::pair<int,int>>& weight_value_pairs);
    unbounded_knapsack(const std::vector<int>& weights, const std::vector<int>& values);
    virtual ~unbounded_knapsack() = default;

    int max_value(int max_weight);
    std::vector<int> max_value_path(int max_weight);
    std::map<int, int> item_count(int max_weight);

protected:
    size_t item_count() const { return _weights.size(); }

    int weight(int index) const { return _weights.at(index); }
    int value(int index) const { return _values.at(index); }

    std::vector<int> _weights{};
    std::vector<int> _values{};

    std::map<int,int> _best_values{}; // weight -> best value
    std::map<int,int> _prev_index{};  // weight -> last added item
};

unbounded_knapsack::unbounded_knapsack(const std::vector<std::pair<int,int>>& weight_value_pairs)
{
    auto item_count = weight_value_pairs.size();
    _weights.reserve(item_count);
    _values.reserve(item_count);

    for (int i = 0; i < weight_value_pairs.size(); ++i)
    {
        _weights.push_back(weight_value_pairs[i].first);
        _values.push_back(weight_value_pairs[i].second);
    }

    _best_values[0] = 0;
}

unbounded_knapsack::unbounded_knapsack(const std::vector<int>& weights, const std::vector<int>& values)
: _weights(weights)
, _values(values)
{
    _best_values[0] = 0;
}


int unbounded_knapsack::max_value(int max_weight)
{
    if (_best_values.count(max_weight) == 0)
    {
        int best_value = 0;
        int added_index = -1;

        for (int i = 0; i < item_count(); ++i)
        {
            auto prev_weight = max_weight - weight(i);
            if (prev_weight < 0) continue;

            auto curr_value = max_value(prev_weight) + value(i);
            if (curr_value > best_value)
            {
                best_value = curr_value;
                added_index = i;
            }
        }

        _best_values[max_weight] = best_value;
        _prev_index[max_weight] = added_index;
    }

    return _best_values.at(max_weight);
}


std::vector<int> unbounded_knapsack::max_value_path(int max_weight)
{
    std::vector<int> path{};

    if (_prev_index.count(max_weight) == 0)
        max_value(max_weight); // to fill data.

    int curr_weight = max_weight;
    while (curr_weight > 0)
    {
        if (_prev_index.count(curr_weight) == 0)
            break;

        int prev_index = _prev_index.at(curr_weight);
        path.push_back(prev_index);
        curr_weight -= weight(prev_index);
    }
    
    std::reverse(path.begin(), path.end());
    return path;
}

std::map<int, int> unbounded_knapsack::item_count(int max_weight)
{
    std::map<int,int> item_count{};

    if (_prev_index.count(max_weight) == 0)
        max_value(max_weight); // to fill data.

    int curr_weight = max_weight;
    while (curr_weight > 0)
    {
        if (_prev_index.count(curr_weight) == 0)
            break;

        int prev_index = _prev_index.at(curr_weight);

        if (item_count.count(prev_index) == 0)
            item_count[prev_index] = 0;
        item_count[prev_index]++;
        
        curr_weight -= weight(prev_index);
    }

    return item_count;
}


class unbounded_knapsack_dp : public unbounded_knapsack
{
public:
    unbounded_knapsack_dp(int max_weight, const std::vector<std::pair<int,int>>& weight_value_pairs) 
    : unbounded_knapsack(weight_value_pairs)
    {
        fill_results(max_weight);
    }

    unbounded_knapsack_dp(int max_weight, const std::vector<int>& weights, const std::vector<int>& values)
    : unbounded_knapsack(weights, values)
    {
        fill_results(max_weight);
    }

private:
    void fill_results(int max_weight)
    {
        for (int curr_weight = 0; curr_weight <= max_weight; ++curr_weight)
        {
            int best_value = 0;
            int added_index = -1;

            for (int item_index = 0; item_index < item_count(); ++item_index)
            {
                auto prev_weight = curr_weight - weight(item_index);
                if (prev_weight < 0) continue;

                auto curr_value = _best_values[prev_weight] + value(item_index);
                if (curr_value > best_value)
                {
                    best_value = curr_value;
                    added_index = item_index;
                }
            }

            _best_values[curr_weight] = best_value;
            _prev_index[curr_weight] = added_index;
        }
    }
};




int main(int argc, char *argv[])
{
    int max_weight = 12;
    if (argc > 1)
    {
        std::string param(argv[1]);
        max_weight = std::stoi(param);
    }

    std::vector<std::pair<int,int>> items {
        {2, 1},
        {3, 4},
        {5, 8},
        {11, 3},
    };
    
    {
        unbounded_knapsack uks(items);
        std::cout << uks.max_value(max_weight) << std::endl;

        for (auto [ndx, count] : uks.item_count(max_weight))
            std::cout << "w: " << items[ndx].first 
                      << ", val: " << items[ndx].second 
                      << ", count: " << count 
                      << std::endl;
    }
    
    std::cout << "\n=============================================\n\n";

    {
        unbounded_knapsack_dp uks(max_weight, items);
        std::cout << uks.max_value(max_weight) << std::endl;
        
        for (auto [ndx, count] : uks.item_count(max_weight))
            std::cout << "w: " << items[ndx].first 
                      << ", val: " << items[ndx].second 
                      << ", count: " << count 
                      << std::endl;
    }
}