#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include "Texture.hpp"

namespace MusicLibAnal::graphics {

    //child class of 'Texture'
    class Image: public Texture {
        public:
            //loads an image to the texture from the given file path
            bool loadImage( std::string path, SDL_Renderer* rn);

            void resetSize();
    };
}