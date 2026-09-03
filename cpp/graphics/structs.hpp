#pragma once

namespace MusicLibAnal::graphics {
    struct Dimensions {
        int w;
        int h;

        constexpr Dimensions(int pWidth, int pHeight) : w(pWidth), h(pHeight) {}
    };

    struct Position {
        float x;
        float y;

        constexpr Position(int pX, int pY) : x(pX), y(pY) {}
    };
}