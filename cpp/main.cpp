#include<SDL3/SDL.h>
#include<SDL3_image/SDL_image.h>
#include<SDL3_ttf/SDL_ttf.h>
#include<SDL3/SDL_main.h>

#include"graphics/structs.hpp"
#include"graphics/Colours.hpp"
#include"view/TestDisplay.hpp"

namespace graphics = MusicLibAnal::graphics;

struct Window {
    SDL_Window* wn{ nullptr };
    SDL_Renderer* renderer{ nullptr };
};

//set up the SDL Window along with all of the SDL modules
bool init(struct graphics::Dimensions dim, struct Window* wn) {
    bool success{ true };

    //initialise SDL
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Unable to initialise SDL: %s\n", SDL_GetError());
        success = false;
    } 
    else {
        //create a window
        if (!SDL_CreateWindowAndRenderer("Music Library Analysis", dim.w, dim.h, SDL_WINDOW_RESIZABLE, &wn->wn, &wn->renderer)) {
            SDL_Log("Unable to create window: %s\n", SDL_GetError());
            success = false;
        }
        else {
            //set the minimum size of the window
            SDL_SetWindowMinimumSize(wn->wn, dim.w, dim.h);

            //enable VSync
            if (!SDL_SetRenderVSync(wn->renderer, 1)) {
                SDL_Log("Could not enable VSync. Error: %s\n", SDL_GetError());
                success = false;
            }

            //initialise font rendering
            if (!TTF_Init()) {
                SDL_Log("SDL font rendering failed to load. Error: %s\n", SDL_GetError());
                success = false;
            }
        }
    }

    return success;
}

//cleans up resources after app ends
void cleanUp(Window* wn) {
    //cleans up window and renderer
    SDL_DestroyRenderer(wn->renderer);
    SDL_DestroyWindow(wn->wn);
    wn->renderer = nullptr;
    wn->wn = nullptr;

    SDL_Quit();
}

int main() {
    int exitCode{0};

    graphics::Dimensions screenDim{500,500};

    //init window
    Window window;
    if (!init(screenDim, &window)) {
        SDL_Log("Unable to initialize program");
        exitCode = 1;
    }

    if (exitCode == 0) {
        bool quit {false};

        SDL_Color bgCol = graphics::getCol(graphics::DARK_GREY);

        //initialise events
        SDL_Event e;
        SDL_zero(e);

        //main loop
        while (!quit) {
            //polling events
            while (SDL_PollEvent(&e)) {
                //if the user quits
                if (e.type == SDL_EVENT_QUIT) {
                    quit = true;
                }
            }

            //draw background colour
            SDL_SetRenderDrawColor(window.renderer, bgCol.r, bgCol.g, bgCol.b, bgCol.a);
            SDL_RenderClear(window.renderer);

            //all rendering here
            MusicLibAnal::view::testDisplay(window.renderer);

            //refresh screen
            SDL_RenderPresent(window.renderer);
        }
    }

    cleanUp(&window);
    return exitCode;
}