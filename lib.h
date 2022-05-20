#pragma once


#include <SDL_image.h>
#include <string>

using namespace std;

class position
{
public:
    short x, y, angle;
    void setPosition(const short int x, const short int y);
};

class LTexture
{
public:
    LTexture();
    ~LTexture() {}

    bool isNULL();

    bool Load(string path,double scale);

     short getWidth();
     short getHeight();

    void free();
    void Render( short x,  short y,  short angle = 0, SDL_Rect* clip = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    SDL_Texture* Texture;

     short textureWidth;
     short textureHeight;


    static SDL_Window* gWindow;
    static SDL_Renderer* gRenderer;
    static SDL_Event event;
    static bool quit;
    static bool die;
    static  short score;

    static const short SCREEN_WIDTH = 350;
    static const short SCREEN_HEIGHT = 625;
    static const  short PIPE_SPACE = 160;
    static const  short PIPE_NUMBER = 4;
    static const  short PIPE_DISTANCE = 220;
    static const  short LAND_HEIGHT = 140;
    static const  short BIRD_WIDTH = 50;
    static const  short BIRD_HEIGHT = 35;
};
