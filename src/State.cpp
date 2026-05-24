#include "State.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Zombie.h"
#include "TileMap.h"
#include "TileSet.h"
#include "InputManager.h"

State::State(){
    quitRequested = false;

    // Criação do background
    GameObject* bgGo = new GameObject();
    bgGo->AddComponent(new SpriteRenderer(*bgGo, "assets/img/Background.png"));
    bgGo->box.x = 0;
    bgGo->box.y = 0;
    AddObject(bgGo);

    // Criação do mapa
    GameObject* mapGo = new GameObject();
    TileSet* tileSet = new TileSet(64, 64, "assets/img/TileSet.png");
    mapGo->AddComponent(new TileMap(*mapGo, "assets/map/map.txt", tileSet));

    // Configura a posição do mapa na origem
    mapGo->box.x = 0;
    mapGo->box.y = 0;
    AddObject(mapGo);

    // Configuração da música de fundo
    music.Open("assets/audio/BGM.wav");
    music.Play();

}

State::~State(){
    objectArray.clear();
}

void State::AddObject(GameObject* go) {
    objectArray.emplace_back(go);
}

void State::Update(float dt) {
    
    InputManager& input = InputManager::GetInstance();

    if (input.QuitRequested() || input.KeyPress(ESCAPE_KEY))
        quitRequested = true;

    if (input.KeyPress(SDLK_SPACE)){
        GameObject* zombieGo1 = new GameObject();
        zombieGo1->AddComponent(new Zombie(*zombieGo1));
        zombieGo1->box.x = input.GetMouseX();
        zombieGo1->box.y = input.GetMouseY();
        AddObject(zombieGo1);
    }
 
    // Percorre todos os objetos e chama o update
    for (size_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
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