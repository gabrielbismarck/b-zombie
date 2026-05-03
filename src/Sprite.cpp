#include <iostream>

#include "Sprite.h"
#include "Game.h"

#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

Sprite::Sprite() {
    frameCountW = 1;
    frameCountH = 1;
    currentFrame = 0;
    texture = nullptr;
    // width = 0;
    // height = 0;
    // clipRect = {0, 0, 0, 0};
}

Sprite::Sprite(std::string file, int frameCountW, int frameCountH){
    texture = nullptr;
    this->frameCountW = frameCountW;
    this->frameCountH = frameCountH;
    currentFrame = 0;
    // width = 0;
    // height = 0;
    // clipRect = {0, 0, 0, 0};

    Open(file);
}

Sprite::~Sprite() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        // texture = nullptr;
    }
}

void Sprite::Open(std::string file) {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        // texture = nullptr;
    }

    texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());

    if (texture == nullptr) {
        std::cout << "Erro ao carregar textura: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    // SetClip(0, 0, width, height);
    SetFrame(0);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::SetFrame(int frame) {
    currentFrame = frame;

    int framWidth = GetWidth();
    int frameHeight = GetHeight();


    int row = frame / frameCountW;
    int col = frame % frameCountW;

    SetClip(col * framWidth, row * frameHeight, framWidth, frameHeight);
}

void Sprite::SetFrameCount(int frameCountW, int frameCountH) {
    this->frameCountW = frameCountW;
    this->frameCountH = frameCountH;
    SetFrame(0);
}
void Sprite::Render(int x, int y, int w, int h) {
    
    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = w;
    dstRect.h = h;

    SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect);
}

int Sprite::GetWidth() {
    return width / frameCountW;
}

int Sprite::GetHeight() {
    return height / frameCountH;
}

bool Sprite::IsOpen() {
    return texture != nullptr;
}