#ifndef RESOURCES_H
#define RESOURCES_H

#include <string>
#include <unordered_map>
#include "SDL_include.h"

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

class Resources {
    public:
        static SDL_Texture* GetImage(std::string file);
        static void ClearImages();

        static Mix_Music* GetMusic(std::string file);
        static void ClearMusics();

        static Mix_Chunk* GetSound(std::string file);
        static void ClearSounds();

    private:
        // Hash tables, chave: caminho do arquivo (string), valor: ponteiro para o a imagem, música ou som carregado
        static std::unordered_map<std::string, Mix_Music*> musicTable;
        static std::unordered_map<std::string, SDL_Texture*> imageTable;
        static std::unordered_map<std::string, Mix_Chunk*> soundTable;
};

#endif