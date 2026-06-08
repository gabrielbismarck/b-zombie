#ifndef CHARACTER_H
#define CHARACTER_H

#include "Component.h"
#include "Vec2.h"
#include "Timer.h"
#include <string>
#include <queue>
#include <memory>

class Character : public Component {
    public:

        class Command {
            public:
                enum CommandType {MOVE, SHOOT};
                CommandType type;
                Vec2 pos;
                Command(CommandType type, float x, float y) : type(type), pos(x, y){};
        };

        Character(GameObject& associated, std::string sprite);
        ~Character();

        void Start() override;
        void Update(float dt) override;
        void Render() override;

        void Issue (Command task);

        static Character* player;

        
    private:
        std::weak_ptr<GameObject> gun;
        std::queue<Command> taskQueue;
        Vec2 speed;
        float linearSpeed;
        int hp;
        Timer deathTimer;

    };


#endif