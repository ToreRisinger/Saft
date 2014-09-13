#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "Input.h"
#include "Util.h"
#include "Texture.h"
#include "Rectangle.h"
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

			//if this frame was to fast, we delay to slow down
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
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create Window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
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
	SDL_Quit();
}