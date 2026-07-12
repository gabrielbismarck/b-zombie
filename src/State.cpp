#include "State.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Zombie.h"
#include "TileMap.h"
#include "TileSet.h"
#include "Camera.h"
#include "InputManager.h"
#include "Character.h"
#include "PlayerController.h"
#include <iostream>
#include "Collider.h"
#include "Collision.h"
#include "WaveSpawner.h"

State::State(){
    quitRequested = false;
    started = false;

    // Criação do background
    GameObject* bgGo = new GameObject();
    SpriteRenderer* bgSR = new SpriteRenderer(*bgGo, "assets/img/Background.png");
    bgSR->SetCameraFollower(true); // O background não deve seguir a câmera
    bgGo->AddComponent(bgSR);
    bgGo->box.x = 0;
    bgGo->box.y = 0;
    AddObject(bgGo);

    // Criação do mapa
    GameObject* mapGo = new GameObject();
    TileSet* tileSet = new TileSet(64, 64, "assets/img/Tileset.png");
    mapGo->AddComponent(new TileMap(*mapGo, "assets/map/map.txt", tileSet));

    // Configura a posição do mapa na origem
    mapGo->box.x = 0;
    mapGo->box.y = 0;
    AddObject(mapGo);

    // Configuração da música de fundo
    music.Open("assets/audio/BGM.wav");
    music.Play();

     // Criação do Player
    GameObject* characterGo = new GameObject();
    characterGo->AddComponent(new Character(*characterGo, "assets/img/Player.png", true));
    characterGo->AddComponent(new PlayerController(*characterGo));
    
    characterGo->box.x = 600;
    characterGo->box.y = 600;

    AddObject(characterGo);
    Camera::Follow(characterGo);

    GameObject* spawnerGo = new GameObject();
    spawnerGo->AddComponent(new WaveSpawner(*spawnerGo));
    AddObject(spawnerGo);

}

State::~State(){
    objectArray.clear();
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go) {
    std::shared_ptr<GameObject> ptr(go);
    objectArray.push_back(ptr);

    if (started)
        ptr->Start();

    return std::weak_ptr<GameObject>(ptr);
}

void State::Update(float dt) {

    Camera::Update(dt);
    
    InputManager& input = InputManager::GetInstance();

    if (input.QuitRequested() || input.KeyPress(ESCAPE_KEY))
        quitRequested = true;
 
    // Percorre todos os objetos e chama o update
    for (size_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }

    for (size_t i = 0; i < objectArray.size(); i++) {
        for (size_t j = i + 1; j < objectArray.size(); j++) {
            auto col_i = objectArray[i]->GetComponent<Collider>();
            auto col_j = objectArray[j]->GetComponent<Collider>();

            if (col_i != nullptr && col_j != nullptr) {
                if (Collision::IsColliding(col_i->box, col_j->box, objectArray[i]->angleDeg * (M_PI / 180.0), objectArray[j]->angleDeg * (M_PI / 180.0))) {
                    objectArray[i]->NotifyCollision(*objectArray[j]);
                    objectArray[j]->NotifyCollision(*objectArray[i]);
                }
            }
        }
    }

    for (size_t i = 0; i < objectArray.size(); i++){
        if (objectArray[i]->IsDead()){
            objectArray.erase(objectArray.begin() + i);
            i--;
        }
    }
}

void State::Render() {
    
    // Percorre todos os objetos e chama o render
    for (size_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Render();
    }
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::Start() {
    LoadAssets();

    for (size_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Start();
    }
    
    started = true;
    
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
    for (size_t i = 0; i < objectArray.size(); i++) {
        if (objectArray[i].get() == go) {
            return std::weak_ptr<GameObject>(objectArray[i]);
        }
    }
    return std::weak_ptr<GameObject>();
}

void State::LoadAssets() {
    
}