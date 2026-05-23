#include "InputManager.h"


// Meyer's Signleton
InputManager& InputManager::GetInstance() {
    static InputManager instance;
    return instance;
}

InputManager::InputManager() {
    
    // Inicializa o estado dos botões do mouse
    for (int i = 0; i < 6; i++) {
        mouseState[i] = false;
        mouseUpdate[i] = 0;
    }

    // Inicializa as variáveis. A tabela de hash n precisa
    quitRequested = false;
    updateCounter = 0;

    mouseX = 0;
    mouseY = 0;
    
}

InputManager::~InputManager() {}

void InputManager::Update() {
    SDL_Event event;

/*
Fazemos uso da função SDL_PollEvent, uma função que recebe um
ponteiro para uma variável do tipo SDL_Event. Se houver um evento ainda a
ser processado, ela retorna true e o grava na variável de evento. Se não,
retorna false
*/

/** 
  while (game_is_still_running) {
     SDL_Event event;
     while (SDL_PollEvent(&event)) {  // poll until all events are handled!
         // decide what to do with this event.
     }

     // update game state, draw the current frame
 }

*/
    // VAriável do tipo SDL_Event
    SDL_Event event;

    
    while (SDL_PollEvent(&event)){


    }
    
    
}

