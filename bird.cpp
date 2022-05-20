#include"bird.h"
#include<iostream>

void bird::init()
{

    birdPosition.setPosition(75, SCREEN_HEIGHT / 2 - 10 );
    ahead = 0;
    angle = 0;
    Load("asset/image/bird.png" , 1);


}

void bird::Free(){
    free();
}

void bird::render(){
    Render(birdPosition.x, birdPosition.y,angle);
}



void bird::fall(){
    if(die && birdPosition.y<SCREEN_HEIGHT-LAND_HEIGHT-BIRD_HEIGHT-5){
        if(time==0){
            x0 = birdPosition.y;
            angle=-25;
        }
        else if(angle<70 && time >30) angle+=3;

        if(time>=0){
            birdPosition.y=x0+time*time*0.18-7.3*time;
            time++;
        }

    } else return;
}



void bird::update(short pipeWidth, short pipeHeight)
{

       if (time == 0)
        {
            x0 = birdPosition.y;
            angle = -25;
        }
        else if (angle < 70 && time > 30)
        {
            angle += 3;
        }

        if (time >= 0)
        {
            birdPosition.y = x0 + time * time * 0.18 - 7.3 * time;
            time++;
        }

        if ( (birdPosition.x + getWidth() > pipePosition[ahead].x +5) && (birdPosition.x + 5 < pipePosition[ahead].x + pipeWidth) &&
             (birdPosition.y + 5 < pipePosition[ahead].y + pipeHeight || birdPosition.y  + getHeight() > pipePosition[ahead].y + pipeHeight + PIPE_SPACE + 5) )
        {
            die = true;
        }
        else if (birdPosition.x > pipePosition[ahead].x + pipeWidth )
        {
            ahead = ( ahead + 1 ) % PIPE_NUMBER;
            score++;
        }

        if (birdPosition.y > SCREEN_HEIGHT - LAND_HEIGHT -  BIRD_HEIGHT - 5 || birdPosition.y < - 10 )
        {
            die = true;
        }

}

