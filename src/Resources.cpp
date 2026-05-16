#include "Resources.h"
#include "Game.h"
#include <iostream>


std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;

SDL_Texture* Resources::GetImage(std::string file) {
    // Uso o auto para deduzir o tipo do iterador, e nãp ter que digitar o tipo completo do iterador (std::unordered_map<std::string, SDL_Texture*>::iterator)
    auto i = imageTable.find(file);
    // retorna um iterador para o elemento encontrado, ou imageTable.end() se não encontrado

    if (i != imageTable.end()) {
        // Se encontrou, retorna o segundo elemento do par, que é o ponteiro para a textura
        return i->second;
    }

    // Se não encontrou, carrega a textura usando o renderer do Game
    SDL_Texture* texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    
    if (texture == nullptr) {
        std::cerr << "Erro Resources: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    // Insere na tabela (caminho do arquivo, ponteiro para a textura) para uso futuro
    imageTable[file] = texture;
    return texture;

}

void Resources::ClearImages() {
    for (auto& pair : imageTable) {
        SDL_DestroyTexture(pair.second); // Libera a textura da SDL
    }
    imageTable.clear(); // Esvazia o mapa
}

Mix_Music* Resources::GetMusic(std::string file) {
    auto i = musicTable.find(file);
    if (i != musicTable.end()) {
        return i->second;
    }

    Mix_Music* music = Mix_LoadMUS(file.c_str());
    if (music == nullptr) {
        std::cerr << "Erro Resources: " << Mix_GetError() << std::endl;
        return nullptr;
    }
    musicTable[file] = music;
    return music;

}

void Resources::ClearMusics() {
    for (auto& pair : musicTable) {
        Mix_FreeMusic(pair.second); // Libera a música da SDL
    }
    musicTable.clear(); // Esvazia o mapa de músicas
}

Mix_Chunk* Resources::GetSound(std::string file) {
    auto i = soundTable.find(file);
    if (i != soundTable.end()) {
        return i->second;
    }

    Mix_Chunk* sound = Mix_LoadWAV(file.c_str());
    if (sound == nullptr) {
        std::cerr << "Erro Resources: " << Mix_GetError() << std::endl;
        return nullptr;
    }
    soundTable[file] = sound;
    return sound;
}

void Resources::ClearSounds() {
    for (auto& pair : soundTable) {
        Mix_FreeChunk(pair.second); // Libera o som da SDL
    }
    soundTable.clear(); // Esvazia o mapa de sons
}