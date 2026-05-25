#include "Zombie.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Camera.h"


Zombie::Zombie(GameObject& associated) : Component(associated){
    hitpoints = 100;

    associated.AddComponent(new SpriteRenderer(associated, "assets/img/Enemy.png", 3, 2));
    
    Animator* anim = new Animator(associated);

    deathSound.Open("assets/audio/Dead.wav");
    hitSound.Open("assets/audio/Hit0.wav");

    anim->AddAnimation("walking", Animation(0, 3, 0.1f));
    anim->AddAnimation("hit", Animation(4, 4, 0.1f));
    anim->AddAnimation("dead", Animation(5, 5, 0));
    hitTimer = Timer();
    hit = false;

    associated.AddComponent(anim);
    anim->SetAnimation("walking");

}


void Zombie::Damage(int damage){

    if (hitpoints <= 0)
        return;

    hitpoints -= damage;
    hit = true;
    hitSound.Play(1);

    Animator* anim = associated.GetComponent<Animator>();
    if (anim != nullptr)
        if (hitpoints <= 0)        {
            anim->SetAnimation("dead");
            deathSound.Play(1);
        }
        else{
            hit = true;
            hitTimer.Restart();
            anim->SetAnimation("hit");
        }
            
        


        
}

void Zombie::Update(float dt){

   InputManager& input = InputManager::GetInstance();

    if (input.MousePress(LEFT_MOUSE_BUTTON)){
        Vec2 mousePos(input.GetMouseX() + Camera::pos.x, input.GetMouseY() + Camera::pos.y);

        if (associated.box.Contains(mousePos))
            Damage(10);    
    }

    hitTimer.Update(dt);
    if(hit && hitTimer.Get() >= 0.1f){
        hit = false;
        Animator* anim = associated.GetComponent<Animator>();
        if (anim != nullptr && hitpoints > 0)
            anim->SetAnimation("walking");
    }
    
}

void Zombie::Render(){
    
}