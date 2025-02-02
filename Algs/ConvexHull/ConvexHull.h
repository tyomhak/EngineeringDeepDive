#pragma once

#include <vector>

#include "Renderer.h"


namespace renderer
{

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
        if (_points.size() > 2)
            draw_hull();
    }

protected:
    virtual std::vector<Point> get_hull_points() = 0;


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
        if (hull_points.empty()) return;

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

protected:
    std::vector<Point> _points{};
    std::vector<Point> _hull_points{};
};

}