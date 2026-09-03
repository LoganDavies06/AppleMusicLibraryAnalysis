#include "Texture.hpp"

namespace MusicLibAnal::graphics {
    Texture::Texture(): 
        texture{ nullptr },
        w{0},
        h{0},
        x{0},
        y(0)
    {}

    Texture::Texture(float pX, float pY): 
        texture{ nullptr },
        w{0},
        h{0},
        x{pX},
        y(pY)
    {}

    Texture::~Texture() {
        destroy();
    }

    void Texture::destroy() {
        SDL_DestroyTexture( texture );
        texture = nullptr;
        w = 0;
        h = 0;
    }

    //sets the poisition of the texture based on point
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
    void Texture::setPosition(float pX, float pY, TexturePoint point) {
        switch (point) {
            case TOPLEFT:
                x = pX;
                y = pY;
                break;
            case TOPRIGHT:
                x = pX - w;
                y = pY;
                break;
            case BOTTOMLEFT:
                x = pX;
                y = pY - h;
                break;
            case BOTTOMRIGHT:
                x = pX - w;
                y = pY - h;
                break;
            case TOP:
                x = pX - w/2.0f;
                y = pY;
                break;
            case BOTTOM:
                x = pX - w/2.0f;
                y = pY - h;
                break;
            case LEFT:
                x = pX;
                y = pY - h/2.0f;
                break;
            case RIGHT:
                x = pX - w;
                y = pY - h/2.0f;
                break;
            case CENTRE:
                x = pX - w/2.0f;
                y = pY - h/2.0f;
                break;
            default:
                x = 0;
                y = 0;
        }
    }

    void Texture::setX(float pX) {
        x = pX;
    }

    void Texture::setY(float pY) {
        y = pY;
    }

    float* Texture::getPosition() {
        float pos[] = {x, y};
        return pos;
    }

    float* Texture::getSize() {
        float size[] = {w, h};
        return size;
    }

    SDL_Texture* Texture::getTexture() {
        return texture;
    }

    void Texture::setAlpha( Uint8 alpha ){
        SDL_SetTextureAlphaMod( texture, alpha );
    }

    void Texture::render(SDL_Renderer* gRenderer, SDL_FRect* clip)
    {
        //Set texture position
        SDL_FRect dstRect{ x, y, w, h };

        if (clip != nullptr){
            dstRect.w = clip->w;
            dstRect.h = clip->h;
        }

        //Render texture
        SDL_RenderTexture( gRenderer, texture, clip, &dstRect );
    }

    void Texture::setWidth(float pW) {
        w = pW;
    }

    void Texture::setHeight(float pH) {
        h = pH;
    }

    void Texture::setSize(float pW, float pH) {
        w = pW;
        h = pH;
    }

    void Texture::setRect(const SDL_FRect& pRect) {
        x = pRect.x;
        y = pRect.y;
        w = pRect.w;
        h = pRect.h;
    }

    void Texture::setRect(float pX, float pY, float pW, float pH) {
        x = pX;
        y = pY;
        w = pW;
        h = pH;
    }

    SDL_FRect Texture::getRect() {
        return SDL_FRect {x, y, w, h};
    }
}