#include <vector>
#include "BST.h"

std::string to_lower(const std::string& str)
{
    auto lower_str = str;
    for (auto& c : lower_str)
        c = tolower(c);
    return lower_str;
}

int main()
{
    // BST bst{};
    bst_impl_parented<int> bst{};

    std::vector<int> values = { 12, 34, 16, 8, 10, 40, 14, 22, 20, 19, 21, 52, 41, 39, 46, 44 };

    for (auto i : values)
    {
        bst.insert(i);
    }

    // std::cout << "Size: " << bst.size() << std::endl;
    // std::cout << "Valid: " << bst.is_valid() << std::endl;
    bst.print();

    // int size = bst.size();
    // for (auto i = 0; i < size; ++i)
    // {
    //     if (auto min_node = bst.min_node())
    //     {
    //         bst.remove(min_node->val);
    //         bst.print();
    //         std::cout << "\n";
    //     }
    //     else
    //         break;
    // }

    std::string input_str;
    while (std::getline(std::cin, input_str))
    {
        input_str = to_lower(input_str);
        if (input_str == "print")
        {
            bst.print();
            continue;
        }
        else if (input_str == "exit")
            break;


        if (auto space_it = std::find(input_str.begin(), input_str.end(), ' '); 
            space_it != input_str.end())
        {
            auto action = std::string(input_str.begin(), space_it);            
            auto number = std::stoi(std::string(space_it + 1, input_str.end()));

            if (action == "insert")
                bst.insert(number);
            else if (action == "remove")
                bst.remove(number);
        }
    }
    

    return 0;
}