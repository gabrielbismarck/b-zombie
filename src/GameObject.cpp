#include "GameObject.h"
#include "Component.h"


GameObject::GameObject() : isDead(false) {}

GameObject::~GameObject() {
    components.clear();
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
}

void GameObject::RemoveComponent(Component* cpt) {
    for (auto it = components.begin(); it != components.end(); it++) {
        if(it->get() == cpt) {
            components.erase(it);
            break;
        }
    }
}




/* public:
        GameObject();
        ~GameObject();

        void Update(float dt);
        void Render();

        void IsDead();
        void RequestDelete();

        void AddComponent(Component* cpt);
        void RemoveComponent(Component* cpt);

        template<typename T>
        T* GetComponent();
        Rect box;

        private:
            std::vector<std::unique_ptr<Component>> components;
            bool isDead; */