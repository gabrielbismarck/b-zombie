#ifndef TITLESTATE_H
#define TITLESTATE_H

#include "State.h"
#include "Timer.h"

// Estado para a tela de título do jogo
class TitleState : public State {
    public:
        TitleState();
        ~TitleState();

        // Carrega os assets específicos da tela de título
        void LoadAssets() override;

        // Atualiza a lógica (espera Space para iniciar ou ESC para sair)
        void Update(float dt) override;

        // Renderiza os elementos da tela de título
        void Render() override;

        // Inicializa os objetos do estado
        void Start() override;

        // Gerencia pause/resume
        void Pause() override;
        void Resume() override;

        Timer blinkTimer;
        bool showText ;
    };
#endif
