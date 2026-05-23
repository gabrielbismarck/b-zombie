#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <unordered_map>
#define INCLUDE_SDL
#include "SDL_include.h"

class InputManager {
public:

    void Update();

    bool KeyPress (int key); 
    bool KeyRelease (int key);
    bool IsKeyDown (int key);

    bool MousePress (int button);
    bool MouseRelease (int button);
    bool IsMouseDown (int button);

    int GetMouseX();
    int GetMouseY();

    bool QuitRequested();

    static InputManager& GetInstance();

private:

    InputManager();
    ~InputManager();

    bool mouseState[6]; 
    int mouseUpdate[6];

    std::unordered_map<int, bool> keyState;
    std::unordered_map<int, int> keyUpdate;

    bool quitRequested;

    int updateCounter;

    int mouseX;
    int mouseY;
};

#endif