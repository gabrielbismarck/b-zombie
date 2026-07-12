#ifndef WAVE_SPAWNER_H
#define WAVE_SPAWNER_H

#include "Component.h"
#include "Timer.h"
#include <vector>


struct Wave {
    int zombies;      // Quantidade total de zumbis que nascem nas ondas
    float cooldown;   // Tempo de espera em segundos entre o spawn dos zumbi
    Wave(int z, float c) : zombies(z), cooldown(c) {}
};

class WaveSpawner : public Component {
public:
    WaveSpawner(GameObject& associated);
    
    void Update(float dt) override;
    
    void Render() override;

private:
    int zombieCounter;           // Conta os zumbis já spawnados
    int currentWave;             // Índice da wave atual
    std::vector<Wave> waves;     // Lista com as definições waves do nível
    Timer zombieCooldownTimer;   // Timer para controle do cooldown de spawn
};

#endif