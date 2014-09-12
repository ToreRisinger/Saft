#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "Timer.h"
#include "Input.h"
#include "Game.h"
#include "Renderer.h"

bool init();
void close();
void clearScreen();
void drawScreen();

SDL_Surface* loadSurface(std::string path);
SDL_Texture* loadTexture(std::string path);

SDL_Window* gWindow = NULL;
//SDL_Surface* gScreenSurface = NULL; vi använder inte denna atm
SDL_Renderer* Renderer::gRenderer = NULL;

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
		Input input;
		Game game;

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
					input.getEvent(&e);
			}
			
			game.input(input);

			//----------------------------------
			
			//--------------UPDATE--------------

			input.update(); //update the input class
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
	SDL_RenderPresent(Renderer::gRenderer);
}

void clearScreen()
{
	SDL_RenderClear(Renderer::gRenderer);
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
			Renderer::gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (Renderer::gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(Renderer::gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

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
	SDL_DestroyRenderer(Renderer::gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	Renderer::gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}