#ifndef ANIMATION_H
#define ANIMATION_H

#define INCLUDE_SDL
#include "SDL_include.h"

class Animation {
    public:
        
    
    SDL_RendererFlip flip;
    int frameStart;
    int frameEnd;
    float frameTime;
    
    Animation(int frameStart = 0, int frameEnd = 0, float frameTime = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
};

#endif 