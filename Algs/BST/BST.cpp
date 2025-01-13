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
    // BST bst{}; // without parent
    bst<int> bst{}; // with parent

    for (int i = 0; i < 15; ++i)
    {
        bst.insert(rand() % 100);
    }
    bst.print();
    // bst.flip();

    // INTERACTIVE BST //
    // commands:
    // insert <num>
    // remove <num>
    // check
    // flip
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
            bst.flip();
            bst.print();
            std::cout << (bst.is_valid() ? "BST is valid!\n" : "BST is NOT valid!\n");
            continue;
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
        }
        bst.print();
        
        std::cout << "\n\n";
    }
    
    return 0;
}