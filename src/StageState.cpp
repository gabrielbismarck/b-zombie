#include "StageState.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "TileMap.h"
#include "Character.h"
#include "PlayerController.h"
#include "AIController.h"
#include "WaveSpawner.h"
#include "Camera.h"
#include "InputManager.h"
#include "Collision.h"
#include "Collider.h"
#include "Game.h"
#include "TitleState.h"
#include "EndState.h"
#include "GameData.h"
#include "Zombie.h"
StageState::StageState() : State() {
    // Criação do background que ignora o movimento da câmera
    GameObject* bgGo = new GameObject();
    SpriteRenderer* bgSR = new SpriteRenderer(*bgGo, "assets/img/Background.png");
    bgSR->SetCameraFollower(true); 
    bgGo->AddComponent(bgSR);
    AddObject(bgGo);

    // Configuração do TileMap e TileSet
    GameObject* mapGo = new GameObject();
    tileSet = new TileSet(64, 64, "assets/img/Tileset.png");
    mapGo->AddComponent(new TileMap(*mapGo, "assets/map/map.txt", tileSet));
    AddObject(mapGo);

    // Criação do Player e configuração da câmera
    GameObject* characterGo = new GameObject();
    characterGo->AddComponent(new Character(*characterGo, "assets/img/Player.png", true));
    characterGo->AddComponent(new PlayerController(*characterGo));
    characterGo->box.x = 1200; // Posição inicial central
    characterGo->box.y = 1200;
    AddObject(characterGo);
    Camera::Follow(characterGo);

    // Spawner de hordas de inimigos
    GameObject* spawnerGo = new GameObject();
    spawnerGo->AddComponent(new WaveSpawner(*spawnerGo));
    AddObject(spawnerGo);
}

StageState::~StageState() {
}

void StageState::Start() {
    LoadAssets();
    backgroundMusic.Open("assets/audio/BGM.wav");
    backgroundMusic.Play(); // Inicia a música tema da fase
    StartArray(); // Inicializa todos os GameObjects inseridos
}

void StageState::Update(float dt) {
    InputManager& input = InputManager::GetInstance();

    // ESC agora volta para o menu em vez de fechar o jogo
    if (input.KeyPress(ESCAPE_KEY)) {
        popRequested = true;
    }

    if (input.QuitRequested()) {
        quitRequested = true;
    }

    Camera::Update(dt); // Atualiza a posição da câmera
    UpdateArray(dt); // Atualiza todos os objetos e remove mortos

    // Lógica de Detecção de Colisões
    for (size_t i = 0; i < objectArray.size(); i++) {
        for (size_t j = i + 1; j < objectArray.size(); j++) {
            auto col_i = objectArray[i]->GetComponent<Collider>();
            auto col_j = objectArray[j]->GetComponent<Collider>();

            if (col_i && col_j) {
                if (Collision::IsColliding(col_i->box, col_j->box, objectArray[i]->angleDeg * (M_PI / 180.0), objectArray[j]->angleDeg * (M_PI / 180.0))) {
                    objectArray[i]->NotifyCollision(*objectArray[j]);
                    objectArray[j]->NotifyCollision(*objectArray[i]);
                }
            }
        }
    }

     // VITÓRIA: Spawner terminou E não há zumbis E não há NPCs vivos
    if (Character::player != nullptr && 
        WaveSpawner::finished && 
        Zombie::zombieCount <= 0 && 
        AIController::npcCount <= 0) { 
        
        GameData::playerVictory = true;
        Game::GetInstance().Push(new EndState());
        popRequested = true;
    } 
    // DERROTA: O player morreu
    else if (Character::player == nullptr) {
        GameData::playerVictory = false;
        Game::GetInstance().Push(new EndState());
        popRequested = true;
    }
}

void StageState::Render() {
    // Renderiza o mapa (TileMap) primeiro
    if (auto mapGo = GetObjectPtr(objectArray[1].get()).lock()) {
        if (auto map = mapGo->GetComponent<TileMap>()) {
            map->Render();
        }
    }
    RenderArray(); // Renderiza os demais objetos (Player, Inimigos, UI)
}

void StageState::LoadAssets() {}
void StageState::Pause() { backgroundMusic.Stop(500); } // Pausa a música ao empilhar outro estado
void StageState::Resume() { backgroundMusic.Play(); } // Retoma a música ao voltar para o topo