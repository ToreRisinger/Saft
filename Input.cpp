#include "Input.h"

Input::Input()
{
	clearKeyPressed();
}

void Input::getEvent(SDL_Event* e)
{
	if ((*e).type == SDL_KEYDOWN)
		keyDown((*e).key.keysym.scancode);
	else if ((*e).type == SDL_KEYUP)
		keyUp((*e).key.keysym.scancode);
}

void Input::update()
{
	keyStates = SDL_GetKeyboardState(NULL);
	for (int i = 0; i < 350; i++) {
		keyCompare[i] = keyPressed[i];
	}
}

bool Input::getKey(int keyCode)
{
	return SDL_GetKeyboardState(NULL)[keyCode];
}

bool Input::getKeyPressed(int keyCode)
{
	if (keyPressed[keyCode] && !keyCompare[keyCode]) //we pressed
		return true;
	else
		return false;
}

void Input::keyUp(int keyCode)
{
	keyPressed[keyCode] = false;
}

void Input::keyDown(int keyCode)
{
	keyPressed[keyCode] = true;
}

void Input::clearKeyPressed()
{
	for (int i = 0; i < 256; i++)
	{
		keyPressed[i] = false;
	}

	for (int i = 0; i < 256; i++)
	{
		keyCompare[i] = false;
	}
}