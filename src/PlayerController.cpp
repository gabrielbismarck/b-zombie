#include "PlayerController.h"
#include "InputManager.h"
#include "Vec2.h"
#include "Character.h"
#include "GameObject.h"
#include "Camera.h"

PlayerController::PlayerController(GameObject& associated) : Component(associated){}
void PlayerController::Update(float dt){

    InputManager& input = InputManager::GetInstance();
    Vec2 direction(0,0);

    Character* character = (Character*) associated.GetComponent<Character>();

    if(input.IsKeyDown(SDLK_w))
        direction.y -= 1;
    
    if(input.IsKeyDown(SDLK_s))
        direction.y += 1;
    
    if(input.IsKeyDown(SDLK_a))
        direction.x -= 1;
    
    if(input.IsKeyDown(SDLK_d))
        direction.x += 1;
    

    if (direction.x != 0 || direction.y != 0){
        character->Issue({Character::Command::MOVE, direction.x, direction.y});
    }

    if (input.MousePress(LEFT_MOUSE_BUTTON)){
        Vec2 mouseWorldPos(input.GetMouseX() + Camera::pos.x, input.GetMouseY() + Camera::pos.y);

        character->Issue({Character::Command::SHOOT, mouseWorldPos.x, mouseWorldPos.y});

    }
}

void PlayerController::Render(){}

void PlayerController::Start(){}

