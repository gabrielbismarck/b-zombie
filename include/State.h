#ifndef STATE_H
#define STATE_H

#include "Music.h"
#include "Sprite.h"
#include "GameObject.h"

class State {

    public:
        State();
        ~State();

        void Start();
        
        std::weak_ptr<GameObject> AddObject(GameObject* go);
        std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);

        bool QuitRequested ();
        void LoadAssets ();
        void Update (float dt);
        void Render ();

    private:
        Music music;
        bool quitRequested;
        std::vector<std::shared_ptr<GameObject>> objectArray;
        bool started;
};
#endif