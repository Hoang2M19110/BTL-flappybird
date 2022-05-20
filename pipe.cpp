#include"pipe.h"


 vector<position> pipePosition;

void pipe::init()
{
    pipePosition.clear();
    for (signed char i = 0; i < PIPE_NUMBER; i++)
    {
        position temp;
        temp.setPosition(SCREEN_WIDTH + i * PIPE_DISTANCE + 350, (rand() % (randMax - randMin + 1)) + randMin);
        pipePosition.push_back(temp);
        Load( "asset/image/pipe.png", 1 );
    }

}

void pipe::Free()
{
    free();
}

void pipe::render()
{
    for (signed char i = 0; i < PIPE_NUMBER; i++)
    {
        if (pipePosition[i].x <= SCREEN_WIDTH && pipePosition[i].x > -getWidth())
        {
            Render(pipePosition[i].x, pipePosition[i].y);
        }
        Render(pipePosition[i].x, pipePosition[i].y + getHeight() + PIPE_SPACE, 180);
    }
}




void pipe::update()
{
    if (!die)
    {
        for (signed char i = 0; i < PIPE_NUMBER; i++)
        {
            if (pipePosition[i].x < - getWidth())
            {
                pipePosition[i].y = (rand() % (randMax - randMin + 1)) + randMin;
                pipePosition[i].x = pipePosition[(i + PIPE_NUMBER - 1) % PIPE_NUMBER].x + PIPE_DISTANCE;
            }
            else
            {
                pipePosition[i].x -= (3+score/30);
            }
        }
    }
}


