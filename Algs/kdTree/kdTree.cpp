
#include <iostream>
#include <memory>
#include <cstdlib>

struct Point
{
    int x, y;
};

struct Node
{
    Node(Node* par, const Point& p) 
    : parent(par)
    , point(p)
    {}

    Point point{0,0};

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

        insert(head.get(), point, true);
    }



    Point NNSearch(const Point& p)
    {

    }

    void debug_print()
    {
        if (!head) return;
        print("", head.get(), false);
    }


private:
    Point NNSearch(const Point& p, const Node* head)
    {
        
    }

    void insert(Node* head, const Point& point, bool is_hor)
    {
        auto smaller_x = [](const Point& l, const Point& r) { return l.x < r.x; };
        auto smaller_y = [](const Point& l, const Point& r) { return l.y < r.y; };

        auto comp_op = is_hor ? smaller_x : smaller_y;

        auto& ptr_ref = comp_op(point, head->point) ? head->l : head->r;
        if (ptr_ref != nullptr)
            insert(ptr_ref.get(), point, !is_hor);
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

        std::cout << prefix + curr_prefix << "(" << node->point.x << "," << node->point.y << ")" << std::endl;

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
        Point pt{ rand() % 30, rand() % 10};
        tree.insert(pt);
    }

    tree.debug_print();
}