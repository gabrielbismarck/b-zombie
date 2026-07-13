#ifndef SOUND_H
#define SOUND_H

#include <string>
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include <memory>

class Sound {
    public:
        Sound();
        Sound(std::string file);
        ~Sound();

        void Play(int times = 1);
        void Stop();
        void Open(std::string file);
        bool isOpen();

    private:
        // Mix_Chunk* chunk;
        std::shared_ptr<Mix_Chunk> chunk;

        int channel;
};

#endif