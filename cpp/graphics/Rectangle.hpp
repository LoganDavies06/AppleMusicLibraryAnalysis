#pragma once

#include <SDL3/SDL.h>
#include "Texture.hpp"

namespace MusicLibAnal::cpp::graphics {
        //child class of 'Texture'
    class Rectangle: public Texture {
        public:
            //constructors
            Rectangle();
            Rectangle(float pX, float pY);
            Rectangle(float pX, float pY, float pW, float pH);
            Rectangle(SDL_FRect& pRect);

            //change the rectangle colour
            void setColour(int r, int g, int b);
            void setColour(const SDL_Color& col);

            SDL_Color getColour();

            void setFilled(bool pFilled);
            bool getFilled();

            void setThickness(float pThickness);
            float getThickness();

            void render(SDL_Renderer* gRenderer, SDL_FRect* clip = nullptr) override;

        private:
            SDL_FRect rect;
            SDL_Color fill;
            bool filled;
            //thickness of border when not filled
            float thickness;

            //updates the rect variable with the given dimensions
            void updateRect();
    };
}