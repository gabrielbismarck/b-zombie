#ifndef SPRITE_H
#define SPRITE_H

#include <string>

#define INCLUDE_SDL
#include "SDL_include.h"
#include "Vec2.h"

class Sprite {
    public:
        Sprite();
        Sprite(std::string file, int frameCountW = 1, int frameCountH = 1);
        ~Sprite();

        void SetScale (float scaleX, float scaleY);
        Vec2 GetScale();
        void SetFlip (SDL_RendererFlip flip);

        void Open (std::string file);
        void SetClip (int x, int y, int w, int h);
        void Render (int x, int y, int w = 0, int h = 0, float angle = 0);

        void SetFrame(int frame);
        void SetFrameCount(int frameCountW, int frameCountH);

        int GetWidth ();
        int GetHeight ();
        bool IsOpen ();
        bool cameraFollower;

    private:
        int frameCountW;
        int frameCountH;
        int currentFrame;

        SDL_Texture* texture;
        int width;
        int height;
        SDL_Rect clipRect;

        Vec2 scale;
        SDL_RendererFlip flip;
};

#endif
