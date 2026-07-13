#include "AIController.h"
#include "Character.h"
#include "Gun.h"
#include "GameObject.h"
#include <cmath>

int AIController::npcCount = 0;

AIController::AIController(GameObject& associated) : Component(associated) {
    state = RESTING; // Estado inicial
    restTimer = Timer();
    npcCount++;
}

void AIController::Update(float dt) {
    // Se o jogador morrer, o NPC para de executar qualquer lógica
    auto character = (Character*)associated.GetComponent<Character>();

     if (Character::player == nullptr || character == nullptr || character->hp <= 0) {
        return; 
    }

    Vec2 playerCenter = Character::player->associated.box.GetCenter();
    Vec2 npcCenter = associated.box.GetCenter();

    // MÁQUINA DE ESTADOS
    if (state == RESTING) {
        restTimer.Update(dt);
        
        // Timer terminou: Obtém posição do jogador e muda para MOVING
        if (restTimer.Get() >= 2.0f) { // Cooldown de 2s entre ataques
            state = MOVING;
            destination = playerCenter;
        }
    } 
    else if (state == MOVING) {
        // Calcula a direção para o destino salvo
        Vec2 dir = (destination - npcCenter);
        float distance = dir.Mag();

        // Se ainda não chegou ao destino se move
        if (distance > 10.0f) {
            Vec2 moveDir = dir.Normalize();
            float speed = 80.0f; // Velocidade do NPC

            character->Issue(Character::Command(Character::Command::MOVE, moveDir.x, moveDir.y));
            
        } 
        // Se chegou ao destino atira contra o jogador e volta a descansar
        else {
            // O NPC atira enviando um comando para o Character
            if (auto character = (Character*)associated.GetComponent<Character>()) {
                character->Issue(Character::Command(Character::Command::SHOOT, playerCenter.x, playerCenter.y));
            }

            state = RESTING;
            restTimer.Restart();
        }
    }
}

void AIController::Render() {}

AIController::~AIController() {
    npcCount--;
}