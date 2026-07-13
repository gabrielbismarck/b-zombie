#include "TitleState.h"
#include "StageState.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Text.h"
#include "InputManager.h"
#include "Game.h"
#include "Camera.h"

TitleState::TitleState() : State() {
    // Criação do background da tela de título
    GameObject* bgGo = new GameObject();
    bgGo->AddComponent(new SpriteRenderer(*bgGo, "assets/img/Title.png"));
    AddObject(bgGo);

    // Criação do texto de instrução
    GameObject* textGo = new GameObject();
    // Configura o texto usando a SDL_ttf através do componente Text
    SDL_Color white = {255, 255, 255, 255};
    textGo->AddComponent(new Text(*textGo, "assets/font/neodgm.ttf", 32, Text::BLENDED, "PRESS SPACE TO START", white));
    
    // Posiciona o texto no centro inferior da tela
    textGo->box.x = 600 - textGo->box.w / 2;
    textGo->box.y = 750;
    AddObject(textGo);
}

TitleState::~TitleState() {
    // A limpeza do objectArray é feita automaticamente pelo destrutor da base State
}

void TitleState::LoadAssets() {
    // Pré-carregamento de assets se necessário
}

void TitleState::Start() {
    LoadAssets();
    StartArray(); // Inicializa todos os GameObjects adicionados
}

void TitleState::Update(float dt) {
    InputManager& input = InputManager::GetInstance();

    // Fecha o jogo se o X da janela for clicado
    if (input.QuitRequested()) {
        quitRequested = true;
    }

    // Fecha o jogo se ESC for pressionado
    if (input.KeyPress(ESCAPE_KEY)) {
        quitRequested = true;
    }

    // Transição para o StageState ao pressionar SPACE
    if (input.KeyPress(SPACE_KEY)) {
        // Empilha a fase do jogo sobre a tela de título
        Game::GetInstance().Push(new StageState());
    }

    blinkTimer.Update(dt);
    if (blinkTimer.Get() >= 0.5f) {
        showText = !showText; // Alterna a visibilidade do texto
        blinkTimer.Restart();
    }

    // Atualiza lógica dos objetos (incluindo timers de animação ou pisca-pisca de texto)
    UpdateArray(dt);
}

void TitleState::Render() {
    // Renderiza o primeiro objeto que eh Background, independente do blink
    if (!objectArray.empty()) {
        objectArray[0]->Render();
    }

    // Renderiza os titles se o texto estiver visível
    if (showText) {
        // Começa do índice 1 para não repetir a renderização do background
        for (size_t i = 1; i < objectArray.size(); i++) {
            objectArray[i]->Render();
        }
    }
}

void TitleState::Pause() {
    // Chamado quando o StageState é empilhado
}

void TitleState::Resume() {
    // Chamado quando o jogador volta do StageState (ex: apertou ESC na fase)
    Camera::Unfollow(); // Garante que a câmera resete para a posição (0,0) na tela de título
    Camera::pos = {0, 0}; 

}