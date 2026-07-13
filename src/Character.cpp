#include "Character.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Game.h"
#include "Gun.h"
#include "Collider.h"
#include "Bullet.h" 
#include "Camera.h" 
#include "Zombie.h" 
#include "Sound.h"  

Character* Character::player = nullptr;

Character::Character(GameObject& associated, std::string sprite, bool isPlayer) : Component(associated){

    hp = 100;
    linearSpeed = 100.0f;
    this->isPlayer = isPlayer;

     if (isPlayer) {
        player = this;
    }

    associated.AddComponent(new SpriteRenderer(associated, sprite, 3, 4));
    Animator* anim = new Animator(associated);

    anim->AddAnimation("idle", Animation(0, 0, 0));
    anim->AddAnimation("walking", Animation(0, 2, 0.1f));
    anim->AddAnimation("dead", Animation(9, 11, 0.2f));
    associated.AddComponent(anim);
    damageTimer.Restart();
    deathTimer.Restart();

}


Character::~Character() {
    if (isPlayer) { // Só limpa o ponteiro se for o player real
        player = nullptr;
    }
}

void Character::Start() {
    
    associated.AddComponent(new Collider(associated));
    
    GameObject* gunGo = new GameObject();
    
    // Obtém o ponteiro para o GameObject associado ao Character para passar para a Gun
    std::weak_ptr<GameObject> characterPtr = Game::GetInstance().GetCurrentState().GetObjectPtr(&associated);

    gunGo->AddComponent(new Gun(*gunGo, characterPtr));
    
    // Adiciona a arma ao estado para que ela seja gerenciada corretamente e guarda o ponteiro fraco para ela na variável gun
    gun = Game::GetInstance().GetCurrentState().AddObject(gunGo);
}

void Character::Update(float dt) {

    damageTimer.Update(dt);

    if (hp <= 0) {
        // Limpa a fila para garantir que nenhum comando seja executado
        while (!taskQueue.empty()) taskQueue.pop();
        
        speed = Vec2(0, 0);

        if (auto gunPtr = gun.lock()) {
            gunPtr->RequestDelete();
        }
        if (auto collider = associated.GetComponent<Collider>()) {
            associated.RemoveComponent(collider);
        }

        Animator* anim = associated.GetComponent<Animator>();
        if (anim != nullptr) {
            anim->SetAnimation("dead");
        }

        deathTimer.Update(dt);
        if (deathTimer.Get() >= 1.5f) {
            associated.RequestDelete();
        }
        
        return; 
    }


    while (!taskQueue.empty()) {
        Command task = taskQueue.front();
        taskQueue.pop();

        if (task.type == Command::MOVE) {
            
            speed = task.pos.Normalize() * linearSpeed;
            
        } else if (task.type == Command::SHOOT) {
            if (auto gunPtr = gun.lock()) {
                if (auto gunComponent = gunPtr->GetComponent<Gun>()) {
                    Vec2 target = task.pos;
                    gunComponent->Shoot(target);
                }
            }
        }
    }
   
    associated.box.x += speed.x * dt;
    associated.box.y += speed.y * dt;

    if (associated.box.x < 640)
        associated.box.x = 640;
    if (associated.box.x + associated.box.w > 1920)
        associated.box.x = 1920 - associated.box.w; // 640 + 1280
    if (associated.box.y < 512)
        associated.box.y = 512;
    if (associated.box.y + associated.box.h > 2048)
        associated.box.y = 2048 - associated.box.h; // 512 + 1536

     Animator* anim = associated.GetComponent<Animator>();
    SpriteRenderer* sr = associated.GetComponent<SpriteRenderer>();

    if (anim != nullptr) {
        if (speed.Mag() > 0) {
            anim->SetAnimation("walking");
            if (sr != nullptr) {
                if (speed.x < 0) sr->SetFlip(SDL_FLIP_HORIZONTAL);
                else if (speed.x > 0) sr->SetFlip(SDL_FLIP_NONE);
            }
        } else {
            anim->SetAnimation("idle");
        }
    }
    
    speed = Vec2(0, 0);
}

void Character::Render() {}

void Character::Issue(Command task) {
    taskQueue.push(task);
}

void Character::NotifyCollision(GameObject& other) {
    // Checa colisão com Bullets
    if (auto bullet = (Bullet*)other.GetComponent<Bullet>()) {
        // Friendly Fire: Só toma dano se a bala for destinada a este tipo de alvo
        if ((bullet->targetsPlayer && this == player) || (!bullet->targetsPlayer && this != player)) {
            
            // Use o método GetDamage() pois o atributo 'damage' é privado
            hp -= bullet->GetDamage();
            
            if (hp <= 0) {
                if(isPlayer) {
                    Camera::Unfollow();
                }
                
                // Removido 'associated'. O construtor de Sound recebe apenas o caminho do arquivo
                Sound("assets/audio/Dead.wav").Play(); 
            } else {
                
                // Removido 'associated'
                Sound("assets/audio/Hit1.wav").Play(); 
            }
        }
    }

    // Checa colisão com Zombies (Dano por contato com cooldown de 0.5s)
    if (other.GetComponent<Zombie>() != nullptr && this == player) {
        if (damageTimer.Get() >= 0.5f) {
            hp -= 10; // Dano fixo por contato com zumbi
            damageTimer.Restart();
            
            // Removido 'associated'
            Sound("assets/audio/Hit1.wav").Play();
            
            if (hp <= 0) Camera::Unfollow();
        }
    }
}

