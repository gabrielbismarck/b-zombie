#include "Camera.h"
#include "InputManager.h"


Vec2 Camera::pos = Vec2(0, 0);
Vec2 Camera::speed = Vec2(0, 0);
GameObject* Camera::focus = nullptr;

void Camera::Follow(GameObject* newFocus){
    focus = newFocus;
}

void Camera::Unfollow(){
    focus = nullptr;
}

void Camera::Update(float dt){
    if(focus != nullptr){
     // A janeça é de 1200x900, então o centro é 600x450
        pos.x = focus->box.x + focus->box.GetCenter().x - 600;
        pos.y = focus->box.y + focus->box.GetCenter().y - 450;

    }
    else{
        
        InputManager& input = InputManager::GetInstance();
        if(input.IsKeyDown(SDLK_LEFT))
            pos.x -= 200 * dt;
        if(input.IsKeyDown(SDLK_RIGHT))
            pos.x += 200 * dt;
        if(input.IsKeyDown(SDLK_UP))
            pos.y -= 200 * dt;
        if(input.IsKeyDown(SDLK_DOWN))
            pos.y += 200 * dt;
    }
}