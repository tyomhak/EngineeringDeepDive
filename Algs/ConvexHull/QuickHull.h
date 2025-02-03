#pragma once

#include <algorithm>
#include "ConvexHull.h"

namespace renderer
{


class QuickHull : public ConvexHull
{
public:
    using ConvexHull::ConvexHull;

protected:
    std::vector<Point> get_hull_points() override
    {
        auto& points = _points;
        auto point_x = [](const Point& l, const Point& r){ return l.x < r.x; };
        auto leftmost_point = *std::min_element(points.begin(), points.end(), point_x);
        auto rightmost_point = *std::max_element(points.begin(), points.end(), point_x);

        auto left_points = get_points_outside_triangle(leftmost_point, rightmost_point, points);
        auto right_points = get_points_outside_triangle(rightmost_point, leftmost_point, points);

        std::vector<Point> hull_points{};
        hull_points.reserve(left_points.size() + right_points.size() + 2);
        hull_points.push_back(leftmost_point);
        std::copy(left_points.begin(), left_points.end(), std::back_inserter(hull_points));
        hull_points.push_back(rightmost_point);
        std::copy(right_points.begin(), right_points.end(), std::back_inserter(hull_points));

        return hull_points;
    }

    std::vector<Point> get_points_outside_triangle(const Point& l, const Point& r, const std::vector<Point>& points)
    {
        std::vector<Point> hull_points{};
        if (points.size() <= 2) return hull_points;

        auto point_x = [](const Point& l, const Point& r){ return l.x < r.x; };
        auto leftmost_point = l;
        auto rightmost_point = r;

        auto furthest_point = *get_furthest_point(leftmost_point, rightmost_point, points);
        if (distance(leftmost_point, rightmost_point, furthest_point) <= 0)
            return hull_points;

        auto prev_col = set_color(Color::Red());
        draw_line(leftmost_point, rightmost_point);
        set_color(Color::Blue());
        draw_line(leftmost_point, furthest_point);
        draw_line(furthest_point, rightmost_point);
        set_color(prev_col);
        force_redraw();
        wait(250);

        std::vector<Point> left_points;
        std::vector<Point> right_points;

        std::copy_if(
            points.begin(), 
            points.end(), 
            std::back_inserter(left_points), 
            [this, leftmost_point, rightmost_point, furthest_point](const Point& point) { 
                return point != rightmost_point && point != furthest_point && sign(point, leftmost_point, furthest_point) > 0; 
            }
        );

        std::copy_if(
            points.begin(), 
            points.end(), 
            std::back_inserter(right_points), 
            [this, leftmost_point, rightmost_point, furthest_point](const Point& point) { 
                return point != leftmost_point && point != furthest_point && sign(point, furthest_point, rightmost_point) > 0; 
            }
        );
        auto left_hull = get_points_outside_triangle(leftmost_point, furthest_point, points);
        auto right_hull = get_points_outside_triangle(furthest_point, rightmost_point, points);
        hull_points.reserve(left_hull.size() + right_hull.size() + 1);

        hull_points.insert(hull_points.end(), left_hull.begin(), left_hull.end());
        hull_points.insert(hull_points.end(), furthest_point);
        hull_points.insert(hull_points.end(), right_hull.begin(), right_hull.end());

        return hull_points;
    }

    auto get_furthest_point(const Point& line_start, const Point& line_end, const std::vector<Point>& points) -> std::vector<Point>::const_iterator
    {
        auto less_comp = [this, &line_start, &line_end](const Point& l, const Point& r){ return distance(line_start, line_end, l) < distance(line_start, line_end, r); };
        return std::max_element(points.begin(), points.end(), less_comp);
    }

    float distance(const Point& line_start, const Point& line_end, const Point& point) const
    {
        return float(((line_end.y - line_start.y) * point.x - (line_end.x - line_start.x) * point.y + line_end.x * line_start.y - line_end.y * line_start.x))
            / sqrtf( (line_end.y - line_start.y)*(line_end.y - line_start.y) + (line_end.x - line_start.x) * (line_end.x - line_start.x) );
    }

    float sign(Point p1, Point p2, Point p3)
    {
        return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
    }
};



}