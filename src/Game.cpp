#include "../include/Game.h"
#include "Resources.h"
#include "InputManager.h"
#include <SDL2/SDL_ttf.h>
#include <ctime>
#include <cstdlib>
#include <iostream>

Game* Game::instance = nullptr;

Game& Game::GetInstance() {
    if (instance == nullptr) {
        instance = new Game("Gabriel Bismarck - 17/0103323", 1200, 900);
    }
    return *instance;
}


Game::Game (std::string title, int width, int height) {
    if (instance != nullptr) {
        std::cout << "Instância de Game já existe!" << std::endl;
        return;
    }

    
    instance = this;
    window = nullptr;
    renderer = nullptr; 
    storedState = nullptr; // Inicializa o estado pendente como nulo
    frameStart = SDL_GetTicks();
    dt = 0;
    srand(time(NULL)); 

    // Inicialização do SDL e subsistemas (Audio, Video, Timer)
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        std::cout << "Erro SDL: " << SDL_GetError() << std::endl;
        exit(1);
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) exit(1);

    Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3);
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0) exit(1);
    Mix_AllocateChannels(32);

    // Inicializa a SDL_ttf para renderização de texto
    if (TTF_Init() != 0) {
        std::cout << "Erro TTF: " << TTF_GetError() << std::endl;
        exit(1);
    }

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

}

Game::~Game() {
    if (storedState != nullptr) delete storedState;
    
    // Esvazia a pilha de estados para liberar memória
    while (!stateStack.empty()) stateStack.pop();

    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
    Resources::ClearFonts();

    TTF_Quit(); // Finaliza biblioteca de texto
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// Retorna o estado que está no topo da pilha atual
State& Game::GetCurrentState() {
    return *stateStack.top();
}

// agenda o novo estado para ser empilhado no início do próximo frame
void Game::Push(State* state) {
    storedState = state;
}

SDL_Renderer* Game::GetRenderer() {
    return renderer;
}

void Game::Run() {
    // Processa o estado inicial vindo da main
    if (storedState != nullptr) {
        stateStack.push(std::unique_ptr<State>(storedState));
        stateStack.top()->Start();
        storedState = nullptr;
    }

    // O loop roda enquanto houver estados e o atual não pedir Quit
    while (!stateStack.empty() && !stateStack.top()->QuitRequested()) {
        
        // GERENCIAMENTO DA PILHA
        // Se o estado pediu pra sair remove e retoma o de baixo
        if (stateStack.top()->PopRequested()) {
            stateStack.pop();
            Resources::ClearImages();
            Resources::ClearMusics();
            Resources::ClearSounds();
            Resources::ClearFonts();

            if (!stateStack.empty()) stateStack.top()->Resume();
        }

        // Se tem um novo estado agendado, pausa o atual e empilha o novo
        if (storedState != nullptr) {
            if (!stateStack.empty()) stateStack.top()->Pause();
            stateStack.push(std::unique_ptr<State>(storedState));
            stateStack.top()->Start();
            storedState = nullptr;
        }

        // CICLO DE FRAME PADRÃO
        CalculateDeltaTime();
        InputManager::GetInstance().Update();

        SDL_RenderClear(renderer);
        if (!stateStack.empty()) {
            stateStack.top()->Update(dt);
            stateStack.top()->Render();
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(33);
    }
        while (!stateStack.empty()) stateStack.pop();
}

void Game::CalculateDeltaTime() {
    int currentTime = SDL_GetTicks();
    dt = (currentTime - frameStart) / 1000.0f;
    frameStart = currentTime;
}

float Game::GetDeltaTime() {
    return dt;
}