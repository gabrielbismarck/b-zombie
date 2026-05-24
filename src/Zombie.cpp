#include "Zombie.h"
#include "GameObject.h"
#include <InputManager.h>



Zombie::Zombie(GameObject& associated) : Component(associated){
    hitpoints = 100;

    deathSound.Open("assets/audio/Dead.wav");
    hitSound.Open("assets/audio/Hit0.wav");

    SpriteRenderer* spr = new SpriteRenderer(associated, "assets/img/Enemy.png", 3, 2);

    spr->SetFrame(1);
    associated.AddComponent(spr);
}

void Zombie::Damage(int damage){
    if (hitpoints > 0){
        hitpoints -= damage;
        hitSound.Play(1);
        if (hitpoints <= 0){
            deathSound.Play(1);
            SpriteRenderer* spr = (SpriteRenderer*) associated.GetComponent<SpriteRenderer>();
            if (spr != nullptr)
                spr->SetFrame(5);
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