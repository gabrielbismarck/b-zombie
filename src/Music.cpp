#include <iostream>

#include "Music.h"

Music::Music() {
    music = nullptr;
}

Music::Music (std::string file) {
    music = nullptr;
    Open (file);
}

Music::~Music () {
    if (music != nullptr) {
        Mix_FreeMusic (music);
        music = nullptr;
    }
}

void Music::Play (int times) {
    if (music != nullptr)
        Mix_PlayMusic (music, times);
    
    // Tratamento de erro
    else
        std::cout << "Erro ao carregar musica: " << SDL_GetError() << std::endl;

}

void Music::Stop (int msToStop) {
    if (music != nullptr)
        Mix_FadeOutMusic (msToStop);
}

void Music::Open(std::string file) {
    if (music != nullptr) {
        Mix_FreeMusic(music);
        music = nullptr;
    }

    music = Mix_LoadMUS(file.c_str());

    if (music == nullptr) {
        std::cout << "Erro ao carregar musica: " << Mix_GetError() << std::endl;
    }
}

bool Music::IsOpen () {
    return music != nullptr;
}