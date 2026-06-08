#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H
#include "Component.h"
#include "Sprite.h"

class SpriteRenderer : public Component {
    public:
        SpriteRenderer(GameObject& associated);
        SpriteRenderer(GameObject& associated, std::string file, int frameCountW = 1, int frameCountH = 1);

        void Open(std::string file);
        void Update(float dt) override;
        void Render() override;
        void SetFrame(int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void SetFrameCount(int frameCountW, int frameCountH);
        
        void SetScale(float scaleX, float scaleY);

        void SetCameraFollower(bool follower);

        void SetFlip(SDL_RendererFlip flip);

    private:
        Sprite sprite;
};

#endif