#include "Zombie.h"
#include "GameObject.h"



Zombie::Zombie(GameObject& associated) : Component(associated){
    hitpoints = 100;

    SpriteRenderer* spr = new SpriteRenderer(associated, "assets/img/Enemy.png", 3, 2);

    spr->SetFrame(1);
    associated.AddComponent(spr);
}

void Zombie::Damage(int damage){
    hitpoints -= damage;

    if (hitpoints <= 0){
        SpriteRenderer* spr = (SpriteRenderer*) associated.GetComponent<SpriteRenderer>();
        if (spr != nullptr)
            spr->SetFrame(5);
    }
}

void Zombie::Update(float dt){
   Damage(1);
}

void Zombie::Render(){
    
}