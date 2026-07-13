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
    scale = Vec2{1, 1};
    flip = SDL_FLIP_NONE;
}

Sprite::Sprite(std::string file, int frameCountW, int frameCountH){
    texture = nullptr;
    this->frameCountW = frameCountW;
    this->frameCountH = frameCountH;
    currentFrame = 0;

    scale = Vec2(1, 1); 
    flip = SDL_FLIP_NONE;
    cameraFollower = false;

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
    SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);
    SetClip(0, 0, GetWidth(), GetHeight()); 

}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::SetFrame(int frame) {
    
    if (frame >= (frameCountW * frameCountH) || frame < 0)
        return;

    currentFrame = frame;

    int framWidth = GetWidth();
    int frameHeight = GetHeight();

    
    if (frameCountW > 0) {
        int row = frame / frameCountW; 
        int col = frame % frameCountW;
        
        // Define o recorte (clip) na textura original
        SetClip(col * framWidth, row * frameHeight, framWidth, frameHeight);
    }
}

void Sprite::SetFrameCount(int frameCountW, int frameCountH) {
    this->frameCountW = frameCountW;
    this->frameCountH = frameCountH;
    SetFrame(0);
}
void Sprite::Render(int x, int y, int w, int h, float angle) {
    
    SDL_Rect dstRect;
    
    if(cameraFollower){
        dstRect.x = x;
        dstRect.y = y;
    }
    else{
        dstRect.x = x - (int)Camera::pos.x;
        dstRect.y = y - (int)Camera::pos.y;
    }

    dstRect.w = (w != 0) ? w : GetWidth(); 
    dstRect.h = (h != 0) ? h : GetHeight();

    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture.get(), &clipRect, &dstRect, angle, nullptr, flip);

}

int Sprite::GetWidth() {
    return (int)((width / frameCountW) * scale.x);
}

int Sprite::GetHeight() {
    return (int)((height / frameCountH) * scale.y);

}

bool Sprite::IsOpen() {
    return texture != nullptr;
}

void Sprite::SetScale(float scaleX, float scaleY) {
    if (scaleX != 0) scale.x = scaleX;
    if (scaleY != 0) scale.y = scaleY;
}

void Sprite::SetFlip(SDL_RendererFlip flip) {
    this->flip = flip;
}
