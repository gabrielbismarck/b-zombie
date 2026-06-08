#include "Gun.h"
#include "SpriteRenderer.h"
#include "Character.h"
#include "Game.h"
#include "Animator.h"
#include "Bullet.h"
#include "InputManager.h"
#include "Camera.h"

Gun::Gun(GameObject& associated, std::weak_ptr<GameObject> character) : Component(associated) {

    this->character = character;

    shootSound.Open("assets/audio/Range.wav");
    reloadSound.Open("assets/audio/PumpAction.mp3");

    cooldownState = 0;
    angle = 0;

    associated.AddComponent(new SpriteRenderer(associated, "assets/img/Gun.png", 3, 2));

    Animator* anim = new Animator(associated);
    anim->AddAnimation("idle", Animation(0, 0, 0));
    anim->AddAnimation("reloading", Animation(3, 5, 0.1f));
    anim->AddAnimation("shoot", Animation(0, 2, 0.1f));
    associated.AddComponent(anim);


}

void Gun::Update(float dt) {
    
    auto characterPtr = character.lock();

    Animator* anim = associated.GetComponent<Animator>(); 

    
    if (!characterPtr){
        associated.RequestDelete();
        return;
    }

    cdTimer.Update(dt);

    

    InputManager& input = InputManager::GetInstance();
    Vec2 mousePos(input.GetMouseX() + Camera::pos.x, input.GetMouseY() + Camera::pos.y);
    Vec2 center = characterPtr->box.GetCenter();

    angle = std::atan2(mousePos.y - center.y, mousePos.x - center.x);

    // Criei esse pivot pra fazer a inversao do offset da gun somente no eixo x
    Vec2 pivot = characterPtr->box.GetCenter() + Vec2(0,15);
    Vec2 offset(25, 15);
    Vec2 gunPos = pivot + Vec2(25, 0).InclinationRad(angle);

    associated.box.x = gunPos.x - associated.box.w/2.0f ;
    associated.box.y = gunPos.y - associated.box.h/2.0f ;
    associated.angleDeg = angle * 180.0f / M_PI;

    if (SpriteRenderer* sr = associated.GetComponent<SpriteRenderer>()) {
        // Se o cosseno for negativo, o mouse ta na esquerda do player
        if (std::cos(angle) < 0) {
            sr->SetFlip(SDL_FLIP_VERTICAL);
        } else {
            sr->SetFlip(SDL_FLIP_NONE);
        }
    }

    if (cooldownState == 1 && cdTimer.Get() >= 0.2f) {
        cooldownState = 2;
        cdTimer.Restart();
        reloadSound.Play();
        if (auto anim = associated.GetComponent<Animator>())
            anim->SetAnimation("reloading");
        
    }
    
    else if (cooldownState == 2 && cdTimer.Get() >= 0.4f) {
        cooldownState = 3;
        cdTimer.Restart();
    }
    
    else if (cooldownState == 3 && cdTimer.Get() >= 0.1f) {
        cooldownState = 0;
        if (anim)
            anim->SetAnimation("idle");
    }

}

void Gun::Render() {}

void Gun::Shoot(Vec2 target) {
    
    if (cooldownState != 0)
    return;

    Vec2 center = associated.box.GetCenter();
    angle = std::atan2(target.y - center.y, target.x - center.x);

    GameObject* bulletGo = new GameObject();
    
    bulletGo->AddComponent(new Bullet(*bulletGo, angle, 300.0f, 20, 500.0f));
    
    Vec2 gunCenter = associated.box.GetCenter();
    bulletGo->box.x = gunCenter.x - bulletGo->box.w / 2.0f;
    bulletGo->box.y = gunCenter.y - bulletGo->box.h / 2.0f;
    
    Game::GetInstance().GetState().AddObject(bulletGo);

    shootSound.Play();
    cooldownState = 1;
    cdTimer.Restart();
}