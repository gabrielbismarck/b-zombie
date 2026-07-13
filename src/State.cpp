#include "State.h"

State::State(){
    popRequested = false;
    quitRequested = false;
    started = false;
}

State::~State(){
    objectArray.clear(); // shared_ptrs garantem a liberação da memória dos GameObjects 
}

// Método genérico para adicionar objetos ao estado atual 
std::weak_ptr<GameObject> State::AddObject(GameObject* go) {
    std::shared_ptr<GameObject> ptr(go);
    objectArray.push_back(ptr);

    if (started)
        ptr->Start();

    return std::weak_ptr<GameObject>(ptr);
}

// Retorna um weak_ptr para um objeto que já está no vetor 
std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
    for (size_t i = 0; i < objectArray.size(); i++) {
        if (objectArray[i].get() == go) {
            return std::weak_ptr<GameObject>(objectArray[i]);
        }
    }
    return std::weak_ptr<GameObject>();
}

// Flags de controle para a pilha de estados do Game
bool State::PopRequested() { return popRequested; }
bool State::QuitRequested() { return quitRequested; }

// Auxiliar para inicializar todos os objetos do vetor
void State::StartArray() {
    for (size_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Start();
    }
    started = true;
}

// Auxiliar que atualiza todos os objetos e remove os mortos (isDead)
void State::UpdateArray(float dt) {
    for (size_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }

    for (auto it = objectArray.begin(); it != objectArray.end(); ) {
        if ((*it)->IsDead()) {
            it = objectArray.erase(it);
        } else {
            it++;
        }
    }
}

// Auxiliar para renderizar todos os objetos na ordem do vetor
void State::RenderArray() {
    for (size_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Render();
    }
}