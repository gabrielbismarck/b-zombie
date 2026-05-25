#ifndef ANIMATION_H
#define ANIMATION_H

class Animation {
    public:
        
        Animation(int frameStart = 0, int frameEnd = 0, float frameTime = 0);

        int frameStart;
        int frameEnd;
        float frameTime;

};

#endif 