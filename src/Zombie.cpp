#include "Zombie.h"
#include "Character.h"
#include "Collider.h"
#include "Animator.h"
#include "SpriteRenderer.h"
#include "Bullet.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Camera.h"


int Zombie::zombieCount = 0;

Zombie::~Zombie() {
    zombieCount--;
}

void Zombie::Start(){
    associated.AddComponent(new Collider(associated));
}


Zombie::Zombie(GameObject& associated) : Component(associated){
    hitpoints = 100;
    hit = false;

    associated.AddComponent(new SpriteRenderer(associated, "assets/img/Enemy.png", 3, 2));
    
    Animator* anim = new Animator(associated);

    deathSound.Open("assets/audio/Dead.wav");
    hitSound.Open("assets/audio/Hit0.wav");

    anim->AddAnimation("walking", Animation(0, 3, 0.1f));
    anim->AddAnimation("hit", Animation(4, 4, 0.1f));
    anim->AddAnimation("dead", Animation(5, 5, 0));
    hitTimer = Timer();

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

    if (hitpoints <= 0){
        if (auto collider = associated.GetComponent<Collider>()) {
            associated.RemoveComponent(collider);
        }
        
        if (auto anim = associated.GetComponent<Animator>()) {
            anim->SetAnimation("dead");
        }

        // Atualiza o timer e deleta o objeto após 1.5 segundos [16, p. 118]
        deathTimer.Update(dt); 
        if (deathTimer.Get() >= 1.5f) {
            associated.RequestDelete();
        }
        return;
    }

    InputManager& input = InputManager::GetInstance();


    if (Character::player != nullptr && !hit) {
        Vec2 target = Character::player->associated.box.GetCenter();
        Vec2 current = associated.box.GetCenter();
        
        // Calcula a direção normalizada e move o zumbi com velocidade constante
        Vec2 dir = (target - current).Normalize();
        associated.box.x += dir.x * 80.0f * dt;
        associated.box.y += dir.y * 80.0f * dt;

        // Rotaciona o zumbi para que ele aponte sempre para o personagem
        associated.angleDeg = dir.InclinationX() * 180.0f / M_PI;

        // Se olhar para a esquerda, o flip verticalmente
        if (SpriteRenderer* sr = (SpriteRenderer*)associated.GetComponent<SpriteRenderer>()) {
            if (dir.x < 0) {
                // Se olhar para a esquerda, o flip vertical compensa a rotação de 180°
                sr->SetFlip(SDL_FLIP_VERTICAL); 
            } else {
                sr->SetFlip(SDL_FLIP_NONE);
            }
        }
    }
    
    if(hit){
        hitTimer.Update(dt);
        if (hitTimer.Get() >= 0.1f){ // Tempo curto para o flash de dano
            hit = false;
            if (auto anim = associated.GetComponent<Animator>()) {
                anim->SetAnimation("walking");
            }
        }
    }

}



void Zombie::Render(){
    
}

void Zombie::NotifyCollision(GameObject& other) {
    if (auto bullet = (Bullet*)other.GetComponent<Bullet>()) {
        if (!bullet->targetsPlayer) { // Filtro de Friendly Fire [18, p. 156]
            hitpoints -= bullet->GetDamage();

            if (hitpoints <= 0) {
                // MODIFICAÇÃO: Remover colisor ao morrer para não travar balas [18, p. 163]
                associated.RemoveComponent(associated.GetComponent<Collider>());
                
                if (auto anim = associated.GetComponent<Animator>()) {
                    anim->SetAnimation("dead");
                }
                deathSound.Play(); 
            } else {
                // MODIFICAÇÃO: Ativar flag e timer para a animação de Hit funcionar
                hit = true;
                hitTimer.Restart();
                if (auto anim = associated.GetComponent<Animator>()) {
                    anim->SetAnimation("hit");
                }
                hitSound.Play();
            }
        }
    }
}