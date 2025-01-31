#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

#include <SDL2/SDL.h>

SDL_Point operator+(const SDL_Point& l, const SDL_Point& r) { return SDL_Point{l.x + r.x, l.y + r.y}; }
SDL_Point operator-(const SDL_Point& l, const SDL_Point& r) { return SDL_Point{l.x - r.x, l.y - r.y}; }
SDL_Point operator*(const SDL_Point& p, float scale) { return SDL_Point{ (int)(float(p.x) * scale), (int)(float(p.y) * scale)}; }
SDL_Point operator/(const SDL_Point& p, float scale) { return p * (1.0 / scale); }


class RenderEngine
{
public:
    struct Color{
        int r; int g; int b;
        
        static Color Black(){ return Color{255, 255, 255};}
        static Color Red(){ return Color{255, 0, 0};}
        static Color Green(){ return Color{0, 255, 0};}
        static Color Blue(){ return Color{0, 0, 255};}
        static Color White() { return Color{0, 0, 0};};
    };

public:
    RenderEngine()
    {
        SDL_Init(SDL_INIT_VIDEO);
        _window = SDL_CreateWindow("SDL2 line drawing",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
        _renderer = SDL_CreateRenderer(_window, -1, 0);
    }
    virtual ~RenderEngine()
    {
        SDL_DestroyRenderer(_renderer);
        SDL_DestroyWindow(_window);
        SDL_Quit();
    }

    // check for user input, and update state
    virtual void handle_input(const SDL_Event& event) = 0;

    // override with custom rendering
    virtual void on_draw() = 0;

    void run()
    {
        while (!_quit)
        {
            SDL_PollEvent(&_event);
            if (_event.type == SDL_QUIT)
            {
                _quit = true;
                break;
            }
            handle_input(_event);
            render();
        }        
    }

    
    Color set_color(const Color& new_color) 
    {
        auto prev_color = _curr_color;
        _curr_color = new_color;
        SDL_SetRenderDrawColor(_renderer, _curr_color.r, _curr_color.g, _curr_color.b, 255);
        return prev_color;
    }

    void fill_screen(const Color& color)
    {
        auto prev_color = set_color(color);
        SDL_RenderClear(_renderer);
        set_color(prev_color);
    }

    void draw_point(const SDL_Point& point);
    void draw_line(const SDL_Point& from, const SDL_Point& to);
    void draw_circle(const SDL_Point& point, int radius);

    void fill_circle(const SDL_Point& point, int radius);

private:
    void render()
    {
        if (_render_changed)
        {
            on_draw();
            SDL_RenderPresent(_renderer);
        }
    }

protected:
    SDL_Window* _window {nullptr};
    SDL_Renderer* _renderer {nullptr};
    SDL_Event _event;
    bool _quit = false;

    bool _render_changed{true};
    Color _curr_color{Color::White()};
};

class ConvexHull : public RenderEngine
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
        default:
            break;
        }
        
    }

    // override with custom rendering
    void on_draw() override
    {}

private:
    std::vector<Point> _points{};
    std::vector<Point> _hull_points{};

};

 
int main(int argc, char ** argv)
{
    std::unique_ptr<RenderEngine> engine(new ConvexHull());
    engine->run();

    // std::vector<SDL_Point> points_list{};
    // bool points_changed = false;
 
    // bool quit = false;
    // SDL_Event event;
 
    
 
    // while (!quit)
    // {
    //     // SDL_Delay(10);
    //     SDL_PollEvent(&event);
 
    //     switch (event.type)
    //     {
    //         case SDL_QUIT:
    //             quit = true;
    //             break;

    //         case SDL_MOUSEBUTTONUP:
    //             if (event.button.button == SDL_BUTTON_LEFT)
    //                 points_list.push_back({event.motion.x, event.motion.y});
    //             else if (event.button.button == SDL_BUTTON_RIGHT)
    //                 points_list.erase(points_list.begin() + points_list.size() - 1);
    //             points_changed = true;
    //     }
 

        
    //     if (points_changed && points_list.size() > 3)
    //     {
    //         points_changed = false;

    //         SDL_SetRenderDrawColor(renderer, 242, 242, 242, 255);
    //         SDL_RenderClear(renderer);
    //         SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);


    //         auto hull_points = points_list;
    //         SDL_Point origin{0,0};
    //         for (auto& p : hull_points)
    //             origin = origin + p;
    //         origin = origin / hull_points.size();
    //         std::cout << origin.x << "," << origin.y << std::endl;

    //         for (auto &point : hull_points)
    //             point = point - origin;

    //         std::sort(hull_points.begin(), hull_points.end(), [](const auto& l, const auto& r) { return atan2(l.y, l.x) < atan2(r.y, r.x); });
    //         auto points_count = hull_points.size();
    //         std::cout << "sort f" << std::endl;

    //         for (int i = 0; i < points_count; ++i)
    //         {
    //             for (int j = i; j < hull_points.size(); ++j)
    //             {
    //                 auto p1_ndx = j == 0 ? 0 : hull_points.size() % j;
    //                 auto p2_ndx = hull_points.size() % (j + 1);
    //                 auto p3_ndx = hull_points.size() % (j + 2);

    //                 auto p1 = hull_points[p1_ndx];
    //                 auto p2 = hull_points[p2_ndx];
    //                 auto p3 = hull_points[p3_ndx];

    //                 if ((p2.x - p1.x)*(p3.y - p1.y) - (p2.y - p1.y)*(p3.x - p1.x) > 0)
    //                 {
    //                     hull_points.erase(hull_points.begin() + p2_ndx);
    //                     break;
    //                 }
    //             }
    //         }

    //         for (auto &point : hull_points)
    //             point = point + origin;


    //         auto it = hull_points.begin();
    //         while (std::next(it) != hull_points.end())
    //         {
    //             SDL_RenderDrawLine(renderer, it->x, it->y, std::next(it)->x, std::next(it)->y);
    //             it = std::next(it);
    //         }
    //         auto last = *hull_points.rbegin();
    //         auto first = *hull_points.begin();
    //         SDL_RenderDrawLine(renderer, last.x, last.y, first.x, first.y);

            

    //         SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    //         for (auto point : points_list)
    //         {
    //             auto radius = 4;
    //             SDL_Rect rect{point.x - radius, point.y - radius, radius * 2 + 1, radius * 2 + 1};
    //             SDL_RenderFillRect(renderer, &rect);
    //             SDL_RenderDrawPoint(renderer, point.x, point.y);
    //         }
    
    //         SDL_RenderPresent(renderer);
    //     }

        
    // }
 
    // // cleanup SDL
 
    
 
    return 0;
}