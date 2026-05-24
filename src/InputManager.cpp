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
    // VAriável do tipo SDL_Event
    // SDL_Event é uma union. É tipo uma struct, mas só armazena um dos seus atributos por vez. No SDL_events.h tem os tipos
    SDL_Event event;

    SDL_GetMouseState(&mouseX, &mouseY);
    quitRequested = false;
    updateCounter++;
    
    while (SDL_PollEvent(&event)){

        switch (event.type)
        {
            
        case SDL_KEYDOWN:
            if (event.key.repeat != 0)
                break;

            keyState[event.key.keysym.sym] = true;
            keyUpdate[event.key.keysym.sym] = updateCounter;
            break;
        
        case SDL_KEYUP:
            keyState[event.key.keysym.sym] = false;
            keyUpdate[event.key.keysym.sym] = updateCounter;
            break;
        
        case SDL_MOUSEBUTTONDOWN:
            mouseState[event.button.button] = true;
            mouseUpdate[event.button.button] = updateCounter;
            break;

        case SDL_MOUSEBUTTONUP:
            mouseState[event.button.button] = false;
            mouseUpdate[event.button.button] = updateCounter;
            break;

        case SDL_QUIT:
            quitRequested = true;
            break;
        }


    }
    
    
}

bool InputManager::KeyPress (int key) {
    // Se a tecla estiver pressiona && tiver sido atualizada nesse frame, retorna true
    return keyState[key] && (keyUpdate[key] == updateCounter);
}

bool InputManager::KeyRelease (int key) {
    // Se a tecla for solta && tiver sido atualizada nesse frame, retorna true
    return !keyState[key] && (keyUpdate[key] == updateCounter);
}

bool InputManager::IsKeyDown (int key) {
    // retorna ao estado da tecla, se ele tiver sido pressionado independente do frame
    return keyState[key];
}

bool InputManager::MousePress (int button) {
    // Se o botão do mouse estiver pressionado && tiver sido atualizado nesse frame, retorna true
    return mouseState[button] && (mouseUpdate[button] == updateCounter);
}

bool InputManager::MouseRelease (int button) {
    // Se o botão do mouse for solto && tiver sido atualizado nesse frame, retorna true
    return !mouseState[button] && (mouseUpdate[button] == updateCounter);
}

bool InputManager::IsMouseDown (int button) {
    // Retorna ao estado do botão, se ele tiver sido pressionado independente do frame
    return mouseState[button];
}

int InputManager::GetMouseX() {
    return mouseX;
}

int InputManager::GetMouseY() {
    return mouseY;
}

bool InputManager::QuitRequested() {
    return quitRequested;
}