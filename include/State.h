#ifndef STATE_H
#define STATE_H

#include "Music.h"
#include "Sprite.h"
#include "GameObject.h"

class State {

    public:
        State();
        ~State();

        void AddObject(GameObject* go);

        bool QuitRequested ();
        void LoadAssets ();
        void Update (float dt);
        void Render ();

    private:
        // Sprite bg;
        Music music;
        bool quitRequested;
        std::vector<std::unique_ptr<GameObject>> objectArray;
};
#endif