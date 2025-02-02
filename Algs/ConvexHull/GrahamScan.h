
#include "ConvexHull.h"

namespace renderer
{

class GrahamScan : public ConvexHull
{
public:
    using ConvexHull::ConvexHull;

protected:
    std::vector<Point> get_hull_points() override
    {
        const int animation_step = 200;
        auto hull_points = _points;

        auto lowest_point_ndx = 0;
        for (int i = 0; i < hull_points.size(); ++i)
        {
            if (hull_points.at(i).y < hull_points.at(lowest_point_ndx).y)
                lowest_point_ndx = i;
        }

        Point origin = hull_points.at(lowest_point_ndx);
        hull_points.erase(hull_points.begin() + lowest_point_ndx);
        auto is_lower = [origin](const Point& l, const Point& r) {
            return atan2(l.y - origin.y, l.x - origin.x) >= atan2(r.y - origin.y, r.x - origin.x); 
        };
        std::sort(hull_points.begin(), hull_points.end(), is_lower);
        hull_points.insert(hull_points.begin(), origin);

        std::vector<Point> st{};
        st.push_back(hull_points.at(0));
        st.push_back(hull_points.at(1));

        for (int ndx = 2; ndx < hull_points.size(); ndx++)
        {
            auto mid_point = st.back();
            st.pop_back();
            auto next_point = hull_points.at(ndx);
            while (!st.empty() && turn_direction(st.back(), mid_point, next_point) > 0)
            {
                mid_point = st.back();
                st.pop_back();

                clear_screen(Color::Black());
                draw_lines(st);
                draw_points();
                force_redraw();
                wait(animation_step);
            }
            st.push_back(mid_point);
            st.push_back(next_point);

            clear_screen(Color::Black());
            draw_lines(st);
            draw_points();
            force_redraw();
            wait(animation_step);
        }

        hull_points.clear();
        while (!st.empty())
        {
            hull_points.push_back(st.back());
            st.pop_back();
        }

        return hull_points;
    }

    int turn_direction(const Point &p1, const Point &p2, const Point &p3)
    {
        return (p2.x - p1.x)*(p3.y - p1.y) - (p2.y - p1.y)*(p3.x - p1.x);
    }
};

}