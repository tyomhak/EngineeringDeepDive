
#include <iostream>
#include <vector>
#include <functional>

class tournament_tree
{
public:
    tournament_tree(std::function<int(int,int)> func, const std::vector<int>& values)
    : _func(func)
    {
        _tree.push_back(values);
        int size = values.size();
        while (size > 0)
        {
            auto new_size = size / 2 + size % 2;
            _tree.push_back(std::vector<int>(new_size, 0));
            auto& prev_level = *(_tree.rbegin() + 1);
            auto& this_level = *(_tree.rbegin());
            for (int i = 0; i < new_size; ++i)
            {
                if (prev_level.size() > ((i * 2) + 1))
                    this_level.at(i) = _func(prev_level.at(i * 2), prev_level.at(i * 2 + 1));
                else
                    this_level.at(i) = prev_level.at(i * 2);
            }
            size = new_size;

            if (size == 1) 
                break;
        }
    }

    int query(int from, int to)
    {
        int result = value(from);

        int level = 0;
        while (from < to)
        {
            if (from % 2)
            {
                result = _func(result, _tree.at(level).at(from)); // value(from));
                from++;
            }
            if (to % 2)
            {
                result = _func(result, _tree.at(level).at(to));
                to--;
            }
            
            from /= 2;
            to /= 2;
            level++;
        }

        result = _func(result, _tree.at(level).at(from));
        return result;
    }

    // void set(int at, int val)
    // {
    //     _tree[0].at(at) = val;

    //     for (int level = 1; level < _tree.size(); ++level)
    //     {
    //         if (at % 2)
    //         {
    //             _tree.at(level).at(at / 2) =  _func(_tree.at(level - 1).at(at - 1), _tree.at(level - 1).at(at));
    //         }
    //         else
    //         {
    //             if (_tree.at(level - 1).size() > at + 1)
    //                 _tree.at(level).at(at / 2) =  _func(_tree.at(level - 1).at(at), _tree.at(level - 1).at(at + 1));
    //             else
    //                 _tree.at(level).at(at / 2) = _tree.at(level - 1).at(at);
    //         }
    //     }
    // }

    void debug_print()
    {
        for (auto level : _tree)
        {
            for (auto val : level)
                std::cout << val << ", ";
            std::cout << std::endl;
        }
    }

private:
    int value(int ndx) { return _tree.at(0).at(ndx); }


private:
    std::vector<std::vector<int>> _tree{};
    std::function<int(int,int)> _func{};
};




int main()
{
    tournament_tree tree([](int l, int r) -> int { return std::max(l, r); }, std::vector<int>{100,2,3,45,6,7,32});
    tree.debug_print();
    std::cout << tree.query(2, 5) << std::endl;
}