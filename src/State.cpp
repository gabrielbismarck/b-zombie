#include "State.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Zombie.h"

State::State(){
    quitRequested = false;

    // Criação do background
    GameObject* bgGo = new GameObject();
    bgGo->AddComponent(new SpriteRenderer(*bgGo, "assets/img/Background.png"));
    bgGo->box.x = 0;
    bgGo->box.y = 0;
    AddObject(bgGo);
    
    //  Criação do Zumbi
    GameObject* zombieGo = new GameObject();
    zombieGo->AddComponent(new Zombie(*zombieGo));
    zombieGo->box.x = 600;
    zombieGo->box.y = 450;
    AddObject(zombieGo);


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
    if (SDL_QuitRequested())
        quitRequested = true;

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