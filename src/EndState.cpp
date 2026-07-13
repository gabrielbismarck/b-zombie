#include "EndState.h"
#include "GameData.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Text.h"
#include "InputManager.h"
#include "Game.h"
#include "TitleState.h"
#include "Camera.h"

EndState::EndState() : State() {

    Camera::Unfollow();
    Camera::pos = {0, 0};

    // Criação do background baseado no resultado em GameData
    GameObject* bgGo = new GameObject();
    std::string bgFile = GameData::playerVictory ? "assets/img/Win.png" : "assets/img/Lose.png";
    SpriteRenderer* bgSR = new SpriteRenderer(*bgGo, bgFile);
    bgSR->SetCameraFollower(true); 
    bgGo->AddComponent(bgSR);
    AddObject(bgGo);

    // Seleção da música tema de vitória ou derrota
    std::string musicFile = GameData::playerVictory ? "assets/audio/endStateWin.ogg" : "assets/audio/endStateLose.ogg";
    backgroundMusic.Open(musicFile);
    backgroundMusic.Play();

    // Texto de instrução para o jogador decidir o próximo passo
    GameObject* textGo = new GameObject();
    SDL_Color white = {255, 255, 255, 255};
    std::string msg = "PRESS SPACE TO RESTART OR ESC TO QUIT";
    textGo->AddComponent(new Text(*textGo, "assets/font/neodgm.ttf", 24, Text::BLENDED, msg, white));
    
    // Centraliza o texto na parte inferior da tela
    textGo->box.x = 600 - textGo->box.w / 2;
    textGo->box.y = 800;
    AddObject(textGo);
}

EndState::~EndState() {
    // A limpeza da memória é delegada ao destrutor da classe base
}

void EndState::Update(float dt) {
    InputManager& input = InputManager::GetInstance();

    // Se ESC for pressionado, encerra a aplicação
    if (input.KeyPress(ESCAPE_KEY) || input.QuitRequested()) {
        quitRequested = true;
    }

    // Se ESPAÇO for pressionado, retorna à tela de título
    if (input.KeyPress(SPACE_KEY)) {
        popRequested = true;
        Game::GetInstance().Push(new TitleState());
    }

    UpdateArray(dt); // Atualiza os timers e animações dos objetos
}

void EndState::Render() {
    RenderArray(); // Desenha o background e as instruções na tela
}

void EndState::Start() {
    LoadAssets();
    StartArray(); // Inicializa os componentes dos objetos inseridos
}

void EndState::LoadAssets() {}
void EndState::Pause() {}
void EndState::Resume() {}
