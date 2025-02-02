#include <iostream>
#include <vector>
#include <stack>
#include <memory>
#include <algorithm>

#include "Renderer.h"

using namespace renderer;

class ConvexHull : public renderer::RenderEngine
{
public:
    using RenderEngine::RenderEngine;

    // check for user input, and update state
    void handle_input(const SDL_Event& event) override
    {
        switch (event.type)
        {
        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT)
                _points.push_back({event.motion.x, event.motion.y});
            else if (event.button.button == SDL_BUTTON_RIGHT)
                _points.erase(_points.begin() + _points.size() - 1);
            request_redraw();
        default:
            break;
        }
        
    }

    // override with custom rendering
    void on_draw() override
    {
        clear_screen(Color::Black());
        draw_points();
        if (_points.size() > 3)
            draw_hull();
    }

private:
    void draw_points()
    {
        auto prev_col = set_color(Color::Green());
        for (auto& point : _points)
            draw_circle(point, 5);      

        set_color(prev_col);
    }

    void draw_hull()
    {
        auto hull_points = get_hull_points();

        auto it = hull_points.begin();
        while (std::next(it) != hull_points.end())
        {
            draw_line(*it, *std::next(it));
            it = std::next(it);
        }
        auto last = *hull_points.rbegin();
        auto first = *hull_points.begin();
        draw_line(last, first);
    }

    std::vector<Point> get_hull_points()
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

    size_t cycl_next(size_t ndx, size_t size, size_t steps = 1) { return size % (ndx + steps); }

private:
    std::vector<Point> _points{};
    std::vector<Point> _hull_points{};
};

 
int main(int argc, char ** argv)
{
    std::unique_ptr<renderer::RenderEngine> engine(new ConvexHull());
    engine->run();
    return 0;
}