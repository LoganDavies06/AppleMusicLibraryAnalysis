#pragma once

#include <SDL3/SDL.h>

//Parent class for everything that can be displayed on screen

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

        //change alpha
        void setAlpha(Uint8 a);

        //display item to screen
        virtual void render(SDL_Renderer* gRenderer, SDL_FRect* clip = nullptr);

        //accessory
        float* getPosition();
        int* getSize();
        SDL_Texture* getTexture();

    protected:
        //texture that is displayed
        SDL_Texture* texture;

        //x and y of the top left corner
        float x, y;

        //width and height of the texture, along with alpha
        int w, h, a;
};