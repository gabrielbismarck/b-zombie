#include "SpriteRenderer.h"
#include "GameObject.h"

SpriteRenderer::SpriteRenderer(GameObject& associated) : Component(associated) {}

SpriteRenderer::SpriteRenderer(GameObject& associated, std::string file, int frameCountW, int frameCountH) : Component(associated), sprite(file, frameCountW, frameCountH) {
    associated.box.w = sprite.GetWidth();
    associated.box.h = sprite.GetHeight();
}

void SpriteRenderer::Open(std::string file) {
    sprite.Open(file);
    associated.box.w = sprite.GetWidth();
    associated.box.h = sprite.GetHeight();
    SetFrame(0);
}

void SpriteRenderer::SetFrameCount(int frameCountW, int frameCountH) {
    sprite.SetFrameCount(frameCountW, frameCountH);
}

void SpriteRenderer::Update(float dt) {
    // O SpriteRenderer não tem nada para atualizar, mas poderia ter animação ou algo do tipo
}
void SpriteRenderer::SetFrame(int frame, SDL_RendererFlip flip) {
    sprite.SetFlip(flip);
    sprite.SetFrame(frame);
}

void SpriteRenderer::Render() {
    sprite.Render((int)associated.box.x, (int)associated.box.y, (int)associated.box.w, (int)associated.box.h, (float)associated.angleDeg);
}

void SpriteRenderer::SetCameraFollower(bool follower) {
    sprite.cameraFollower = follower;
}

void SpriteRenderer::SetScale(float scaleX, float scaleY) {
    float centerX = associated.box.x + (associated.box.w / 2.0f);
    float centerY = associated.box.y + (associated.box.h / 2.0f);

    sprite.SetScale(scaleX, scaleY);

    associated.box.w = sprite.GetWidth();
    associated.box.h = sprite.GetHeight();

    associated.box.x = centerX - (associated.box.w / 2.0f);
    associated.box.y = centerY - (associated.box.h / 2.0f);
}

void SpriteRenderer::SetFlip(SDL_RendererFlip flip) {
    sprite.SetFlip(flip);
}
