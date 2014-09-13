class Game
{
public:
	Game();
	~Game();
	void render();
	void update();
	void input(Input* input);
private:
	std::vector<Rectangle*> rectangles;
	Player* player = nullptr;
	Menu* mainmenu = nullptr;
};

Game::Game()
{
	player = new Player();

	mainmenu = new Menu();

	mainmenu->addBackground(640, 480, 100, 80, 80);

	SDL_Color textColor = { 0, 0, 0 };
	mainmenu->addButton("button1", "Game", 20, textColor, 38, 38, GAME, 64, 32, 32, 32);
	mainmenu->addButton("button1", "Help", 20, textColor, 38, 102, MAINMENU, 64, 32, 32, 96);
	mainmenu->addButton("button1", "Score", 20, textColor, 36, 166, MAINMENU, 64, 32, 32, 160);
	mainmenu->addButton("button1", "Exit", 20, textColor, 38, 230, MAINMENU, 64, 32, 32, 224);

	for (int x = 0; x < 20; ++x)
	{
		for (int y = 7; y < 15; ++y)
		{
			Rectangle* rect = new Rectangle("bricks_darkyellow_medium", 32, 32, x*32, y*32);
			rectangles.push_back(rect);
		}
	}
}

Game::~Game() {}

void Game::render()
{
	if (state == MAINMENU)
	{
		mainmenu->render();
	}
	else if (state == GAME)
	{
		for (Rectangle* rect : rectangles)
			rect->render();
		
		player->render();
	}
}

void Game::update()
{
	if (state == MAINMENU)
	{
		mainmenu->update();
	}
	else if (state == GAME)
	{
		player->update();
	}
}

void Game::input(Input* input)
{
	if (state == MAINMENU)
	{
		mainmenu->input(input);
	}
	else if (state == GAME)
	{
		player->input(input);
	}
}