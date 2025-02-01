#include <SDL2/SDL.h>

SDL_Point operator+(const SDL_Point& l, const SDL_Point& r);
SDL_Point operator-(const SDL_Point& l, const SDL_Point& r);
SDL_Point operator*(const SDL_Point& p, float scale);
SDL_Point operator/(const SDL_Point& p, float scale);


namespace renderer
{
using Point = SDL_Point;




class RenderEngine
{
public:
    struct Color{
        int r; int g; int b;
        
        static Color White(){ return Color{255, 255, 255};}
        static Color Red(){ return Color{255, 0, 0};}
        static Color Green(){ return Color{0, 255, 0};}
        static Color Blue(){ return Color{0, 0, 255};}
        static Color Black() { return Color{0, 0, 0};};
    };

public:
    RenderEngine();
    virtual ~RenderEngine();

    // check for user input, and update state
    virtual void handle_input(const SDL_Event& event) = 0;

    // override with custom rendering
    virtual void on_draw() = 0;

    void run();
    
    void request_redraw() { _needs_redraw = true; }
    Color set_color(const Color& new_color);


    void fill_screen(const Color& color);
    void draw_point(const Point& point);
    void draw_line(const Point& from, const Point& to);
    void draw_circle(const Point& point, int radius);

private:
    void render();

protected:
    SDL_Window* _window {nullptr};
    SDL_Renderer* _renderer {nullptr};
    SDL_Event _event;
    bool _quit = false;

    bool _needs_redraw{true};
    Color _curr_color{Color::White()};
};

}