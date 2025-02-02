#include "Renderer.h"

namespace renderer
{

bool operator==(const Point& l, const Point& r) { return l.x == r.x && l.y == r.y; }
Point operator+(const Point& l, const Point& r) { return Point{l.x + r.x, l.y + r.y}; }
Point operator-(const Point& l, const Point& r) { return Point{l.x - r.x, l.y - r.y}; }
Point operator*(const Point& p, float scale) { return Point{ (int)(float(p.x) * scale), (int)(float(p.y) * scale)}; }
Point operator/(const Point& p, float scale) { return p * (1.0 / scale); }

RenderEngine::RenderEngine()
{
    SDL_Init(SDL_INIT_VIDEO);
    _window = SDL_CreateWindow("SDL2 line drawing",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    _renderer = SDL_CreateRenderer(_window, -1, 0);
}

RenderEngine::~RenderEngine()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void RenderEngine::run()
{
    while (!_quit)
    {
        SDL_PollEvent(&_event);
        switch (_event.type)
        {
        case SDL_QUIT:
            _quit = true;
            break;
        case SDL_WINDOWEVENT_RESIZED:
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            request_redraw();
            break;
        default:
            break;
        }

        handle_input(_event);
        render();
    }        
}

RenderEngine::Color RenderEngine::set_color(const Color& new_color) 
{
    auto prev_color = _curr_color;
    _curr_color = new_color;
    SDL_SetRenderDrawColor(_renderer, _curr_color.r, _curr_color.g, _curr_color.b, 255);
    return prev_color;
}

void RenderEngine::clear_screen(const Color& color)
{
    auto prev_color = set_color(color);
    SDL_RenderClear(_renderer);
    set_color(prev_color);
}

void RenderEngine::draw_point(const Point& point)
{
    auto radius = 4;
    SDL_Rect rect{point.x - radius, point.y - radius, radius * 2 + 1, radius * 2 + 1};
    SDL_RenderFillRect(_renderer, &rect);
    SDL_RenderDrawPoint(_renderer, point.x, point.y);
}

void RenderEngine::draw_line(const Point& from, const Point& to)
{
    SDL_RenderDrawLine(_renderer, from.x, from.y, to.x, to.y);
}

void RenderEngine::draw_lines(const std::vector<Point>& points)
{
    if (points.size() < 2) return;
    
    for (auto i = 0; i < points.size() - 1; ++i)
    {
        draw_line(points.at(i), points.at(i + 1));
    }
    draw_line(points.at(points.size() - 1), points.at(0));
}

void RenderEngine::draw_circle(const Point& center, int radius)
{
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        SDL_RenderDrawPoint(_renderer, center.x + x, center.y - y);
        SDL_RenderDrawPoint(_renderer, center.x + x, center.y + y);
        SDL_RenderDrawPoint(_renderer, center.x - x, center.y - y);
        SDL_RenderDrawPoint(_renderer, center.x - x, center.y + y);
        SDL_RenderDrawPoint(_renderer, center.x + y, center.y - x);
        SDL_RenderDrawPoint(_renderer, center.x + y, center.y + x);
        SDL_RenderDrawPoint(_renderer, center.x - y, center.y - x);
        SDL_RenderDrawPoint(_renderer, center.x - y, center.y + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}


void RenderEngine::render()
{
    if (_needs_redraw)
    {
        _needs_redraw = false;
        on_draw();
        SDL_RenderPresent(_renderer);
    }
}

}
