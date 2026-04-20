#include "State.h"

State::State() : bg("assets/img/Background.png"), music("assets/audio/BGM.wav"), quitRequested(false){
    music.Play(-1);
}

void State::LoadAssets() {
    bg.Open("assets/img/Background.png");
    music.Open("assets/audio/BGM.wav");
}

void State::Update(float dt) {
    if (SDL_QuitRequested())
        quitRequested = true;
}

void State::Render() {
    bg.Render(0, 0);
}

bool State::QuitRequested() {
    return quitRequested;
}