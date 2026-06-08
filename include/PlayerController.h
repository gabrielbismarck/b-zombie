#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "Component.h"
#include "GameObject.h"

class PlayerController : public Component{
    public:
        PlayerController(GameObject& associated);
        
        void Start() override;
        void Update(float dt) override;
        void Render() override;
};

#endif