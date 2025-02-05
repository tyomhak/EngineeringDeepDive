
#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>


using Point = std::vector<int>;

// void print(const Point& point)
// {
//     std::cout << "(";
//     for (auto it = point.begin(); it != (point.end() - 1); ++it)
//         std::cout << *it << ",";
//     std::cout << *point.rbegin() << ")";
// }

std::ostream& operator<<(std::ostream& os, const Point& point) 
{
    os << "(";
    for (auto it = point.begin(); it != (point.end() - 1); ++it)
        os << *it << ",";
    return os << *point.rbegin() << ")";
}

struct Node
{
    Node(Node* par, const Point& p) 
    : parent(par)
    , point(p)
    {}

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
        if (!_head)
        {
            _head.reset(new Node(nullptr, point));
            return;
        }

        insert(_head.get(), point, 0);
    }



    Point NNSearch(const Point& point)
    {
        if (!_head)
            throw;

        Point result_point = _head->point;
        int sqr_dist = square_distance(_head->point, point);
        NNSearch(point, _head.get(), sqr_dist, result_point, 0);

        return result_point;
    }

    void debug_print()
    {
        if (!_head) return;
        print("", _head.get(), false);
    }


private:
    void NNSearch(const Point& point, const Node* head, int& min_sqr_distance, Point& closestPoint, int dimention)
    {
        if (!head) return;
        
        if (square_distance(head->point, point) < min_sqr_distance)
        {
            min_sqr_distance = square_distance(head->point, point);
            closestPoint = head->point;
        }

        if (smaller(head->point, point, dimention))
            NNSearch(point, head->l.get(), min_sqr_distance, closestPoint, (dimention + 1) % point.size());
        else
            NNSearch(point, head->r.get(), min_sqr_distance, closestPoint, (dimention + 1) % point.size());



        if (smaller(head->point, point, dimention) && head->r)
        {
            if (min_sqr_distance > dimention_distance(head->r->point, point, dimention))
                NNSearch(point, head->r.get(), min_sqr_distance, closestPoint, (dimention + 1) % point.size());
        }
        else if (head->l)
        {
            if (min_sqr_distance > dimention_distance(head->l->point, point, dimention))
                NNSearch(point, head->l.get(), min_sqr_distance, closestPoint, (dimention + 1) % point.size());
        }
    }

    int square_distance(const Point& l, const Point& r)
    {
        int result = 0;
        for (int dimention = 0; dimention < l.size(); ++dimention)
        {
            result += (l[dimention] - r[dimention]) * (l[dimention] - r[dimention]);
        }
        return result;
    }

    int dimention_distance(const Point& l, const Point& r, int dimention)
    {
        return abs(l.at(dimention) - r.at(dimention));
    }

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

        if (node != _head.get())
        {
            bool has_nodes_below = isLeft && node->parent->r;

            curr_prefix = std::string(has_nodes_below ? "  ╠══" : "  ╚══")
                + std::string(isLeft ? "L" : "R")
                + std::string("═══");
            next_prefix = has_nodes_below ? "  ║     " : "        ";
        }

        std::cout << prefix + curr_prefix << node->point << std::endl;

        print(prefix + next_prefix, node->l.get(), true);
        print(prefix + next_prefix, node->r.get(), false);
    }
    

private:
    std::unique_ptr<Node> _head{nullptr};
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

    std::cout << "\n\n";
    std::vector<Point> targets{
        Point{0,0,0},
        Point{100,0,0},
        Point{0,100,0},
        Point{0,0,100},
        Point{100,100,100},
        Point{10, 10, 10}
    };

    for (auto target : targets)
        std::cout << "Closest to " << target << " is " << tree.NNSearch(target) << std::endl;
}