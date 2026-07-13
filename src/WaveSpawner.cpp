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

// Inicialização da flag estática para controle de vitória no StageState 
bool WaveSpawner::finished = false;

WaveSpawner::WaveSpawner(GameObject& associated) : Component(associated) {
    zombieCounter = 0;
    currentWave = 0;
    
    // Reset da flag no construtor para evitar vitória instantânea em novas partidas
    WaveSpawner::finished = false; 

    // Configuração das ondas de teste (Duas hordas de 3 inimigos)
    waves.clear(); 
    waves.emplace_back(3, 2.0f); // 3 inimigos, um a cada 2 segundos
    waves.emplace_back(3, 2.0f); 
}

void WaveSpawner::Update(float dt) {
    zombieCooldownTimer.Update(dt);

    // Verifica se ainda existem ondas pendentes no vetor
    if (currentWave < (int)waves.size()) {
        
        // Se ainda faltam zumbis para nascer nesta wave e o tempo de espera expirou
        if (zombieCounter < waves[currentWave].zombies && zombieCooldownTimer.Get() >= waves[currentWave].cooldown) {
            
            // Calcula posição aleatória em um raio de 800 pixels (fora da visão da tela)
            float angle = (rand() % 360) * (M_PI / 180.0f);
            Vec2 spawnOffset = Vec2(800, 0).InclinationRad(angle); 
            
            GameObject* enemyGo = new GameObject();
            
            // Sorteio de tipo: 30% NPCs (Character + AI) e 70% Zumbis
            if (rand() % 100 < 30) {
                enemyGo->AddComponent(new Character(*enemyGo, "assets/img/NPC.png", false));
                enemyGo->AddComponent(new AIController(*enemyGo));
            } else {
                enemyGo->AddComponent(new Zombie(*enemyGo));
            }
            
            // Posiciona o inimigo em relação à câmera atual
            enemyGo->box.x = Camera::pos.x + 600 + spawnOffset.x; 
            enemyGo->box.y = Camera::pos.y + 450 + spawnOffset.y;
            
            // Adiciona o novo inimigo ao estado atual do jogo
            Game::GetInstance().GetCurrentState().AddObject(enemyGo);

            zombieCounter++;
            zombieCooldownTimer.Restart();
        } 
        // Condição para trocar de onda: todos os zumbis da atual devem estar mortos
        else if (zombieCounter >= waves[currentWave].zombies && Zombie::zombieCount <= 0) {
            currentWave++;
            zombieCounter = 0;
            zombieCooldownTimer.Restart();
        }
    } else {
        // Fim de todas as ondas: seta a flag de vitória e solicita exclusão do spawner
        WaveSpawner::finished = true; 
        associated.RequestDelete();
    }
}

void WaveSpawner::Render() {
}