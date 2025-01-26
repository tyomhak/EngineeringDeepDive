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

std::vector<Item> knapsack_01_items_dp(const std::vector<Item>& items, int max_weight)
{
    std::vector<std::vector<int>> table(items.size() + 1, std::vector<int>(max_weight + 1, 0));
    std::map<int, Item> used_items{};

    for (int item_ndx = 1; item_ndx < table.size(); ++item_ndx) {
        for (int weight = 1; weight < max_weight + 1; ++weight) {
            table[item_ndx][weight] = table[item_ndx - 1][weight];

            if (items[item_ndx - 1].weight <= weight) {
                auto with_item_value = table[item_ndx - 1][weight - items[item_ndx - 1].weight] + items[item_ndx - 1].value;
                if (table[item_ndx][weight] < with_item_value) {
                    table[item_ndx][weight] < with_item_value;
                    used_items[weight] = items.at(item_ndx - 1);
                }
            }
        }
    }

    std::vector<Item> result_items{};
    auto item_ndx = used_items.at(max_weight);
    auto curr_weight = max_weight;
    while (curr_weight > 0 && used_items.count(curr_weight)) {
        result_items.push_back(used_items.at(curr_weight));
        curr_weight -= used_items.at(curr_weight).weight;
    }
    return result_items;
}



int main(int argc, char *argv[])
{
    int max_weight = 15;
    if (argc > 1)
    {
        std::string param(argv[1]);
        max_weight = std::stoi(param);
    }
    std::vector<Item> items{
        {2, 1},
        {3, 4},
        {5, 8},
        {11, 3}
    };

    std::cout << knapsack_01(items, max_weight) << std::endl;
    std::cout << knapsack_01_memo(items, max_weight) << std::endl;
    
    auto result_items = knapsack_01_items_dp(items, max_weight);
    auto result_value = 0;
    auto result_weight = 0;
    for (auto item : result_items) {
        std::cout << "{" << item.weight << ", " << item.value << "}";
        result_value += item.value;
        result_weight += item.weight;
    }
    std::cout << std::endl;
    std::cout << "Value: " << result_value << "\n";
    std::cout << "Weight: " << result_weight << "\n";

    
}