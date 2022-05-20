#include<iostream>
#include<SDl.H>
#include<SDL_image.h>
#include"game.h"
#include"lib.h"
#include"bird.h"
using namespace std;



const short FPS = 73;
const short frameDelay = 1000 / FPS;

int main(int agrc, char* agrv[]){
    Uint32 frameStart;
    short int frameTime;
    game g;
    bool isMenu=0;
    bool isPause=0;

    while(!g.isQuit()){
        frameStart=SDL_GetTicks();
        if(g.isDie()){
            while(g.isDie() && !g.isQuit()){
                g.takeInput();
                if(isMenu==1 && g.userInput.Type==game::input::PLAY){
                    if(g.checkReplay() )isMenu=0;
                    g.userInput.Type=game::input::NONE;
                }
                g.renderBackground();
                g.pipe.render();
                g.land.render();
                if(isMenu){
                    g.bird.render();
                    g.bird.fall();
                    g.renderGameover();
                    g.renderMedal();
                    g.renderMenuScore();
                    g.renderBestScore();
                    g.replayButton();
                }
                else{
                g.pipe.init();
                g.bird.init();
                g.bird.render();
                g.renderMessage();
                if(g.userInput.Type==game::input::PLAY){
                    g.start();
                    isMenu=1;
                    g.userInput.Type==game::input::NONE;
                }
                g.land.update();
                }
                g.display();
            }
        }
        else{
            g.takeInput();
            if(g.userInput.Type==game::input::PAUSE){
                isPause=abs(isPause-1);
                g.userInput.Type=game::input::NONE;
            }
            if(isPause==0 && g.userInput.Type==game::input::PLAY){
                g.bird.resetTime();
                g.userInput.Type=game::input::NONE;
            }
            g.renderBackground();
            g.pipe.render();
            g.land.render();
            g.bird.render();
            g.renderPlayingScore();

            if(!isPause){
                g.bird.update(g.getPipeWidth(),g.getPipeHeight());
                g.pipe.update();
                g.land.update();
                g.pauseButton();
            }
            else {
                g.renderPause();
                g.renderMedal();
                g.resumeButton();
                g.renderMenuScore();
                g.renderBestScore();
                g.replayButton();

                if(g.userInput.Type==game::input::PLAY){
                    if(g.checkReplay()) isPause=0;
                    g.userInput.Type=game::input::NONE;
                }
            }
            g.display();

        }

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    return 0;
}



