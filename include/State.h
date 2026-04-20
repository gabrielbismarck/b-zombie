#ifndef STATE_H
#define STATE_H

#include "Music.h"
#include "Sprite.h"

class State {

    public:
        State();

        bool QuitRequested ();
        void LoadAssets ();
        void Update (float dt);
        void Render ();

    private:
        Sprite bg;
        Music music;
        bool quitRequested;
};
#endif