#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Component.h"
#include "SpriteRenderer.h"
#include "Sound.h"
#include "Timer.h"

class Zombie : public Component {
    public:
        Zombie(GameObject& associated);

        ~Zombie();

        void Start() override;
        void Damage(int damage);

        void Update(float dt) override;
        void Render() override;

        void NotifyCollision(GameObject& other) override;
        static int zombieCount;

    private:
        int hitpoints;
        Timer hitTimer;
        bool hit;
        Sound deathSound;
        Sound hitSound;
        Timer deathTimer;
};


#endif