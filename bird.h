#pragma once

#include"lib.h"
#include"pipe.h"

class bird:LTexture{
public:
    void init();
    void render();
    void Free();
    void resetTime(){
        time=0;
    }
    void fall();
   void update(short pipeWidth, short pipeHeight);

private:
    short angle , time ,x0, ahead=0;
    string saved_path="";
    position birdPosition;
};

