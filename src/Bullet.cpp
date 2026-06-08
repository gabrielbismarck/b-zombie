#include "Bullet.h"
#include "GameObject.h"
#include "SpriteRenderer.h"


Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance) : Component(associated){

     SpriteRenderer* sr = new SpriteRenderer(associated, "assets/img/Bullet.png");
     
     sr->SetScale(1, 1);
     
     associated.AddComponent(sr);

     associated.angleDeg = angle * 180.0f / M_PI + 90.0f;

    this->speed = Vec2(speed * cos(angle), speed * sin(angle));
    this->damage = damage;
    this->distanceLeft = maxDistance;
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

