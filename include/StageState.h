#ifndef STAGESTATE_H
#define STAGESTATE_H

#include "State.h"
#include "TileSet.h"
#include "Music.h"

// StageState representa o estado principal (a fase do jogo)
class StageState : public State {
    public:
        StageState();
        ~StageState();

        void LoadAssets() override; // Carrega os recursos da fase (Imagens, Sons)
        void Update(float dt) override; // Atualiza a lógica da fase, câmera e colisões
        void Render() override; // Desenha os elementos na tela

        void Start() override; // Inicializa os objetos após a criação do estado
        void Pause() override; // Chamado quando outro estado (ex: Menu) é empilhado
        void Resume() override; // Chamado quando o estado volta ao topo da pilha

    private:
        TileSet* tileSet; // Ponteiro para o tileSet 
        Music backgroundMusic; // Música de fundo específica desta fase 
};

#endif