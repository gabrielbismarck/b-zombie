#ifndef ENDSTATE_H
#define ENDSTATE_H

#include "State.h"
#include "Music.h"

// EndState: Estado responsável por exibir as telas de Win/Lose
class EndState : public State {
    public:
        EndState();
        ~EndState();

        // Implementação dos métodos virtuais da classe base State
        void LoadAssets() override;
        void Update(float dt) override;
        void Render() override;

        void Start() override;
        void Pause() override;
        void Resume() override;

    private:
        // Música de fundo específica para vitória ou derrota
        Music backgroundMusic; 
};

#endif