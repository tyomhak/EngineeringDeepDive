#include <vector>
#include "BST.h"

int main()
{
    BST bst{};
    std::vector<int> values = { 12, 34, 16, 8, 10, 40 }; // 14, 22, 20, 19, 21, 52, 41, 39, 46, 44

    for (auto i : values)
    {
        bst.insert(i);
    }

    std::cout << "Size: " << bst.size() << std::endl;
    std::cout << "Valid: " << bst.is_valid() << std::endl;
    bst.print();

    // for (auto i : values)
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

    return 0;
}