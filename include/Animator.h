#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <unordered_map>
#include <string>
#include "Component.h"
#include "Animation.h"

class Animator : public Component {
    public:

        Animator(GameObject& associated);
        
        void Update(float dt);
        void Render(); 
        void SetAnimation(std::string name);
        void AddAnimation(std::string name, Animation anim);
        std::string current;

    private:

        std::unordered_map<std::string, Animation> animations;

        int frameStart, frameEnd, currentFrame;
        float frameTime, timeElapsed;
};

#endif