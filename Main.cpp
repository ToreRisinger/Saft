#include <math.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Input.h"
#include "Util.h"
#include "Texture.h"
#include "Block.h"
#include "Level.h"
#include "Player.h"
#include "Timer.h"
#include "Button.h"
#include "Menu.h"
#include "Game.h"

bool init();
void close();
void clearScreen();
void drawScreen();

SDL_Surface* loadSurface(std::string path);
SDL_Texture* loadTexture(std::string path);

//SDL_Surface* gScreenSurface = NULL; vi använder inte denna atm
SDL_Window* gWindow = nullptr;
Input* input = nullptr;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const double FRAME_TIME = 1000/60;

int main(int argc, char* args[])
{
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		bool isRunning = true;
		int frames = 0;
		int seconds = 0;
		Timer loopTime;
		loopTime.start();
		SDL_Event e;
		Game game;
		input = new Input();

		//GAMELOOP
		while (isRunning)
		{
			seconds += loopTime.getElapsedTime();
			loopTime.start();
			
			//--------------INPUT--------------

			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
					isRunning = false;
				else
					input->getEvent(&e);
			}
			
			game.input(input);

			//----------------------------------
			
			//--------------UPDATE--------------

			input->update(); //update the input class
			game.update(); // update game

			//----------------------------------

			//--------------RENDER--------------

			clearScreen();
			game.render();

			//Draw the screen we have prepared this gameloop, Vsync is activated to this will regulate the framerate to 60 fps
			drawScreen();
			
			//----------------------------------

			if (seconds >= 1000)
			{
				std::stringstream ss;
				std::string fps;
				ss << frames;
				ss >> fps;
				printf(("fps: " + fps + '\n').c_str());
				frames = 0;
				seconds = 0;
			}

			//If Vsync isnt working, this will limit the framerate to about 60-63. Might need to make this better
			double thisFrameTime = loopTime.getElapsedTime();
			if (thisFrameTime < FRAME_TIME) SDL_Delay(FRAME_TIME - thisFrameTime);
			
			frames++;
		}
	}

	close();

	return 0;
}

void drawScreen()
{
	SDL_RenderPresent(gRenderer);
}

void clearScreen()
{
	SDL_RenderClear(gRenderer);
}

bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	//Create Window
	gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}
	
		//Create renderer for window
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (gRenderer == NULL)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}
			
	//Initialize renderer color
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}

	//Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}

	gFont = TTF_OpenFont("res/fonts/00TT.TTF", 28);
	if (gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}
			
	return true;
}

void close()
{
	//Destroy window    
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}
