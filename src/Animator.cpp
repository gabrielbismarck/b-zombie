#include "Animator.h"
#include "SpriteRenderer.h"
#include "GameObject.h"

Animator::Animator(GameObject& associated) : Component(associated) {
    
    frameStart = 0;
    frameEnd = 0;
    frameTime = 0;
    currentFrame = 0;
    timeElapsed = 0;
} 

void Animator::Update(float dt) {
    
    if (frameTime == 0) return;

    timeElapsed += dt;

    if (timeElapsed >= frameTime) {
        currentFrame++;
        timeElapsed -= frameTime;
        
        if (currentFrame > frameEnd) 
            currentFrame = frameStart;
        

        SpriteRenderer* spr = associated.GetComponent<SpriteRenderer>();
        
        if (spr != nullptr) 
            spr->SetFrame(currentFrame);
        
    }
}

void Animator::Render() {}

void Animator::SetAnimation(std::string name) {
    
    
    
    auto it = animations.find(name);

    if (it != animations.end() && current != name) {
        current = name;
        frameStart = it->second.frameStart;
        frameEnd = it->second.frameEnd;
        frameTime = it->second.frameTime;
        currentFrame = frameStart;
        timeElapsed = 0;

        if (auto sprite = associated.GetComponent<SpriteRenderer>()) 
            sprite->SetFrame(currentFrame);
        
    }
}
void Animator::AddAnimation(std::string name, Animation anim) {
    
    if (animations.find(name) == animations.end()) {
        animations[name] = anim;
    }
}