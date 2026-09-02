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
            Rectangle(float pX, float pY, int pW, int pH);
            Rectangle(SDL_FRect& pRect);

            //change the shape of the rectangle
            void setWidth(int pW);
            void setHeight(int pH);
            void setSize(int pW, int pH);
            void setRect(const SDL_FRect& pRect);
            void setRect(float pX, float pY, int pW, int pH);

            //change the position of the rectangle
            void setPosition(float pX, float pY, TexturePoint point = TOPLEFT) override;
            void setX(float pX) override;
            void setY(float pY) override;

            //change the rectangle colour
            void setColour(int r, int g, int b);
            void setColour(const SDL_Color& col);

            SDL_Color getColour();

            void render(SDL_Renderer* gRenderer, SDL_FRect* clip = nullptr) override;

        private:
            SDL_FRect rect;
            SDL_Color fill;

            //updates the rect variable with the given dimensions
            void updateRect();
    };
}