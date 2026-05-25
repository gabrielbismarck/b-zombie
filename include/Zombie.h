#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Component.h"
#include "SpriteRenderer.h"
#include "Sound.h"
#include "Timer.h"

class Zombie : public Component {
    public:
        Zombie(GameObject& associated);

        void Damage(int damage);

        void Update(float dt) override;
        void Render() override;

        

    private:
        int hitpoints;
        Timer hitTimer;
        bool hit;
        Sound deathSound;
        Sound hitSound;
};


#endif