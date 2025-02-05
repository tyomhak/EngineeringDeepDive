
#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>


using Point = std::vector<int>;

struct Node
{
    Node(Node* par, const Point& p) 
    : parent(par)
    , point(p)
    {}

    // Point point{0,0};
    Point point{};

    Node* parent{nullptr};
    std::unique_ptr<Node> l{nullptr};
    std::unique_ptr<Node> r{nullptr};
};


class KD_Tree
{
public:

    void insert(const Point& point)
    {
        if (!head)
        {
            head.reset(new Node(nullptr, point));
            return;
        }

        insert(head.get(), point, 0);
    }



    // Point NNSearch(const Point& p)
    // {

    // }

    void debug_print()
    {
        if (!head) return;
        print("", head.get(), false);
    }


private:
    // Point NNSearch(const Point& p, const Node* head, float& min_distance, Node& closestPoint, bool is_hor)
    // {
    //     if (!head) return;
        
    //     if (head->point.)
    // }

    // int square_distance(const Point& l, const Point& r) { return std::abs((l.x - r.x) * (l.x - r.x) + (l.y - r.y) * (l.y - r.y)); }

    int smaller(const Point& l, const Point& r, int dimention)
    {
        return l[dimention] < r[dimention];
    }

    void insert(Node* head, const Point& point, int dimention)
    {
        auto& ptr_ref = smaller(point, head->point, dimention) ? head->l : head->r;
        if (ptr_ref != nullptr)
            insert(ptr_ref.get(), point, (dimention + 1) % point.size());
        else
            ptr_ref.reset(new Node(head, point));
    }



    void print(const std::string& prefix, Node* node, bool isLeft) const
    {
        if (!node) return;

        std::string curr_prefix{};
        std::string next_prefix{};

        if (node != head.get())
        {
            bool has_nodes_below = isLeft && node->parent->r;

            curr_prefix = std::string(has_nodes_below ? "  ╠══" : "  ╚══")
                + std::string(isLeft ? "L" : "R")
                + std::string("═══");
            next_prefix = has_nodes_below ? "  ║     " : "        ";
        }

        std::cout << prefix + curr_prefix << "(";
        for (auto it = node->point.begin(); it != (node->point.end() - 1); it++)
            std::cout << *it << ",";
        std::cout << *node->point.rbegin();
        std::cout << ")" << std::endl;

        print(prefix + next_prefix, node->l.get(), true);
        print(prefix + next_prefix, node->r.get(), false);
    }
    

private:
    std::unique_ptr<Node> head{nullptr};
};


int main()
{
    KD_Tree tree{};

    for (int i = 0; i < 10; ++i)
    {
        Point pt{ rand() % 30, rand() % 30, rand() % 30};
        tree.insert(pt);
    }

    tree.debug_print();
}