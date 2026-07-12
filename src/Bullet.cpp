#include "Bullet.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "Collider.h"
#include "Character.h"
#include "Zombie.h"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, bool targetsPlayer) : Component(associated){
    this->targetsPlayer = targetsPlayer;

     SpriteRenderer* sr = new SpriteRenderer(associated, "assets/img/Bullet.png");
     
     sr->SetScale(1, 1);
     
     associated.AddComponent(sr);

     associated.angleDeg = angle * 180.0f / M_PI + 90.0f;

    this->speed = Vec2(speed * cos(angle), speed * sin(angle));
    this->damage = damage;
    this->distanceLeft = maxDistance;
    associated.AddComponent(new Collider(associated));
}

void Bullet::Update(float dt){
 
    associated.box.x += speed.x * dt;
    associated.box.y += speed.y * dt;
    
    // Distancia que falta menos a distancia que o projétil percorreu nesse frame
    distanceLeft -= speed.Mag() * dt;
    
    if (distanceLeft <= 0)
        associated.RequestDelete();
}

void Bullet::Render(){}

int Bullet::GetDamage(){
    return damage;
}

void Bullet::NotifyCollision(GameObject& other) {

    if (targetsPlayer) {
        // Bala de NPC só some se atingir o Player real
        // Verifica se o GameObject colidido é o mesmo que está no ponteiro estático do Player
        if (Character::player != nullptr && &other == &Character::player->associated) {
            associated.RequestDelete();
        }
    } else {
        // Bala de Player só deve some se atingir um inimigo
        // Ignora a colisão se o objeto atingido for o próprio jogador
        if (Character::player != nullptr && &other != &Character::player->associated) {
            
            // Verifica se o alvo é um Zombie ou um NPC
            if (other.GetComponent<Zombie>() != nullptr || other.GetComponent<Character>() != nullptr) {
                associated.RequestDelete();
            }
        }
    }
}