#include <iostream>
#include "Resources.h"
#include "Sprite.h"
#include "Game.h"

#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include "Camera.h"

Sprite::Sprite() {
    frameCountW = 1;
    frameCountH = 1;
    currentFrame = 0;
    texture = nullptr;
    cameraFollower = false; 

}

Sprite::Sprite(std::string file, int frameCountW, int frameCountH){
    texture = nullptr;
    this->frameCountW = frameCountW;
    this->frameCountH = frameCountH;
    currentFrame = 0;
    Open(file);
}

Sprite::~Sprite() {}

void Sprite::Open(std::string file) {
    texture = Resources::GetImage(file);

    if (texture == nullptr) {
        std::cout << "Erro ao carregar textura: " << SDL_GetError() << std::endl;
        return;
    }

    // Obtém a largura e altura total da textura usando SDL_QueryTexture
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
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
    
    if(cameraFollower)
        dstRect = {x, y, w, h};
    else
        dstRect = {x - (int)Camera::pos.x, y - (int)Camera::pos.y, w, h};

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