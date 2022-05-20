
#include"land.h"

void land::init(){
    landPosition.setPosition(0, SCREEN_HEIGHT - LAND_HEIGHT);
    Load("asset/image/land.png",1);
}


void land::Free(){
    free();
}

void land::render(){
    if(landPosition.x>0){
        Render(landPosition.x,landPosition.y);
    }
    else if(landPosition.x>-SCREEN_WIDTH && landPosition.x<=0){
        Render(landPosition.x,landPosition.y);
        Render(landPosition.x+SCREEN_WIDTH,landPosition.y);
    }
    else{
        landPosition.setPosition(0,SCREEN_HEIGHT-LAND_HEIGHT);
        Render(landPosition.x,landPosition.y);
    }
}

void land::update(){
    landPosition.x-=(3+score/30);
}
