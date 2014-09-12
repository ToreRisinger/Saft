#include <SDL.h>

class Input
{
public:
	Input();
	void update();

	bool getKey(int keyCode);
	bool getKeyPressed(int keyCode);
	void keyUp(int keyCode);
	void keyDown(int keyCode);
	void clearKeyPressed();
	void Input::getEvent(SDL_Event* event);

private:
	const Uint8 *keyStates;
	bool keyPressed[350];
	bool keyCompare[350];
};
