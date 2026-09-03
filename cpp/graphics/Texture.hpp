#pragma once

#include <SDL3/SDL.h>

//Parent class for everything that can be displayed on screen
namespace MusicLibAnal::cpp::graphics{
    /*
    TL --- T --- TR
    |     |     |
    |     |     |
    L --- C --- R
    |     |     |
    |     |     |
    BL --- B --- BR

    T =  Top, L = Left, B = Bottom, R = Right, C = Centre
    */
    typedef enum {
        TOPLEFT,
        TOPRIGHT,
        BOTTOMLEFT,
        BOTTOMRIGHT,
        TOP,
        BOTTOM,
        LEFT,
        RIGHT,
        CENTRE
    } TexturePoint;

    class Texture{
        public:
            //constructors
            Texture();
            Texture(float pX, float pY);

            //destructors
            ~Texture();
            void destroy();

            //change the position of the texture
            virtual void setPosition(float pX, float pY, TexturePoint point = TOPLEFT);
            virtual void setX(float pX);
            virtual void setY(float pY);

            //change the size of the texture
            void setWidth(float pW);
            void setHeight(float pH);
            void setSize(float pW, float pH);
            void setRect(const SDL_FRect& pRect);
            void setRect(float pX, float pY, float pW, float pH);

            //change alpha
            void setAlpha(Uint8 a);

            //display item to screen
            virtual void render(SDL_Renderer* gRenderer, SDL_FRect* clip = nullptr);

            //accessory
            float* getPosition();
            float* getSize();
            SDL_FRect getRect();
            SDL_Texture* getTexture();

        protected:
            //texture that is displayed
            SDL_Texture* texture;

            //x and y of the top left corner
            float x, y, w, h;

            //width and height of the texture, along with alpha
            int a;
    };
}