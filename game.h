#pragma once

#include"bird.h"
#include"land.h"
#include"pipe.h"

using namespace std;

class game:LTexture{
public:
    struct input{
        enum type{QUIT,PLAY,NONE,PAUSE};
        type Type;
    };
    input userInput;
    bird bird;
    land land;
    pipe pipe;

    game();
    ~game();
    void initGraphic();

    bool isQuit(){
        return quit;
    }

    bool isDie(){
        return die;
    }

    void takeInput();

    void display();

    void releaseGraphic();

    void renderBackground();

    void renderMessage();

    void pauseButton();

    void resumeButton();

    void replayButton();

    void renderPause();

    void renderGameover();

     void renderPlayingScore();

    void renderMenuScore();

    void renderBestScore();

    void renderMedal();

    bool checkReplay();

    void start();

    short getPipeWidth(){
        return pipe.width();
    }

    short getPipeHeight(){
        return pipe.height();
    }

private:
    const double scale = 0.75;
    short bestScore;
};

