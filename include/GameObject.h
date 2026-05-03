#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <memory>
#include <string>
#include "Rect.h"
#include "Component.h"


class GameObject {
    public:
        GameObject();
        ~GameObject();

        void Update(float dt);
        void Render();

        bool IsDead();
        void RequestDelete();

        void AddComponent(Component* cpt);
        void RemoveComponent(Component* cpt);

        template<typename T>
        T* GetComponent() {
            for (auto& cpt : components) {
                T* ptr = dynamic_cast<T*>(cpt.get());
                if (ptr != nullptr)
                    return ptr;
            }
            return nullptr;
        }
        Rect box;

        private:
            std::vector<std::unique_ptr<Component>> components;
            bool isDead;


};
#endif