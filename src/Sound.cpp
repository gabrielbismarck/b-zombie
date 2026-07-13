#include "Sound.h"
#include <iostream>

#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include <Resources.h>

Sound::Sound(){
    chunk = nullptr;
    channel = -1;
}
Sound::Sound(std::string file) : Sound() {
    Open(file);
}

// void Sound::Play(int times) {
//     // Mix_PlayChannel retorna o número do canal onde o som foi reproduzido ou -1 em caso de erro
//     channel = Mix_PlayChannel(-1, chunk.get(), times -1); // times - 1 porque o parâmetro é o número de repetições, e não o número total de vezes que o som deve ser reproduzido
//     if (channel == -1) {
//         std::cerr << "Erro ao reproduzir o som: " << Mix_GetError() << std::endl;
//     }
// }

void Sound::Play(int times) {
    if (chunk != nullptr) {
        channel = Mix_PlayChannel(-1, chunk.get(), times - 1); 
    }
}

void Sound::Stop() {
    if (chunk != nullptr) {
        Mix_HaltChannel(channel); // Para o canal específico onde o som está sendo reproduzido
    }
}

void Sound::Open(std::string file) {
    chunk = Resources::GetSound(file);
    
    if (chunk == nullptr) {
        std::cerr << "Erro ao carregar o som: " << file << " Erro: " << Mix_GetError() << std::endl; // Imprime o erro específico do SDL_mixer ao invés de usar o SDL_GetError()

    }
}

Sound::~Sound() {}

bool Sound::isOpen() {
    return chunk != nullptr;
}