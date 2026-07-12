#include "WaveSpawner.h"
#include "Zombie.h"
#include "Game.h"
#include "Camera.h"
#include "GameObject.h"
#include "State.h"
#include <cmath>
#include <cstdlib>
#include "Character.h"
#include "AIController.h"

WaveSpawner::WaveSpawner(GameObject& associated) : Component(associated) {
    zombieCounter = 0;
    currentWave = 0;

    waves.emplace_back(5, 2.0f);  // Onda 1: 5 zumbis, um a cada 2s
    waves.emplace_back(10, 1.0f); // Onda 2: 10 zumbis, um a cada 1s
    waves.emplace_back(20, 0.5f); // Onda 3: 20 zumbis, um a cada 0.5s
}

void WaveSpawner::Update(float dt) {
    zombieCooldownTimer.Update(dt);

    // Verifica se ainda existem ondas pendentes no vetor
    if (currentWave < (int)waves.size()) {
        
        // Se ainda faltam zumbis para nascer nessa wave e o tempo de cooldown expirou
        if (zombieCounter < waves[currentWave].zombies && zombieCooldownTimer.Get() >= waves[currentWave].cooldown) {
            
            // Gera um ângulo aleatório para definir a direção
            float angle = (rand() % 360) * (M_PI / 180.0f);
            
            // Define um raio de 800 pixels. Como a tela é 1200x900, 800 garante que nasçam fora da visão
            Vec2 spawnOffset = Vec2(800, 0).InclinationRad(angle); 
            
            // Criação do GameObject do inimigo
            GameObject* enemyGo = new GameObject();
            
            // 30% de chance de nascer um NPC, 70% de ser um Zumbi
            if (rand() % 100 < 30) {
                // NPCs usam Character (com a sprite de NPC) e o AIController 
                enemyGo->AddComponent(new Character(*enemyGo, "assets/img/NPC.png", false));
                enemyGo->AddComponent(new AIController(*enemyGo));
            } else {
                enemyGo->AddComponent(new Zombie(*enemyGo));
            }
            
            enemyGo->box.x = Camera::pos.x + 600 + spawnOffset.x; 
            enemyGo->box.y = Camera::pos.y + 450 + spawnOffset.y;
            
            Game::GetInstance().GetState().AddObject(enemyGo);

            zombieCounter++;
            zombieCooldownTimer.Restart();
        } 
        else if (zombieCounter >= waves[currentWave].zombies && Zombie::zombieCount <= 0) {
            currentWave++;
            zombieCounter = 0;
            zombieCooldownTimer.Restart();
        }
    } else {
        associated.RequestDelete();
    }
}


void WaveSpawner::Render() {
}
