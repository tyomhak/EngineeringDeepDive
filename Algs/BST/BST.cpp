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
    std::vector<int> vals{};
    for (int i = 0; i < 15; ++i)
    {
        // bst.insert(rand() % 100);
        vals.push_back(i);
    }
    
    bst<int> bst(vals);
    bst.print();
    std::cout << "Balanceness: " << bst.balanceness() << std::endl;

    // INTERACTIVE BST //
    // commands:
    // insert <num>
    // remove <num>
    // check
    // flip
    // rprint
    // preorder_print
    // exit
    std::string input_str;
    while (std::getline(std::cin, input_str))
    {
        input_str = to_lower(input_str);
        if (input_str == "check")
        {
            std::cout << (bst.is_valid() ? "BST is valid!\n" : "BST is NOT valid!\n");
            continue;
        }
        if (input_str == "flip")
        {
            const auto recursive = false; 
            if (recursive)
                bst.flip();
            else
                bst.flip_iterative();
                
            bst.print();
            std::cout << (bst.is_valid() ? "BST is valid!\n" : "BST is NOT valid!\n");
            continue;
        }
        if (input_str == "rprint")
        {
            for (auto it = bst.rbegin(); it != bst.rend(); --it)
                std::cout << it._node->val << ", ";
            std::cout << std::endl;
        }
        if (input_str == "inorder_print")
        {
            bst.inorder_action_iterative([](auto val){ std::cout << val << ", ";});
            std::cout << std::endl;
        }
        if (input_str == "preorder_print")
        {
            bst.pre_order_action_iterative([](int i){ std::cout << i << ", "; });
            // bst.pre_order_action_recursive([](int i){ std::cout << i << ", "; });
            std::cout << std::endl;
        }
        if (input_str == "exit")
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

            bst.print();
        }
        std::cout << "Balanceness: " << bst.balanceness() << std::endl;
        
        std::cout << "\n\n";
    }
    
    return 0;
}