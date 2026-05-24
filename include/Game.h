#ifndef GAME_H
#define GAME_H

#define INCLUDE_SDL
#include <string>
#include <SDL_include.h>
#include "State.h"

class Game {
    public:
        static Game& GetInstance();
        ~Game ();
        
        State& GetState ();
        SDL_Renderer* GetRenderer ();
        
        float GetDeltaTime ();

        void Run ();

    private:
        Game (std::string title, int width, int height);

        static Game* instance;
        SDL_Window* window;
        SDL_Renderer* renderer;
        State* state;

        int frameStart;
        float dt;
        void CalculateDeltaTime();

};

#endif