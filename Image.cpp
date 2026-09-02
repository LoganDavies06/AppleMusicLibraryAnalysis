#include "Image.hpp"

bool Image::loadImage( std::string path, SDL_Renderer* rn) {
    destroy();

    SDL_Surface* loadedImg = IMG_Load(path.c_str());
    if (loadedImg == nullptr)
    {
        SDL_Log("Unable to load image %s: %s\n", path.c_str(), SDL_GetError());
    }
    else
    {
        texture = SDL_CreateTextureFromSurface(rn, loadedImg);
        if (texture == nullptr)
        {
            SDL_Log("Unable to create texture form surface: %s\n", SDL_GetError());
        }
        else
        {
            w = loadedImg->w;
            h = loadedImg->h;
        }

        SDL_DestroySurface(loadedImg);
    }

    return texture != nullptr;
}