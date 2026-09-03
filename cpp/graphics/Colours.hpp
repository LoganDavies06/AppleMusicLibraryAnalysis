#pragma once

#include<SDL3/SDL.h>

namespace MusicLibAnal::graphics {
    typedef enum {
        BLACK,
        WHITE,
        DARK_GREY,
        GREY,
        RED
    } colName;

    SDL_Color getCol(colName c);
}