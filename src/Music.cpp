#include <iostream>

#include "Music.h"
#include <Resources.h>

Music::Music() {
    music = nullptr;
}

Music::Music (std::string file) {
    music = nullptr;
    Open (file);
}

Music::~Music () {}

void Music::Play (int times) {
    if (music != nullptr)
        Mix_PlayMusic (music.get(), times);
    
    // Tratamento de erro
    else
        std::cout << "Erro ao carregar musica: " << SDL_GetError() << std::endl;

}

void Music::Stop (int msToStop) {
    if (music != nullptr)
        Mix_FadeOutMusic (msToStop);
}

void Music::Open(std::string file) {
    music = Resources::GetMusic(file);

    if (music == nullptr) {
        std::cout << "Erro ao carregar musica: " << Mix_GetError() << std::endl;
    }
}

bool Music::IsOpen () {
    return music != nullptr;
}