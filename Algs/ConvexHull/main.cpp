#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

#include "Renderer.h"

class ConvexHull : public renderer::RenderEngine
{
public:
    using RenderEngine::RenderEngine;
    using Point = SDL_Point;

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
        fill_screen(Color::Black());
        draw_points();
        if (_points.size() > 3)
            draw_hull();
    }

private:
    void draw_points()
    {
        auto prev_col = set_color(Color::Green());
        for (auto& point : _points)
            draw_circle(point, 15);      

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
        auto hull_points = _points;
        SDL_Point origin{0,0};
        for (auto& p : hull_points)
            origin = origin + p;
        origin = origin / hull_points.size();
        std::cout << origin.x << "," << origin.y << std::endl;

        for (auto &point : hull_points)
            point = point - origin;

        std::sort(hull_points.begin(), hull_points.end(), [](const auto& l, const auto& r) { return atan2(l.y, l.x) < atan2(r.y, r.x); });
        auto points_count = hull_points.size();

        for (auto &point : hull_points)
        {
            draw_line(origin, point + origin);
            SDL_RenderPresent(_renderer);
            SDL_Delay(500);
        }

        for (int i = 0; i < points_count; ++i)
        {
            for (int j = i; j < hull_points.size(); ++j)
            {
                auto p1_ndx = j == 0 ? 0 : hull_points.size() % j;
                auto p2_ndx = hull_points.size() % (j + 1);
                auto p3_ndx = hull_points.size() % (j + 2);

                auto p1 = hull_points[p1_ndx];
                auto p2 = hull_points[p2_ndx];
                auto p3 = hull_points[p3_ndx];

                if ((p2.x - p1.x)*(p3.y - p1.y) - (p2.y - p1.y)*(p3.x - p1.x) > 0)
                {
                    hull_points.erase(hull_points.begin() + p2_ndx);
                    break;
                }
            }
        }

        for (auto &point : hull_points)
            point = point + origin;
        
        return hull_points;
    }

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