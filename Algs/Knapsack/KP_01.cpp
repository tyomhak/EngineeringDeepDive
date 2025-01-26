#include <vector>
#include <map>
#include <algorithm>
#include <functional>

#include <iostream>


struct Item
{
    int weight;
    int value;
};

int knapsack_01(const std::vector<Item>& items, int max_weight)
{
    std::vector<std::vector<int>> table(items.size() + 1, std::vector<int>(max_weight + 1, 0));

    for (int item_ndx = 1; item_ndx < table.size(); ++item_ndx)
    {
        for (int weight = 1; weight < max_weight + 1; ++weight)
        {
            if (items[item_ndx - 1].weight > weight)
                table[item_ndx][weight] = table[item_ndx - 1][weight];
            else
            {
                table[item_ndx][weight] = std::max(
                    table[item_ndx - 1][weight],
                    table[item_ndx - 1][weight - items[item_ndx - 1].weight] + items[item_ndx - 1].value
                );
            }
        }
    }

    return table[items.size()][max_weight];
}

int knapsack_01_memo(const std::vector<Item>& items, int max_weight) {
    std::vector<std::vector<int>> table(items.size(), std::vector<int>(max_weight + 1, -1));
    for (auto &row : table)
        row[0] = 0;

    std::function<int(int,int)> get_max = [&table, &items, &get_max](int upto_item, int weight) {
        if (upto_item < 0) return 0;
        
        if (table[upto_item][weight] == -1) {
            if (items[upto_item].weight > weight)
                table[upto_item][weight] = get_max(upto_item - 1, weight);
            else
                table[upto_item][weight] = std::max(
                    get_max(upto_item - 1, weight),
                    get_max(upto_item - 1, weight - items[upto_item].weight) + items[upto_item].value
                );
        }

        return table[upto_item][weight];
    };
    return get_max(items.size() - 1, max_weight);
}



class knapsack_01
{
public:
    knapsack_01(const std::vector<std::pair<int,int>>& weight_value_pairs, int max_weight)
    {
        for (auto [weight, value] : weight_value_pairs)
        {
            _weights.push_back(weight);
            _values.push_back(value);
        }

        fill_max_value_table(max_weight);
    }
    knapsack_01(const std::vector<int>& weights, const std::vector<int>& values, int max_weight)
    : _weights(weights)
    , _values(values)
    {
        fill_max_value_table(max_weight);
    }

    int max_value(int weight) { return _max_value_table[_weights.size() - 1][weight]; }
    int max_value_items();

private:
    int weight(int item_index) const { return _weights.at(item_index); }
    int value(int item_index) const { return _values.at(item_index); }

    void fill_max_value_table(int max_weight)
    {
        while (_max_value_table.size() < _weights.size())
            _max_value_table.push_back(std::vector<int>(max_weight, 0));
        
        for (auto &row : _max_value_table)
        {
            while (row.size() <= max_weight)
                row.push_back(0);
        }


        for (int curr_weight = 0; curr_weight <= max_weight; ++curr_weight)
        {
            for (int item = 0; item < _weights.size(); ++item)
            {
                if (weight(item) >= curr_weight)
                    _max_value_table[item][curr_weight] = max_value(curr_weight, item - 1);
                else
                    _max_value_table[item][curr_weight] = std::max(
                        max_value(curr_weight, item - 1),
                        max_value(curr_weight - weight(item)) + value(item)
                    );
            }
        }
    }


    int max_value(int weight, int up_to_index)
    {
        if (weight <= 0 || up_to_index < 0) return 0;
        return _max_value_table[up_to_index][weight];
    }


private:
    std::vector<int> _weights;
    std::vector<int> _values;

    std::vector<std::vector<int>> _max_value_table{}; // [up to item index][max weight]
};









int main(int argc, char *argv[])
{
    int max_weight = 7;
    if (argc > 1)
    {
        std::string param(argv[1]);
        max_weight = std::stoi(param);
    }

    // std::vector<std::pair<int,int>> items {
    //     {2, 1},
    //     {3, 4},
    //     {5, 8},
    //     {11, 3},
    // };

    std::vector<Item> items{
        {2, 1},
        {3, 4},
        {5, 8},
        {11, 3}
    };

    std::cout << knapsack_01(items, max_weight) << std::endl;
    std::cout << knapsack_01_memo(items, max_weight) << std::endl;
    
    {
        // knapsack_01 uks(items, max_weight);
        // std::cout << uks.max_value(max_weight) << std::endl;

        // for (auto [ndx, count] : uks.item_count(max_weight))
        //     std::cout << "w: " << items[ndx].first 
        //               << ", val: " << items[ndx].second 
        //               << ", count: " << count 
        //               << std::endl;
    }
}