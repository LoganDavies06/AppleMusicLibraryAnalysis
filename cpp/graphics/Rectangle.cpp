#include "Rectangle.hpp"
#include <vector>

namespace MusicLibAnal::graphics {
    Rectangle::Rectangle()
        : Texture(),
        rect{},
        filled {true},
        thickness {1}
    {}

    Rectangle::Rectangle(float pX, float pY)
        : Texture(pX, pY),
        rect {},
        filled {true},
        thickness {1}
    {
        rect.x = pX;
        rect.y = pY;
    }

    Rectangle::Rectangle(float pX, float pY, float pW, float pH)
        : Texture(pX, pY),
        rect {},
        filled {true},
        thickness {1}
    {
        w = pW;
        h = pH;

        rect.x = pX;
        rect.y = pY;
        rect.w = pW;
        rect.h = pH;
    }

    Rectangle::Rectangle(SDL_FRect& pRect)
        : Texture(pRect.x, pRect.y),
        rect {},
        filled {true},
        thickness {1}
    {
        w = pRect.w;
        h = pRect.h;

        rect.x = pRect.x;
        rect.y = pRect.y;
        rect.w = pRect.w;
        rect.h = pRect.h;
    }

    void Rectangle::updateRect() {
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
    }

    void Rectangle::render(SDL_Renderer* rn, SDL_FRect* clip) {
        //sets the colour of the rectangle
        SDL_SetRenderDrawColor(rn, fill.r, fill.g, fill.b, fill.a);
        updateRect();
        std::vector<SDL_FRect> rects;

        //filled rectangle
        if (filled) {
            if (clip != nullptr) {
                rects = {*clip};
            }
            else {
                rects = {rect};
            }
        }
        //rectangle not filled: draw 4 rectangles for border
        else {
            if (clip != nullptr) {
                //left, top, right, bottom
                rects = {
                    SDL_FRect {clip->x, clip->y, thickness, clip->h},
                    SDL_FRect {clip->x, clip->y, clip->w, thickness},
                    SDL_FRect {clip->x + clip->w - thickness, clip->y, thickness, clip->h},
                    SDL_FRect {clip->x, clip->y + clip->h - thickness, clip->w, thickness}
                };
            }
            else {
                //left, top, right, bottom
                rects = {
                    SDL_FRect {x, y, thickness, h},
                    SDL_FRect {x, y, w, thickness},
                    SDL_FRect {x + w - thickness, y, thickness, h},
                    SDL_FRect {x, y + h - thickness, w, thickness}
                };
            }
        }
        
        //render rectangle
        for (const auto& i: rects)
        {
            SDL_RenderFillRect(rn, &i);
        }
    }

    void Rectangle::setColour(int r, int g, int b) {
        fill.r = r;
        fill.g = g;
        fill.b = b;
    }

    void Rectangle::setColour(const SDL_Color& col) {
        fill = col;
    }

    SDL_Color Rectangle::getColour() {
        return fill;
    }

    void Rectangle::setFilled(bool pFilled) { filled = pFilled; }
    bool Rectangle::getFilled() { return filled; }

    void Rectangle::setThickness(float pThickness) { thickness = pThickness; }
    float Rectangle::getThickness() { return thickness; }
}