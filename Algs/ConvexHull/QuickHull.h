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
        auto hull_points = _points;
        auto point_x = [](const Point& l, const Point& r){ return l.x < r.x; };
        auto leftmost_point = *std::min_element(hull_points.begin(), hull_points.end(), point_x);
        auto rightmost_point = *std::max_element(hull_points.begin(), hull_points.end(), point_x);

        remove_points_inside_triangle(leftmost_point, rightmost_point, hull_points);

        // auto furthest_point = *get_furthest_point(leftmost_point, rightmost_point, hull_points);
        // for (auto point : hull_points)
        // {
        //     auto is_inside = [this, leftmost_point, rightmost_point, furthest_point](const Point& point)
        //     {
        //         return (point != leftmost_point) && (point != rightmost_point) && (point != furthest_point) &&
        //             point_inside_triangle(point, leftmost_point, rightmost_point, furthest_point); 
        //     };
        //     std::erase_if(hull_points, is_inside);
        // }




        return hull_points;
    }

    void remove_points_inside_triangle(const Point& l, const Point& r, std::vector<Point>& points)
    {
        auto point_x = [](const Point& l, const Point& r){ return l.x < r.x; };
        auto leftmost_point = l; // *std::min_element(points.begin(), points.end(), point_x);
        auto rightmost_point = r; // *std::max_element(points.begin(), points.end(), point_x);

        auto furthest_point = *get_furthest_point(leftmost_point, rightmost_point, points);
        if (distance(leftmost_point, rightmost_point, furthest_point) <= 0)
            return;

        // auto prev_color = set_color()
        draw_lines({leftmost_point, rightmost_point, furthest_point});
        wait(200);

        auto prev_col = set_color(Color::Black());
        for (auto& point : points)
            draw_point(point);
        set_color(prev_col);

        for (auto point : points)
        {
            auto is_inside = [this, leftmost_point, rightmost_point, furthest_point](const Point& point)
            {
                return (point != leftmost_point) && (point != rightmost_point) && (point != furthest_point) &&
                    point_inside_triangle(point, leftmost_point, rightmost_point, furthest_point); 
            };
            std::erase_if(points, is_inside);
        }

        for (auto& point : points)
            draw_point(point);
        wait(200);

        // // render for debug
        // {
        //     clear_screen();
        //     draw_points();

        //     auto prev_col = set_color(Color::Red());
        //     draw_lines({leftmost_point, rightmost_point, furthest_point});
        //     for (auto point : points)
        //     {
        //         draw_circle(point, 7);
        //     }
        //     set_color(prev_col);
        //     force_redraw();
        // }

        remove_points_inside_triangle(leftmost_point, furthest_point, points);
        remove_points_inside_triangle(furthest_point, rightmost_point, points);
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

    bool point_inside_triangle(const Point& point, const Point& p1, const Point& p2, const Point& p3)
    {
        float d1, d2, d3;
        bool has_neg, has_pos;

        d1 = sign(point, p1, p2);
        d2 = sign(point, p2, p3);
        d3 = sign(point, p3, p1);

        has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
        has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

        return !(has_neg && has_pos);
    }

    float sign(Point p1, Point p2, Point p3)
    {
        return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
    }
};



}