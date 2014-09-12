#include "Rectangle.h"
#include <vector>
#include "Player.h"

class Game
{
public:
	Game();
	~Game();
	void render();
	void update();
	void input(Input& input);

private:
	//TODO all game objects in a vector
	std::vector<Rectangle*> rectangles;
	Player* player = nullptr;
};

Game::Game()
{
	player = new Player();
	for (int x = 0; x < 20; ++x)
	{
		for (int y = 7; y < 15; ++y)
		{
			Rectangle* rect = new Rectangle();
			rect->setTexture("bricks_darkyellow_medium.png");
			rect->setWidth(32);
			rect->setHeight(32);
			rect->setX(x*32);
			rect->setY(y*32);
			rectangles.push_back(rect);
		}
	}
	
}

Game::~Game()
{
	
}

void Game::render()
{
	for (Rectangle* rect : rectangles)
		rect->render();
	player->render();
}

void Game::update()
{
	player->update();
}

void Game::input(Input& input)
{
	player->input(input);
}