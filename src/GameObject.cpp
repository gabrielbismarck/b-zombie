#include "GameObject.h"
#include "Component.h"


GameObject::GameObject() {
    isDead = false;
    started = false;
    angleDeg = 0;
}

GameObject::~GameObject() {
    components.clear();
}

void GameObject::Start() {
    for (size_t i = 0; i < components.size(); i++) {
        components[i]->Start();
    }
    started = true;
}

void GameObject::Update(float dt) {
    for (size_t i = 0; i < components.size(); i++) {
        // uso -> ao ivés de . pq é um vetor de ponteiros
        components[i]->Update(dt);
    }
}

void GameObject::Render() {
    for (size_t i = 0; i < components.size(); i++) {
        // uso -> pq é um vetor de ponteiros
        components[i]->Render();
    }
}

bool GameObject::IsDead() {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(Component* cpt) {
    components.emplace_back(cpt);

    if (started)
        cpt->Start();
}

void GameObject::RemoveComponent(Component* cpt) {
    for (auto it = components.begin(); it != components.end(); it++) {
        if(it->get() == cpt) {
            components.erase(it);
            break;
        }
    }
}

void GameObject::NotifyCollision(GameObject& other) {
    // Itera por todos os componentes do objeto e chama o NotifyCollision de cada um
    for (size_t i = 0; i < components.size(); i++) {
        components[i]->NotifyCollision(other);
    }
}