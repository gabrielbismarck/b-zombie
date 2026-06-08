#include "Animation.h"
#include "SDL_include.h"

Animation::Animation(int start, int end, float time, SDL_RendererFlip flip) {
    this->frameStart = start;
    this->frameEnd = end;
    this->frameTime = time;
    this->flip = flip; 
}