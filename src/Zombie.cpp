#include "Zombie.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "InputManager.h"
#include "GameObject.h"


Zombie::Zombie(GameObject& associated) : Component(associated){
    hitpoints = 100;

    associated.AddComponent(new SpriteRenderer(associated, "assets/img/Enemy.png", 3, 2));
    
    Animator* anim = new Animator(associated);

    deathSound.Open("assets/audio/Dead.wav");
    hitSound.Open("assets/audio/Hit0.wav");

    anim->AddAnimation("walking", Animation(0, 3, 0.1f));
    anim->AddAnimation("dead", Animation(5, 5, 0));

    associated.AddComponent(anim);
    anim->SetAnimation("walking");

    
}

void Zombie::Damage(int damage){
    if (hitpoints > 0){
        hitpoints -= damage;
        hitSound.Play(1);
        if (hitpoints <= 0){
            
            deathSound.Play(1);
            Animator* anim = associated.GetComponent<Animator>();
            if (anim != nullptr)
                anim->SetAnimation("dead");
        }
    }
        
}

void Zombie::Update(float dt){

   InputManager& input = InputManager::GetInstance();

    if (input.MousePress(LEFT_MOUSE_BUTTON)){

        int mouseX = input.GetMouseX();
        int mouseY = input.GetMouseY();

        int posIniZombieX = associated.box.x;
        int posIniZombieY = associated.box.y;
        int widthZombie = associated.box.w;
        int heightZombie = associated.box.h;

        // Checa se o mouse clicou em cima do zombie atraves de Colisao ponto-retangulo
        if(mouseX >= posIniZombieX && mouseX <= (posIniZombieX + widthZombie) &&
           mouseY >= posIniZombieY && mouseY <= (posIniZombieY + heightZombie) ){
            Damage(50);
        }
    }
}

void Zombie::Render(){
    
}