#include "Rectangle.hpp"

Rectangle::Rectangle()
    : Texture(),
    rect{}
{}

Rectangle::Rectangle(float pX, float pY)
    : Texture(pX, pY),
    rect {}
{
    rect.x = pX;
    rect.y = pY;
}

Rectangle::Rectangle(float pX, float pY, int pW, int pH)
    : Texture(pX, pY),
    rect {}
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
    rect {}
{
    w = pRect.w;
    h = pRect.h;

    rect.x = pRect.x;
    rect.y = pRect.y;
    rect.w = pRect.w;
    rect.h = pRect.h;
}

void Rectangle::setWidth(int pW) {
    w = pW;
    updateRect();
}

void Rectangle::setHeight(int pH) {
    h = pH;
    updateRect();
}

void Rectangle::setSize(int pW, int pH) {
    w = pW;
    h = pH;
    updateRect();
}

void Rectangle::setRect(const SDL_FRect& pRect) {
    x = pRect.x;
    y = pRect.y;
    w = pRect.w;
    h = pRect.h;
    updateRect();
}

void Rectangle::setRect(float pX, float pY, int pW, int pH) {
    x = pX;
    y = pY;
    w = pW;
    h = pH;
    updateRect();
}

void Rectangle::updateRect() {
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
}

void Rectangle::setPosition(float pX, float pY, TexturePoint point) {
    Texture::setPosition(pX, pY, point);
    updateRect();
}

void Rectangle::setX(float pX) {
    Texture::setX(pX);
    updateRect();
}

void Rectangle::setY(float pY) {
    Texture::setY(pY);
    updateRect();
}

void Rectangle::render(SDL_Renderer* rn, SDL_FRect* clip) {
    //sets the colour of the rectangle
    SDL_SetRenderDrawColor(rn, fill.r, fill.g, fill.b, fill.a);
    updateRect();
    
    if (clip != nullptr)
    {
        SDL_RenderFillRect(rn, clip);
    }
    else
    {
        SDL_RenderFillRect(rn, &rect);
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