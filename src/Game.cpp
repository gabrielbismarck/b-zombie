#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
// #include "SDL_include.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include <iostream>

#include "../include/Game.h"
#include <Resources.h>
#include <InputManager.h>

// ponteiro que mantéma instância (única) da classe
Game* Game::instance = nullptr;

/* GetInstance(). Nesse método, a primeira coisa a se
fazer é checar se já há uma instância dela rodando (instance != nullptr),
se já existir, o retorne. Se não existir, instancie a primeira (e única!)
instância de Game usando new.  */

Game& Game::GetInstance() {
    // Cria a instância com o título
    if (instance == nullptr) {
        instance = new Game("Gabriel Bismarck - 17/0103323", 1200, 900);
    }
    return *instance; // retorna a instância como referência
}


/**
 * @brief Construtor da classe Game.
 * @details Inicializa a classe Game com um título e dimensões de janela.
 * @param title Título da janela.
 * @param width Largura da janela em pixels.
 * @param height Altura da janela em pixels.
 */
Game::Game (std::string title, int width, int height) {

    if (instance != nullptr) {
        std::cout << "Já existe uma janela do jogo aberta!" << std::endl;
        return;
    }

    instance = this;
    window = nullptr;
    renderer = nullptr; 
    state = nullptr;
    frameStart = 0;
    dt = 0;

    // Inicia a biblioteca SDL e auxiliares
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        std::cout << "Erro ao iniciar SDL: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Inicia a biblioteca SDL_image
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cout << "Erro ao iniciar SDL_image: " << IMG_GetError() << std::endl;
        exit(1);
    }

    // Inicia a biblioteca de sons
    Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3);

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0) {
        std::cout << "Erro ao iniciar SDL_mixer: " << Mix_GetError() << std::endl;
        exit(1);
    }

    // Aloca 32 canais para produzir e reproduzir 32 sons simultaneamente
    Mix_AllocateChannels(32);

    // Cria a janela com o título e dimensões fornecidas. Posiciona ela no centro da tela
    window = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        0
    );

    if (window == nullptr) {
        std::cout << "Erro ao criar janela: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Cria um renderizador para desenhar na janela
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == nullptr) {
        std::cout << "Erro ao criar renderizador: " << SDL_GetError() << std::endl;
        exit(1);
    }

    state = new State();
}

/**
 * @brief Destrutor da classe Game.
 * @details Libera a memória alocada dinamicamente pela instância da classe Game.
 * Destroi o renderizador, a janela e fecha a biblioteca SDL.
 */
Game::~Game() {
    if (state != nullptr) {
        delete state;
        state = nullptr;
    }

    // Fecha as bibliotecas de imagem e audio
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();

    // Fecha o renderizador e a janela
    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window != nullptr) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    SDL_Quit();
}

State& Game::GetState() {
    return *state;
}

SDL_Renderer* Game::GetRenderer() {
    return renderer;
}

void Game::Run() {
    while (!state->QuitRequested()) {
        
        CalculateDeltaTime();
        InputManager::GetInstance().Update();

        state->Update(dt);
        state->Render();


        SDL_RenderPresent(renderer);
        SDL_Delay(33);
    }

    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
}
    
void Game::CalculateDeltaTime() {
    
    int currentTime = SDL_GetTicks();
    // frameAtual - frameAnterior em segundos
    dt = (currentTime - frameStart) / 1000.0f;
    frameStart = currentTime;
}

float Game::GetDeltaTime() {
    CalculateDeltaTime();
    return dt;
}
