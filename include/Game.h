#include <stack>
#include <memory>
#include "State.h"
#include "SDL_ttf.h"

class Game {
    public:
        static Game& GetInstance();
        ~Game ();
        
        // Retorna o estado que está no topo da pilha
        State& GetCurrentState (); 
        SDL_Renderer* GetRenderer ();
        
        float GetDeltaTime ();
        void Run ();

        // Agenda o empilhamento de um novo estado
        void Push(State* state); 

    private:
        Game (std::string title, int width, int height);

        static Game* instance;
        SDL_Window* window;
        SDL_Renderer* renderer;
        
        // Gerenciamento de pilha
        State* storedState; 
        std::stack<std::unique_ptr<State>> stateStack;

        int frameStart;
        float dt;
        void CalculateDeltaTime();
};