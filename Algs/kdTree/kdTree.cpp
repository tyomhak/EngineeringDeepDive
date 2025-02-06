
#include <iostream>
#include <cstdlib>


#include <vector>
#include <queue>
#include <memory>
#include <cmath>

using Point = std::vector<int>;

std::ostream& operator<<(std::ostream& os, const Point& point) 
{
    os << "(";
    for (auto it = point.begin(); it != (point.end() - 1); ++it)
        os << *it << ",";
    return os << *point.rbegin() << ")";
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
struct SquareDistComparator
{
    SquareDistComparator(const Point& target_point) : target(target_point) {}

    bool operator()(const Point& l, const Point& r)
    {
        return square_distance(target, l) < square_distance(target, r);
    }

    Point target{};
};

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

    std::vector<Point> NNSearch(const Point& target_point, int n)
    {
        SquareDistComparator cmp(target_point);
        std::priority_queue<Point, std::vector<Point>, SquareDistComparator> pq(cmp);
        NNSearch(target_point, _head.get(), pq, n, 0);

        std::vector<Point> results{};
        results.reserve(pq.size());
        while (!pq.empty())
        {
            results.push_back(pq.top());
            pq.pop();
        }
        return results;
    }

    std::vector<Point> RangeQuery(const Point& min_point, const Point& max_point)
    {
        std::vector<Point> points_in_range{};
        if (!_head) 
            return points_in_range;

        range_query(min_point, max_point, _head.get(), points_in_range, 0);
        return points_in_range;
    }



    void debug_print()
    {
        if (!_head) return;
        print("", _head.get(), false);
    }


private:

    void range_query(const Point& min_point, const Point& max_point, Node* node, std::vector<Point>& points_in_range, int dimention)
    {
        if (!node) return;
        auto& point = node->point;

        bool is_in_range = true;
        for (auto dim = 0; dim < point.size(); ++dim)
        {
            if (smaller(max_point, point, dim) || smaller(point, min_point, dim))
            {
                is_in_range = false;
                break;
            }
        }

        if (is_in_range)
            points_in_range.push_back(point);

        
        if (smaller(min_point, point, dimention) && smaller(point, max_point, dimention))
        {
            range_query(min_point, max_point, node->l.get(), points_in_range, (dimention + 1) % point.size());
            range_query(min_point, max_point, node->r.get(), points_in_range, (dimention + 1) % point.size());
        }
        else if (smaller(max_point, point, dimention))
            range_query(min_point, max_point, node->l.get(), points_in_range, (dimention + 1) % point.size());
        else if (smaller(point, min_point, dimention))
            range_query(min_point, max_point, node->r.get(), points_in_range, (dimention + 1) % point.size());
    }

    void insert(Node* head, const Point& point, int dimention)
    {
        auto& ptr_ref = smaller(point, head->point, dimention) ? head->l : head->r;
        if (ptr_ref != nullptr)
            insert(ptr_ref.get(), point, (dimention + 1) % point.size());
        else
            ptr_ref.reset(new Node(head, point));
    }

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
            if (auto dim_dist = dimention_distance(head->r->point, point, dimention); min_sqr_distance > dim_dist * dim_dist)
                NNSearch(point, head->r.get(), min_sqr_distance, closestPoint, (dimention + 1) % point.size());
        }
        else if (head->l)
        {
            if (auto dim_dist = dimention_distance(head->l->point, point, dimention); min_sqr_distance > dim_dist * dim_dist)
                NNSearch(point, head->l.get(), min_sqr_distance, closestPoint, (dimention + 1) % point.size());
        }
    }

    void NNSearch(const Point& point, const Node* head, std::priority_queue<Point, std::vector<Point>, SquareDistComparator>& pq, int n, int dimention)
    {
         if (!head) return;

        if (head->point.at(2) == 23)
            bool debug_stop = true;

        pq.push(head->point);
        while (pq.size() > n)
            pq.pop();

        bool is_left = smaller(head->point, point, dimention);
        if (is_left)
            NNSearch(point, head->l.get(), pq, n, (dimention + 1) % point.size());
        else
            NNSearch(point, head->r.get(), pq, n, (dimention + 1) % point.size());

        if (is_left && head->r)
        {
            if (auto dim_dist = dimention_distance(head->r->point, point, dimention); (square_distance(pq.top(), point)) > dim_dist * dim_dist || pq.size() < n)
                NNSearch(point, head->r.get(), pq, n, (dimention + 1) % point.size());
        }
        else if (!is_left && head->l)
        {
            if (auto dim_dist = dimention_distance(head->l->point, point, dimention); (square_distance(pq.top(), point)) > dim_dist * dim_dist || pq.size() < n)
                NNSearch(point, head->l.get(), pq, n, (dimention + 1) % point.size());
        }
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
    int num_of_points = 100;
    int max_val = 50;

    for (int i = 0; i < num_of_points; ++i)
    {
        Point pt{ rand() % max_val, rand() % max_val, rand() % max_val};
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

    for (auto target : targets)
    {
        std::cout << "Closest to " << target << " are:" << std::endl;
        auto closest_n = tree.NNSearch(target, 5);
        for (auto point : closest_n)
            std::cout << "    " << point << "\n";
        std::cout << "\n\n";
    }

    std::cout << "Points inside: \n";
    for (auto point_inside : tree.RangeQuery(Point{10,10,10}, Point{30,30,30}))
        std::cout << "    " << point_inside << "\n";
    std::cout << "\n\n";
}