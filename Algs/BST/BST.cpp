#include <vector>
#include "BST.h"

int main()
{
    BST bst{};
    std::vector<int> values = {34, 16, 8, 10, 14, 22, 20, 19, 21, 52, 41, 39, 46, 44};

    for (auto i : values)
    {
        bst.insert(i);
    }

    std::cout << "Valid: " << bst.is_valid() << std::endl;
    for (int i = 0; i < 52; ++i)
    {
        std::cout << "Contains " << i << " : " << bst.contains(i) << std::endl;
    }

    return 0;
}