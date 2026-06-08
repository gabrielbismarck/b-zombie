#ifndef GUN_H
#define GUN_H

#include "Component.h"
#include "Vec2.h"
#include "Sound.h"
#include "Timer.h"
#include <memory>

class Gun : public Component {
    public:
        Gun(GameObject& associated, std::weak_ptr<GameObject> character);

        // void Start() override;
        void Update(float dt) override;
        void Render() override;
        void Shoot(Vec2 target);

    private:
        Sound shootSound;
        Sound reloadSound;
        int cooldownState;
        Timer cdTimer;
        std::weak_ptr<GameObject> character;
        float angle;
};

#endif