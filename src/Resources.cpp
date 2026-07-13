#include "Resources.h"
#include "Game.h"
#include <iostream>

// Tabelas agora armazenam shared_ptr para gerenciamento automático
std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> Resources::imageTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Music>> Resources::musicTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> Resources::soundTable;
std::unordered_map<std::string, std::shared_ptr<TTF_Font>> Resources::fontTable;

std::shared_ptr<SDL_Texture> Resources::GetImage(std::string file) {
    auto it = imageTable.find(file);
    if (it != imageTable.end()) return it->second;

    // Carrega a textura normalmente
    SDL_Texture* texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    if (texture == nullptr) {
        std::cerr << "Erro Resources (Image): " << SDL_GetError() << std::endl;
        return nullptr;
    }

    // Cria shared_ptr com lambda para desalocação correta via SDL
    std::shared_ptr<SDL_Texture> ptr(texture, [](SDL_Texture* t) { SDL_DestroyTexture(t); });
    imageTable[file] = ptr;
    return ptr;
}

void Resources::ClearImages() {
    // Remove apenas recursos que não estão sendo usados por ninguém (count == 1)
    for (auto it = imageTable.begin(); it != imageTable.end();) {
        if (it->second.unique()) it = imageTable.erase(it);
        else it++;
    }
}

std::shared_ptr<Mix_Music> Resources::GetMusic(std::string file) {
    auto it = musicTable.find(file);
    if (it != musicTable.end()) return it->second;

    Mix_Music* music = Mix_LoadMUS(file.c_str());
    if (music == nullptr) {
        std::cerr << "Erro Resources (Music): " << Mix_GetError() << std::endl;
        return nullptr;
    }

    // Deleção via Mix_FreeMusic
    std::shared_ptr<Mix_Music> ptr(music, [](Mix_Music* m) { Mix_FreeMusic(m); });
    musicTable[file] = ptr;
    return ptr;
}

void Resources::ClearMusics() {
    for (auto it = musicTable.begin(); it != musicTable.end();) {
        if (it->second.unique()) it = musicTable.erase(it);
        else it++;
    }
}

std::shared_ptr<Mix_Chunk> Resources::GetSound(std::string file) {
    auto it = soundTable.find(file);
    if (it != soundTable.end()) return it->second;

    Mix_Chunk* sound = Mix_LoadWAV(file.c_str());
    if (sound == nullptr) {
        std::cerr << "Erro Resources (Sound): " << Mix_GetError() << std::endl;
        return nullptr;
    }

    // Deleção via Mix_FreeChunk
    std::shared_ptr<Mix_Chunk> ptr(sound, [](Mix_Chunk* c) { Mix_FreeChunk(c); });
    soundTable[file] = ptr;
    return ptr;
}

void Resources::ClearSounds() {
    for (auto it = soundTable.begin(); it != soundTable.end();) {
        if (it->second.unique()) it = soundTable.erase(it);
        else it++;
    }
}

std::shared_ptr<TTF_Font> Resources::GetFont(std::string file, int fontSize) {
    std::string key = file + std::to_string(fontSize);
    auto it = fontTable.find(key);
    if (it != fontTable.end()) return it->second;

    TTF_Font* font = TTF_OpenFont(file.c_str(), fontSize);
    if (font == nullptr) {
        std::cerr << "Erro Resources (Font): " << TTF_GetError() << std::endl;
        return nullptr;
    }

    // Deleção via TTF_CloseFont
    std::shared_ptr<TTF_Font> ptr(font, [](TTF_Font* f) { TTF_CloseFont(f); });
    fontTable[key] = ptr;
    return ptr;
}

void Resources::ClearFonts() {
    for (auto it = fontTable.begin(); it != fontTable.end(); ) {
        if (it->second.unique()) {
            it = fontTable.erase(it);
        } else {
            it++;
        }
    }
}