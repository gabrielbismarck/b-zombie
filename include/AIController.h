#ifndef AI_CONTROLLER_H
#define AI_CONTROLLER_H

#include "Component.h"
#include "Timer.h"
#include "Vec2.h"

class AIController : public Component {
public:
    AIController(GameObject& associated);
    void Update(float dt) override;
    void Render() override;

private:
    enum AIState { MOVING, RESTING };
    AIState state;
    Timer restTimer;
    Vec2 destination;
};

#endif