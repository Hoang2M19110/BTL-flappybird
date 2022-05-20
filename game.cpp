#include"game.h"
#include <fstream>
#include<string>

void game::takeInput(){
    while(SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            quit = true;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN || (event.type == SDL_KEYDOWN &&
		(event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_UP) && event.key.repeat == 0) )
        {
            userInput.Type = input::PLAY;
        }
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE && event.key.repeat == 0)
		{
			userInput.Type = input::PAUSE;
		}
    }
}

bool game::checkReplay(){
    int x, y;
	SDL_GetMouseState(&x, &y);
	if ((x > (SCREEN_WIDTH - 100)/2 && x < (SCREEN_WIDTH + 100) / 2 && y > 380 && y < 380 + 60)||(event.type == SDL_KEYDOWN &&
		(event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_UP) && event.key.repeat == 0))
	{
		return true;
	}
	return false;
}

void game::start(){
    die = false;
    score = 0;
    bird.resetTime();
}

game::game(){
    initGraphic();
    land.init();
    pipe.init();
    bird.init();
}



game::~game(){
    free();
    bird.Free();
    land.Free();
   releaseGraphic();
}



void game::initGraphic(){

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
	}
	else
	{
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		gWindow = SDL_CreateWindow( "Flappy Bird", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
			}
			else
			{
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
				}

			}
		}
	}
}

void game::renderBackground(){
	LTexture image;
	image.Load("asset/image/background.png", 1);
	image.Render(0, 0);
	image.free();
}

void game::renderMessage(){
    LTexture image;
    image.Load("asset/image/message.png", 1);
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 180);
	image.free();
}

void game::resumeButton(){
    LTexture image;
	image.Load("asset/image/resume.png", 1);
	image.Render(SCREEN_WIDTH - 50, 20);
	image.free();
}

void game::pauseButton(){
    LTexture image;
	image.Load("asset/image/pause.png", 1);
	image.Render(SCREEN_WIDTH - 50, 20);
	image.free();
}

void game::replayButton(){
    LTexture image;
	image.Load("asset/image/replay.png", 1);
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 380);
	image.free();
}

void game::releaseGraphic(){
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    SDL_DestroyRenderer( gRenderer );
    gRenderer = NULL;
    IMG_Quit();
    SDL_Quit();
}

void game::renderPause(){
	LTexture image;
	image.Load("asset/image/pausemenu.png", 1);
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 205);
	image.free();
}

void game::renderGameover(){
    LTexture image;
	image.Load("asset/image/gameover.png", 1);
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 150);
	image.free();
}

void game::renderPlayingScore(){
    string s=to_string(score);
    signed char l=s.length();
    LTexture image;
    for(signed char i=0;i<l;i++){
        signed char number = s[i] - '0';
		if (number == 1) image.Load("asset/number/1.png", 1);
		else if (number == 2) image.Load("asset/number/2.png", 1);
		else if (number == 3) image.Load("asset/number/3.png", 1);
		else if (number == 4) image.Load("asset/number/4.png", 1);
		else if (number == 5) image.Load("asset/number/5.png", 1);
		else if (number == 6) image.Load("asset/number/6.png", 1);
		else if (number == 7) image.Load("asset/number/7.png", 1);
		else if (number == 8) image.Load("asset/number/8.png", 1);
		else if (number == 9) image.Load("asset/number/9.png", 1);
		else image.Load("asset/number/0.png", 1);
		image.Render((SCREEN_WIDTH - (image.getWidth() * l + (l - 1) * 10)) / 2 + (i + 30) * i, 100);
	}
	image.free();
}

void game::renderMenuScore(){
    string s=to_string(score);
    signed char l=s.length();
    LTexture image;
    for(signed char i=0;i<l;i++){
        signed char number = s[i] - '0';
		if (number == 1) image.Load("asset/number/1.png", 0.6);
		else if (number == 2) image.Load("asset/number/2.png", 0.6);
		else if (number == 3) image.Load("asset/number/3.png", 0.6);
		else if (number == 4) image.Load("asset/number/4.png", 0.6);
		else if (number == 5) image.Load("asset/number/5.png", 0.6);
		else if (number == 6) image.Load("asset/number/6.png", 0.6);
		else if (number == 7) image.Load("asset/number/7.png", 0.6);
		else if (number == 8) image.Load("asset/number/8.png", 0.6);
		else if (number == 9) image.Load("asset/number/9.png", 0.6);
		else image.Load("asset/number/0.png", 0.6);
		image.Render(260 - image.getWidth() * (l - i - 1) * 0.75 - 5 * (l - i - 1), 268);
	}
	image.free();
}

void game::renderBestScore(){
    ifstream fileIn("asset/date/bestscore.txt");
    fileIn>>bestScore;
    ofstream fileOut("asset/data/bestScore.txt",ios::trunc);
    if(score>bestScore) bestScore=score;

    string s=to_string(bestScore);
    signed char l=s.length();
    LTexture image;
    for(signed char i=0;i<l;i++){
        signed char number = s[i] - '0';
		if (number == 1) image.Load("asset/number/1.png", 0.6);
		else if (number == 2) image.Load("asset/number/2.png", 0.6);
		else if (number == 3) image.Load("asset/number/3.png", 0.6);
		else if (number == 4) image.Load("asset/number/4.png", 0.6);
		else if (number == 5) image.Load("asset/number/5.png", 0.6);
		else if (number == 6) image.Load("asset/number/6.png", 0.6);
		else if (number == 7) image.Load("asset/number/7.png", 0.6);
		else if (number == 8) image.Load("asset/number/8.png", 0.6);
		else if (number == 9) image.Load("asset/number/9.png", 0.6);
		else image.Load("asset/number/0.png", 0.6);
		image.Render(260 - image.getWidth()*(l-i-1)*0.75 - 5*(l - i - 1), 315);
	}
	image.free();
}

void game::renderMedal(){
    LTexture image;
    if (score >= 0 && score <= 9) image.Load("asset/medal/rookie.png", 0.75);
	else if (score >= 10 && score <= 19) image.Load("asset/medal/bronze.png", 0.75);
	else if (score >= 20 && score <= 29) image.Load("asset/medal/silver.png", 0.75);
	else if (score >= 30 && score <= 39) image.Load("asset/medal/gold.png", 0.75);
	else if (score >= 40 && score <= 49) image.Load("asset/medal/platinum.png", 0.75);
	else image.Load("asset/medal/BE.png", 0.75);


	image.Render(82, 275);
	image.free();
}

void game::display(){
    SDL_RenderPresent(gRenderer);
    SDL_RenderClear(gRenderer);
}

