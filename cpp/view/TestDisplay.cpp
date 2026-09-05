#include "TestDisplay.hpp"

#include "../graphics/Rectangle.hpp"

using namespace MusicLibAnal::graphics;

namespace MusicLibAnal::view {
    void testDisplay(SDL_Renderer* rn) {
        Rectangle rect1 {5,5,60,60};
        Rectangle rect2 {100,100,60,60};

        rect1.setColour(SDL_Color{255,255,255});
        rect2.setColour(SDL_Color{255,255,255});

        rect2.setFilled(false);
        rect2.setThickness(5);

        rect1.render(rn);
        rect2.render(rn);
    }
}